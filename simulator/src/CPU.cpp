#include "../include/CPU.hpp"
#include "../include/Executor.hpp"
#include "../include/RAMDevice.hpp"
#include "../include/ROMDevice.hpp"
#include "../include/UARTDevice.hpp"
#include "../include/MemoryMap.hpp"
#include "../include/Cache.hpp"
#include "../include/Decoder.hpp"
#include <memory>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cctype>

using namespace MemMap;

namespace {

    constexpr std::uint64_t VRAM_DUMP_INTERVAL = 2;

    std::uint64_t g_instrCount = 0;

    void dumpVRAMToTerminal(const CPU& cpu)
    {
        bool hasContent = false;

        // 1. Primeira varredura: verificar se existe algum byte != 0x00
        for (std::uint32_t addr = VRAM_START; addr <= VRAM_END; ++addr) {
            if (cpu.loadByte(addr) != 0x00) {
                hasContent = true;
                break;
            }
        }

        // Se está tudo vazio, não imprime nada
        if (!hasContent) {
            return;
        }

        // 2. Agora imprime porque sabemos que há conteúdo
        std::cout << "\n[VRAM - dump após " << g_instrCount
                << " instruções]\n";

        std::uint32_t col = 0;

        for (std::uint32_t addr = VRAM_START; addr <= VRAM_END; ++addr) {
            std::uint8_t value = cpu.loadByte(addr);

            char c = (value >= 32 && value <= 126)
                    ? static_cast<char>(value)
                    : '.';

            std::cout << c;
            ++col;

            if (col == VRAM_COLS) {
                std::cout << '\n';
                col = 0;
            }
        }

        if (col != 0) {
            std::cout << '\n';
        }

        std::cout << "[fim VRAM]\n";
    }

}

CPU::CPU(size_t memorySize)
    : regs(), bus(), pc(0), cache(&bus)

{
    const size_t minSize = static_cast<size_t>(ADDRESS_SPACE_SZ);
    if (memorySize < minSize) {
        memorySize = minSize;
    }

    auto ram = std::make_shared<RAMDevice>(memorySize);
    bus.addDevice(0x00000000u, static_cast<uint32_t>(memorySize), ram);

    // std::vector<uint8_t> romData = {}; 
    // auto rom = std::make_shared<ROMDevice>(romData);
    // bus.addDevice(0x00001000u, 0x1000u, rom);
    
    auto uart = std::make_shared<UARTDevice>();
    bus.addDevice(0x10000000u, 0x100u, uart);
}

bool CPU::loadProgram(const std::string& filename, uint32_t entryPoint)
{
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "[ERRO] Não foi possível abrir o arquivo: " << filename << "\n";
        return false;
    }

    std::vector<uint8_t> romData(8 * 1024 * 1024, 0); // 8 MB
    uint32_t currentAddr = 0;

    std::string line;

    while (std::getline(file, line)) {
        if (line.empty())
            continue;

        // detecta @endereçoxxx:
        if (line[0] == '@') {
            currentAddr = std::stoul(line.substr(1), nullptr, 16);
            continue;
        }

        // linha com palavra de 32 bits
        if (line.size() >= 8) {
            uint32_t word = std::stoul(line.substr(0, 8), nullptr, 16);

            // little endian
            romData[currentAddr + 0] = (word >> 0) & 0xFF;
            romData[currentAddr + 1] = (word >> 8) & 0xFF;
            romData[currentAddr + 2] = (word >> 16) & 0xFF;
            romData[currentAddr + 3] = (word >> 24) & 0xFF;

            currentAddr += 4;
        }
    }

    auto rom = std::make_shared<ROMDevice>(romData);

    const uint32_t ROM_BASE_ADDR = 0x00000000;  
    bus.addDevice(ROM_BASE_ADDR, romData.size(), rom);

    pc = entryPoint;

    std::cout << "[INFO] Arquivo HEX carregado com sucesso.\n";
    return true;
}



// Registradores
void CPU::writeReg(size_t index, uint32_t value) {
    regs.write(index, value);
}

uint32_t CPU::readReg(size_t index) const {
    return regs.read(index);
}

void CPU::dump() const {
    regs.dump();
}

uint8_t CPU::loadByte(uint32_t addr) const {
    return cache.readByte(addr);
}

uint16_t CPU::loadHalf(uint32_t addr) const {
    return cache.readHalf(addr);
}

uint32_t CPU::loadWord(uint32_t addr) const {
    return cache.readWord(addr);
}

void CPU::storeByte(uint32_t addr, uint8_t value) {
    cache.writeByte(addr, value);
}

void CPU::storeHalf(uint32_t addr, uint16_t value) {
    cache.writeHalf(addr, value);
}

void CPU::storeWord(uint32_t addr, uint32_t value) {
    cache.writeWord(addr, value);
}

uint32_t CPU::fetch() const {
    return loadWord(pc);
}

void CPU::run() {
    while (pc != 0) {
        try {
            // 1. FETCH
            uint32_t instrWord = fetch();

            // 2. DECODE
            Instruction instr = decoder.decode(instrWord);

            // 3. EXECUTE
            uint32_t currentPC = pc; 

            if (instr.type == InstructionType::UNKNOWN) {
                pc += 4;
                continue;
            }

            execute(instr);

            // 4. NEXT PC
            if (pc == currentPC) {
                advancePC(); 
            }

        } catch (const std::exception& e) {
            std::cerr << "[ERRO CRÍTICO] Excecao na execucao em 0x" 
                      << std::hex << pc << ": " << e.what() << "\n" << std::dec;
            break; 
        }
    }

    std::cout << "\n--- SIMULACAO CONCLUIDA ---\n";
    dump(); 
}

void CPU::execute(const Instruction& instr) {

    switch (instr.type) {

        case InstructionType::R_TYPE:
            Executor::executeRType(instr, *this);
            break;

        case InstructionType::I_TYPE:
            Executor::executeIType(instr, *this);
            break;

        case InstructionType::S_TYPE:
            Executor::executeSType(instr, *this);
            break;

        case InstructionType::B_TYPE:
            Executor::executeBType(instr, *this);
            break;

        case InstructionType::U_TYPE:
            Executor::executeUType(instr, *this);
            break;

        case InstructionType::J_TYPE:
            Executor::executeJType(instr, *this);
            break;

        default:
            std::cout << "[ERRO] Tipo de instrucao desconhecido.\n";
            break;
    }

    ++g_instrCount;

    if (g_instrCount % VRAM_DUMP_INTERVAL == 0) {
        dumpVRAMToTerminal(*this);
    }
}
