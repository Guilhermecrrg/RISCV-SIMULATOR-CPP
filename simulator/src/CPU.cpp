#include "../include/CPU.hpp"
#include "../include/Executor.hpp"

CPU::CPU(size_t memorySize)
    : mem(memorySize), pc(0)
{
}

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
    return mem.readByte(addr);
}

uint16_t CPU::loadHalf(uint32_t addr) const {
    return mem.readHalf(addr);
}

uint32_t CPU::loadWord(uint32_t addr) const {
    return mem.readWord(addr);
}

void CPU::storeByte(uint32_t addr, uint8_t value) {
    mem.writeByte(addr, value);
}

void CPU::storeHalf(uint32_t addr, uint16_t value) {
    mem.writeHalf(addr, value);
}

void CPU::storeWord(uint32_t addr, uint32_t value) {
    mem.writeWord(addr, value);
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

        default:
            std::cout << "[ERRO] Tipo de instrução desconhecido.\n";
            break;
    }
}
