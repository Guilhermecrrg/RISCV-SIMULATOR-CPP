#include "../include/CPU.hpp"
#include "../include/Executor.hpp"
#include "../include/RAMDevice.hpp"
#include "../include/ROMDevice.hpp"
#include "../include/UARTDevice.hpp"
#include <memory>
#include <vector>
#include <iostream>

CPU::CPU(size_t memorySize)
    : regs(), bus(), pc(0)
{
    auto ram = std::make_shared<RAMDevice>(memorySize);
    bus.addDevice(0x00000000u, static_cast<uint32_t>(memorySize), ram);

    std::vector<uint8_t> romData = {}; 
    auto rom = std::make_shared<ROMDevice>(romData);
    bus.addDevice(0x00001000u, 0x1000u, rom);
    
    auto uart = std::make_shared<UARTDevice>();
    bus.addDevice(0x10000000u, 0x100u, uart);
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
    return bus.readByte(addr);
}

uint16_t CPU::loadHalf(uint32_t addr) const {
    return bus.readHalf(addr);
}

uint32_t CPU::loadWord(uint32_t addr) const {
    return bus.readWord(addr);
}

void CPU::storeByte(uint32_t addr, uint8_t value) {
    bus.writeByte(addr, value);
}

void CPU::storeHalf(uint32_t addr, uint16_t value) {
    bus.writeHalf(addr, value);
}

void CPU::storeWord(uint32_t addr, uint32_t value) {
    bus.writeWord(addr, value);
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
}
