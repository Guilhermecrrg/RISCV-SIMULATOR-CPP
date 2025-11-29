#include "../include/CPU.hpp"
#include "../include/Executor.hpp"

CPU::CPU() {
    
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


void CPU::execute(const Instruction& instr) {
    switch (instr.type) {

        case InstructionType::R_TYPE:
            executeR(instr);
            break;

        case InstructionType::I_TYPE:
            executeI(instr);
            break;

        default:
            std::cout << "Tipo de instrução não suportado.\n";
            break;
    }
}

void CPU::executeR(const Instruction& instr) {
    Executor::executeRType(instr, *this);
}

void CPU::executeI(const Instruction& instr) {
    Executor::executeIType(instr, *this);
}