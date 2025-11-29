#include "../include/Decoder.hpp"

Instruction Decoder::decodeR(uint32_t instr) {
    Instruction i;

    i.opcode = instr & 0x7F;               // bits 0-6
    i.rd     = (instr >> 7)  & 0x1F;       // bits 7-11
    i.funct3 = (instr >> 12) & 0x07;       // bits 12-14
    i.rs1    = (instr >> 15) & 0x1F;       // bits 15-19
    i.rs2    = (instr >> 20) & 0x1F;       // bits 20-24
    i.funct7 = (instr >> 25) & 0x7F;       // bits 25-31

    i.type = InstructionType::R_TYPE;

    return i;
}

Instruction Decoder::decodeI(uint32_t word) {
    Instruction instr;

    instr.opcode = word & 0x7F;               // bits 0-6
    instr.rd     = (word >> 7)  & 0x1F;       // bits 7-11
    instr.funct3 = (word >> 12) & 0x07;       // bits 12-14
    instr.rs1    = (word >> 15) & 0x1F;       // bits 15-19
    instr.imm = static_cast<int32_t>(word) >> 20;   // bits 20-31

    instr.type = InstructionType::I_TYPE;

    return instr;
}
