#include "../include/Decoder.hpp"

Instruction Decoder::decodeR(uint32_t instrWord) {
    Instruction i;

    i.opcode = instrWord & 0x7F;               // bits 0-6
    i.rd     = (instrWord >> 7)  & 0x1F;       // bits 7-11
    i.funct3 = (instrWord >> 12) & 0x07;       // bits 12-14
    i.rs1    = (instrWord >> 15) & 0x1F;       // bits 15-19
    i.rs2    = (instrWord >> 20) & 0x1F;       // bits 20-24
    i.funct7 = (instrWord >> 25) & 0x7F;       // bits 25-31

    i.type = InstructionType::R_TYPE;
    return i;
}

Instruction Decoder::decodeI(uint32_t instrWord) {
    Instruction i;

    i.opcode = instrWord & 0x7F;               // bits 0-6
    i.rd     = (instrWord >> 7)  & 0x1F;       // bits 7-11
    i.funct3 = (instrWord >> 12) & 0x07;       // bits 12-14
    i.rs1    = (instrWord >> 15) & 0x1F;       // bits 15-19

    i.imm = static_cast<int32_t>(instrWord) >> 20; // bits 20-31

    i.type = InstructionType::I_TYPE;
    return i;
}

Instruction Decoder::decodeS(uint32_t instrWord) {
    Instruction i;

    i.opcode = instrWord & 0x7F;                 // bits 0-6
    i.funct3 = (instrWord >> 12) & 0x07;         // bits 12-14
    i.rs1    = (instrWord >> 15) & 0x1F;         // bits 15-19
    i.rs2    = (instrWord >> 20) & 0x1F;         // bits 20-24

    uint32_t imm4_0  = (instrWord >> 7)  & 0x1F; // bits 7-11
    uint32_t imm11_5 = (instrWord >> 25) & 0x7F; // bits 25-31
    
    int32_t imm = static_cast<int32_t>((imm11_5 << 5) | imm4_0);

    
    if (imm & 0x800) {
        imm |= static_cast<int32_t>(0xFFFFF000);
    }

    i.imm = imm;
    i.type = InstructionType::S_TYPE;

    return i;
}

Instruction Decoder::decodeB(uint32_t instrWord) {
    Instruction i;

    i.opcode = instrWord & 0x7F;                // bits 0-6
    i.funct3 = (instrWord >> 12) & 0x07;        // bits 12-14
    i.rs1    = (instrWord >> 15) & 0x1F;        // bits 15-19
    i.rs2    = (instrWord >> 20) & 0x1F;        // bits 20-24

    uint32_t imm11   = (instrWord >> 7)  & 0x01;   // bit 7
    uint32_t imm4_1  = (instrWord >> 8)  & 0x0F;   // bits 8-11
    uint32_t imm10_5 = (instrWord >> 25) & 0x3F;   // bits 25-30
    uint32_t imm12   = (instrWord >> 31) & 0x01;   // bit 31

    int32_t imm = static_cast<int32_t>(
          (imm12   << 12)
        | (imm11   << 11)
        | (imm10_5 << 5)
        | (imm4_1  << 1)
    );

    if (imm & 0x1000) {                // bit 12
        imm |= static_cast<int32_t>(0xFFFFE000);
    }

    i.imm = imm;
    i.type = InstructionType::B_TYPE;

    return i;
}

Instruction Decoder::decodeU(uint32_t instrWord) {
    Instruction i;

    i.opcode = instrWord & 0x7F;               // bits 0-6
    i.rd     = (instrWord >> 7) & 0x1F;        // bits 7-11

    int32_t imm20 = static_cast<int32_t>(instrWord & 0xFFFFF000);
    
    i.imm = imm20;
    i.type = InstructionType::U_TYPE;
    return i;
}

