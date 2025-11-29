#include "../include/Decoder.hpp"

Instruction Decoder::decode(uint32_t instr) {
    Instruction i;

    i.opcode = instr & 0x7F;               // bits 0-6
    i.rd     = (instr >> 7)  & 0x1F;       // bits 7-11
    i.funct3 = (instr >> 12) & 0x07;       // bits 12-14
    i.rs1    = (instr >> 15) & 0x1F;       // bits 15-19
    i.rs2    = (instr >> 20) & 0x1F;       // bits 20-24
    i.funct7 = (instr >> 25) & 0x7F;       // bits 25-31

    return i;
}
