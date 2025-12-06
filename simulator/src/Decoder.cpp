#include "../include/Decoder.hpp"
#include <iostream>

Instruction Decoder::decode(uint32_t instrWord) {
    uint32_t opcode = instrWord & 0x7F;

    switch (opcode) {

        // R-TYPE
        case 0b0110011:
            return decodeR(instrWord);

        // I-TYPE
        case 0b0010011: 
        case 0b0000011: 
        case 0b1100111:
        case 0b0001111:
        case 0b1110011: 
            return decodeI(instrWord);

        // S-TYPE
        case 0b0100011:
            return decodeS(instrWord);

        // B-TYPE
        case 0b1100011:
            return decodeB(instrWord);

        // U-TYPE
        case 0b0110111: 
        case 0b0010111: 
            return decodeU(instrWord);

        // J-TYPE
        case 0b1101111:
            return decodeJ(instrWord);

        default:
            std::cout << "[ERRO] Opcode desconhecido: "  << opcode << "\n";
            Instruction inv{};
            inv.type = InstructionType::UNKNOWN;
            return inv;
    }
}


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

Instruction Decoder::decodeJ(uint32_t instrWord) {
    Instruction i;

    i.opcode = instrWord & 0x7F;          // bits 0-6
    i.rd     = (instrWord >> 7) & 0x1F;   // bits 7-11

    int32_t imm20    = static_cast<int32_t>((instrWord >> 31) & 0x1);   // bit 31
    int32_t imm10_1  = static_cast<int32_t>((instrWord >> 21) & 0x3FF); // bits 21-30
    int32_t imm11    = static_cast<int32_t>((instrWord >> 20) & 0x1);   // bit 20
    int32_t imm19_12 = static_cast<int32_t>((instrWord >> 12) & 0xFF);  // bits 12-19


    int32_t imm = (imm20 << 20)
                | (imm19_12 << 12)
                | (imm11 << 11)
                | (imm10_1 << 1);

     
    if (imm & (1 << 20)) {
        imm |= static_cast<int32_t>(0xFFE00000);
    }

    i.imm = imm;
    i.type = InstructionType::J_TYPE;

    return i;
}
