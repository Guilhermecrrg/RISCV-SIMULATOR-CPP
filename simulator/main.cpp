#include <iostream>
#include <cstdint>

#include "include/CPU.hpp"
#include "include/Decoder.hpp"

// -------------------------------------------------------
// ENCODE R-TYPE
// -------------------------------------------------------
uint32_t encodeR(uint32_t funct7, uint32_t rs2, uint32_t rs1, uint32_t funct3, uint32_t rd, uint32_t opcode) {
    return (funct7 << 25) |
    (rs2    << 20) |
    (rs1    << 15) |
    (funct3 << 12) |
    (rd     << 7)  |
    (opcode);
}

// -------------------------------------------------------
// ENCODE I-TYPE
// -------------------------------------------------------
uint32_t encodeI(int32_t imm, uint32_t rs1, uint32_t funct3, uint32_t rd, uint32_t opcode) {
    uint32_t imm12 = imm & 0xFFF;
    return (imm12 << 20) |
    (rs1   << 15) |
    (funct3 << 12)|
    (rd    << 7)  |
    (opcode);
}

// -------------------------------------------------------
// ENCODE S-TYPE (STORE)  — SB, SH, SW
// -------------------------------------------------------
uint32_t encodeS(uint32_t funct3, uint32_t rs2, uint32_t rs1, int32_t imm, uint32_t opcode) {
    uint32_t imm11_5 = (imm >> 5) & 0x7F;
    uint32_t imm4_0  = imm & 0x1F;


    return (imm11_5 << 25) |
        (rs2     << 20) |
        (rs1     << 15) |
        (funct3  << 12) |
        (imm4_0  << 7)  |
        opcode;
}
 
// -------------------------------------------------------
// ENCODE B-TYPE (BRANCHES)
// -------------------------------------------------------
uint32_t encodeB(int32_t imm, uint32_t rs2, uint32_t rs1, uint32_t funct3, uint32_t opcode) {
    uint32_t imm12   = (imm >> 12) & 0x1;      // bit 12
    uint32_t imm10_5 = (imm >> 5)  & 0x3F;     // bits 10-5
    uint32_t imm4_1  = (imm >> 1)  & 0xF;      // bits 4-1
    uint32_t imm11   = (imm >> 11) & 0x1;      // bit 11

    return (imm12   << 31) |
           (imm10_5 << 25) |
           (rs2     << 20) |
           (rs1     << 15) |
           (funct3  << 12) |
           (imm4_1  << 8 ) |
           (imm11   << 7 ) |
           opcode;
}

// -------------------------------------------------------
// ENCODE U-TYPE 
// -------------------------------------------------------
uint32_t encodeU(int32_t imm, uint32_t rd, uint32_t opcode) {
    uint32_t imm20 = (static_cast<uint32_t>(imm) & 0xFFFFF000);

    return imm20 | (rd << 7) | opcode;
}

// -------------------------------------------------------
// ENCODE U-TYPE 
// -------------------------------------------------------
uint32_t encodeJ(int32_t imm, uint32_t rd, uint32_t opcode) {
    uint32_t imm20    = (imm >> 20) & 0x1;
    uint32_t imm10_1  = (imm >> 1)  & 0x3FF;
    uint32_t imm11    = (imm >> 11) & 0x1;
    uint32_t imm19_12 = (imm >> 12) & 0xFF;

    return (imm20 << 31)
         | (imm19_12 << 12)
         | (imm11 << 20)
         | (imm10_1 << 21)
         | (rd << 7)
         | opcode;
}




int main() {
    CPU cpu(MemMap::ADDRESS_SPACE_SZ);
    Decoder decoder;

    // -------------------------------------------------------
    // Inicializar registradores base para os testes
    // -------------------------------------------------------
    cpu.writeReg(1, 10);
    cpu.writeReg(2, 5);

    // =======================================================
    // TESTES R-TYPE
    // =======================================================
    std::cout << "\n===== TESTES R-TYPE =====\n";

    // ADD x3 = x1 + x2 = 10 + 5 = 15
    uint32_t addInstr = encodeR(0,2,1,0b000,3,0b0110011);
    cpu.execute(decoder.decode(addInstr));
    std::cout << "ADD  x3 -> esperado: 15, obtido: " << cpu.readReg(3) << "\n";

    // SUB x4 = x1 - x2 = 10 - 5 = 5
    uint32_t subInstr = encodeR(0b0100000,2,1,0b000,4,0b0110011);
    cpu.execute(decoder.decode(subInstr));
    std::cout << "SUB  x4 -> esperado: 5, obtido: " << cpu.readReg(4) << "\n";

    // AND x5 = x1 & x2 = 10 & 5 = 0
    uint32_t andInstr = encodeR(0,2,1,0b111,5,0b0110011);
    cpu.execute(decoder.decode(andInstr));
    std::cout << "AND  x5 -> esperado: 0, obtido: " << cpu.readReg(5) << "\n";

    // OR x6 = x1 | x2 = 10 | 5 = 15
    uint32_t orInstr = encodeR(0,2,1,0b110,6,0b0110011);
    cpu.execute(decoder.decode(orInstr));
    std::cout << "OR   x6 -> esperado: 15, obtido: " << cpu.readReg(6) << "\n";

    // XOR x7 = x1 ^ x2 = 10 ^ 5 = 15
    uint32_t xorInstr = encodeR(0,2,1,0b100,7,0b0110011);
    cpu.execute(decoder.decode(xorInstr));
    std::cout << "XOR  x7 -> esperado: 15, obtido: " << cpu.readReg(7) << "\n";

    // SLT x8 = (x1 < x2) ? 1 : 0 -> 10 < 5 -> 0
    uint32_t sltInstr = encodeR(0,2,1,0b010,8,0b0110011);
    cpu.execute(decoder.decode(sltInstr));
    std::cout << "SLT  x8 -> esperado: 0, obtido: " << cpu.readReg(8) << "\n";


    // =======================================================
    // TESTES I-TYPE
    // =======================================================
    std::cout << "\n===== TESTES I-TYPE =====\n";

    // ADDI x9 = x1 + 3 = 13
    uint32_t addiInstr = encodeI(3, 1, 0b000, 9, 0b0010011);
    cpu.execute(decoder.decode(addiInstr));
    std::cout << "ADDI x9  -> esperado: 13, obtido: " << cpu.readReg(9) << "\n";

    // XORI x10 = x1 ^ 7 = 10 ^ 7 = 13
    uint32_t xoriInstr = encodeI(7, 1, 0b100, 10, 0b0010011);
    cpu.execute(decoder.decode(xoriInstr));
    std::cout << "XORI x10 -> esperado: 13, obtido: " << cpu.readReg(10) << "\n";

    // ORI x11 = x1 | 8 = 10 | 8 = 10
    uint32_t oriInstr = encodeI(8, 1, 0b110, 11, 0b0010011);
    cpu.execute(decoder.decode(oriInstr));
    std::cout << "ORI  x11 -> esperado: 10, obtido: " << cpu.readReg(11) << "\n";

    // ANDI x12 = x1 & 12 = 10 & 12 = 8
    uint32_t andiInstr = encodeI(12, 1, 0b111, 12, 0b0010011);
    cpu.execute(decoder.decode(andiInstr));
    std::cout << "ANDI x12 -> esperado: 8, obtido: " << cpu.readReg(12) << "\n";

    // SLTI x13 = (x1 < -2) ? 1 : 0 -> 10 < -2 -> 0
    uint32_t sltiInstr = encodeI(-2, 1, 0b010, 13, 0b0010011);
    cpu.execute(decoder.decode(sltiInstr));
    std::cout << "SLTI x13 -> esperado: 0, obtido: " << cpu.readReg(13) << "\n";


    // =======================================================
    // TESTES S-TYPE
    // =======================================================
    std::cout << "\n===== TESTES S-TYPE (STORE) =====\n";

    cpu.writeReg(1, 100);
    cpu.writeReg(2, 0xAABBCCDD);

    // SB (store byte — salva DD)
    uint32_t sbInstr = encodeS(0b000, 2, 1, 4, 0b0100011);
    cpu.execute(decoder.decode(sbInstr));
    uint8_t sb_val = cpu.loadByte(104);
    std::cout << std::hex;
    std::cout << "SB  mem[104] -> esperado: 0xdd, obtido: 0x" << (int)sb_val << std::dec << "\n";

    // SH (store half — salva CC DD)
    uint32_t shInstr = encodeS(0b001, 2, 1, 8, 0b0100011);
    cpu.execute(decoder.decode(shInstr));
    uint16_t sh_val = cpu.loadHalf(108);
    std::cout << std::hex;
    std::cout << "SH  mem[108..109] -> esperado: 0xccdd, obtido: 0x" << sh_val << std::dec << "\n";

    // SW (store word — salva AA BB CC DD)
    uint32_t swInstr = encodeS(0b010, 2, 1, 12, 0b0100011);
    cpu.execute(decoder.decode(swInstr));
    uint32_t sw_val = cpu.loadWord(112);
    std::cout << std::hex;
    std::cout << "SW  mem[112..115] -> esperado: 0xaabbccdd, obtido: 0x" << sw_val << std::dec << "\n";

    // =======================================================
    // TESTES B-TYPE (BRANCH ESCALONANDO O PC)
    // =======================================================
    std::cout << "\n===== TESTES B-TYPE =====\n";

    // PC inicial
    cpu.setPC(0);

    // Registradores
    cpu.writeReg(1, 10);
    cpu.writeReg(2, 10);

    // -------------------------------------------------------
    // BEQ x1, x2, offset = 8  (PC + 8)
    // Deve saltar
    // -------------------------------------------------------
    uint32_t beqInstr = encodeB(
        8,        // offset
        2, 1,     // rs2, rs1
        0b000,    // funct3 (BEQ)
        0b1100011 // opcode
    );

    cpu.execute(decoder.decode(beqInstr));
    std::cout << "BEQ  (esperado PC=8)   PC=" << cpu.getPC() << "\n";

    // -------------------------------------------------------
    // BNE x1, x2, offset = 12 (não deve saltar)
    // -------------------------------------------------------
    uint32_t bneInstr = encodeB(
        12,
        2, 1,
        0b001,     // BNE
        0b1100011
    );

    cpu.setPC(0);
    cpu.execute(decoder.decode(bneInstr));
    std::cout << "BNE  (esperado PC=4)   PC=" << cpu.getPC() << "\n";

    // -------------------------------------------------------
    // BLT (10 < 20) → salta
    // -------------------------------------------------------
    cpu.writeReg(1, 10);
    cpu.writeReg(2, 20);

    uint32_t bltInstr = encodeB(
        16,
        2, 1,
        0b100,     // BLT
        0b1100011
    );

    cpu.setPC(0);
    cpu.execute(decoder.decode(bltInstr));
    std::cout << "BLT  (PC esperado=16)  PC=" << cpu.getPC() << "\n";

    // -------------------------------------------------------
    // BGE (20 >= 10) → salta
    // -------------------------------------------------------
    cpu.writeReg(1, 20);
    cpu.writeReg(2, 10);

    uint32_t bgeInstr = encodeB(
        20,
        2, 1,
        0b101,     // BGE
        0b1100011
    );

    cpu.setPC(0);
    cpu.execute(decoder.decode(bgeInstr));
    std::cout << "BGE  (PC esperado=20)  PC=" << cpu.getPC() << "\n";

    std::cout << "\n===== TESTES U-TYPE =====\n";

    cpu.setPC(100); // para testar AUIPC

    uint32_t luiInstr = encodeU(0x12345000, 14, 0b0110111);
    cpu.execute(decoder.decode(luiInstr));
    std::cout << "LUI  x14 = 0x" << std::hex << cpu.readReg(14)
            << "  (esperado 0x12345000)\n" << std::dec;

    uint32_t auipcInstr = encodeU(0x00012000, 15, 0b0010111);
    cpu.execute(decoder.decode(auipcInstr));
    std::cout << "AUIPC x15 = 0x" << std::hex << cpu.readReg(15)
            << "  (esperado 100 + 0x12000)\n" << std::dec;


    std::cout << "\n===== TESTE J-TYPE (JAL) =====\n";

    cpu.setPC(100);   // exemplo
    uint32_t jalInstr = encodeJ(16, 5, 0b1101111); // pular +16 bytes

    cpu.execute(decoder.decode(jalInstr));

    std::cout << "x5 (link) = " << cpu.readReg(5) << " (esperado 104)\n";
    std::cout << "PC        = " << cpu.getPC()    << " (esperado 116)\n";


    // Dump final dos registradores
    std::cout << "\n=== ESTADO FINAL DOS REGISTRADORES ===\n";
    cpu.dump();

    uint32_t invalidInstr = 0xFFFFFFFF;   
    cpu.execute(decoder.decode(invalidInstr));

    std::cin.get();
    return 0;

}
