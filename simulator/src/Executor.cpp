#include "../include/Executor.hpp"
#include "../include/ALU.hpp"
#include "../include/CPU.hpp"
#include <iostream>

void Executor::executeRType(const Instruction& instr, CPU& cpu) {
    int32_t rs1 = static_cast<int32_t>(cpu.readReg(instr.rs1));
    int32_t rs2 = static_cast<int32_t>(cpu.readReg(instr.rs2));

    uint32_t result = 0;

    switch (instr.funct3) {

        case 0b000: // ADD / SUB
            if (instr.funct7 == 0b0100000) // SUB
                result = static_cast<uint32_t>(ALU::subSigned(rs1, rs2));
            else // ADD
                result = static_cast<uint32_t>(ALU::addSigned(rs1, rs2));
            break;

        case 0b001: // SLL
            result = ALU::sllOp(static_cast<uint32_t>(rs1), static_cast<uint32_t>(rs2) & 0x1F);
            break;

        case 0b101: // SRL / SRA
            if (instr.funct7 == 0b0100000) // SRA
                result = ALU::sraOp(rs1, static_cast<uint32_t>(rs2) & 0x1F);
            else                           // SRL
                result = ALU::srlOp(static_cast<uint32_t>(rs1), static_cast<uint32_t>(rs2) & 0x1F);
            break;

        case 0b111: // AND
            result = ALU::andOp(static_cast<uint32_t>(rs1), static_cast<uint32_t>(rs2));
            break;

        case 0b110: // OR
            result = ALU::orOp(static_cast<uint32_t>(rs1), static_cast<uint32_t>(rs2));
            break;

        case 0b100: // XOR
            result = ALU::xorOp(static_cast<uint32_t>(rs1), static_cast<uint32_t>(rs2));
            break;

        case 0b010: // SLT signed
            result = ALU::sltSigned(rs1, rs2);
            break;

        default:
            std::cout << "[ERRO] funct3 desconhecido no R-Type.\n";
            return;
    }

    cpu.writeReg(instr.rd, result);
}


void Executor::executeIType(const Instruction& instr, CPU& cpu) {
    int32_t imm = instr.imm;
    uint32_t rs1_u = cpu.readReg(instr.rs1);
    int32_t rs1_s = static_cast<int32_t>(rs1_u);

    uint32_t result = 0;

    switch (instr.opcode) {

        // ----------------------------------------------------
        // I-type aritmético 
        // ----------------------------------------------------
        case 0b0010011: {
            switch (instr.funct3) {
                case 0b000: // ADDI
                    result = static_cast<uint32_t>(ALU::addSigned(rs1_s, imm));
                    break;

                case 0b001: // SLLI
                    result = ALU::sllOp(static_cast<uint32_t>(rs1_s), imm & 0x1F);
                    break;

                case 0b101: // SRLI / SRAI
                    if ((imm >> 10) & 0x1)// SRAI
                        result = ALU::sraOp(rs1_s, imm & 0x1F);
                    else                         // SRLI
                        result = ALU::srlOp(static_cast<uint32_t>(rs1_s), imm & 0x1F);
                    break;

                case 0b100: // XORI
                    result = ALU::xorOp(static_cast<uint32_t>(rs1_s), static_cast<uint32_t>(imm));
                    break;

                case 0b110: // ORI
                    result = ALU::orOp(static_cast<uint32_t>(rs1_s), static_cast<uint32_t>(imm));
                    break;

                case 0b111: // ANDI
                    result = ALU::andOp(static_cast<uint32_t>(rs1_s), static_cast<uint32_t>(imm));
                    break;

                case 0b010: // SLTI (signed)
                    result = ALU::sltSigned(rs1_s, imm);
                    break;

                default:
                    std::cout << "[ERRO] funct3 desconhecido no I-Type aritmético.\n";
                    return;
            }

            cpu.writeReg(instr.rd, result);
            break;
        }

        // ----------------------------------------------------
        // LOADS 
        // ----------------------------------------------------
        case 0b0000011: {
            int64_t addr64 = static_cast<int64_t>(rs1_u) + static_cast<int64_t>(imm);
            uint32_t addr = static_cast<uint32_t>(addr64);

            switch (instr.funct3) {
                case 0b000: { // LB 
                    uint8_t b = cpu.loadByte(addr);
                    int32_t val = static_cast<int32_t>(static_cast<int8_t>(b)); 
                    cpu.writeReg(instr.rd, static_cast<uint32_t>(val));
                    break;
                }

                case 0b001: { // LH 
                    uint16_t h = cpu.loadHalf(addr);
                    int32_t val = static_cast<int32_t>(static_cast<int16_t>(h));
                    cpu.writeReg(instr.rd, static_cast<uint32_t>(val));
                    break;
                }

                case 0b010: { // LW 
                    uint32_t w = cpu.loadWord(addr);
                    cpu.writeReg(instr.rd, w);
                    break;
                }

                case 0b100: { // LBU 
                    uint8_t b = cpu.loadByte(addr);
                    cpu.writeReg(instr.rd, static_cast<uint32_t>(b));
                    break;
                }

                case 0b101: { // LHU 
                    uint16_t h = cpu.loadHalf(addr);
                    cpu.writeReg(instr.rd, static_cast<uint32_t>(h));
                    break;
                }

                default:
                    std::cout << "[ERRO] funct3 desconhecido no LOAD I-Type.\n";
                    return;
            }
            break;
        }

        // ----------------------------------------------------
        // JALR 
        // ----------------------------------------------------
        case 0b1100111: {
            uint32_t pc = cpu.getPC();
            cpu.writeReg(instr.rd, pc + 4);

            int64_t target64 = static_cast<int64_t>(rs1_u) + static_cast<int64_t>(imm);
            uint32_t target = static_cast<uint32_t>(target64) & ~static_cast<uint32_t>(1);
            cpu.setPC(target);
            break;
        }

        default:
            std::cout << "[ERRO] Opcode I-Type desconhecido.\n";
            return;
    }
}


void Executor::executeSType(const Instruction& instr, CPU& cpu) {
    uint32_t base = cpu.readReg(instr.rs1);  
    uint32_t value = cpu.readReg(instr.rs2); 
    int32_t imm = instr.imm;                  

    uint32_t addr = base + static_cast<uint32_t>(imm);               

    switch (instr.funct3) {

        case 0b000:  // SB - Store Byte
            cpu.storeByte(addr, static_cast<uint8_t>(value & 0xFF));
            break;

        case 0b001:  // SH - Store Half Word (16 bits)
            cpu.storeHalf(addr, static_cast<uint16_t>(value & 0xFFFF));
            break;

        case 0b010:  // SW - Store Word (32 bits)
            cpu.storeWord(addr, value);
            break;

        default:
            std::cout << "[ERRO] funct3 desconhecido no S-Type.\n";
            return;
    }
}

void Executor::executeBType(const Instruction& instr, CPU& cpu) {
    uint32_t rs1Val = cpu.readReg(instr.rs1);
    uint32_t rs2Val = cpu.readReg(instr.rs2);

    int32_t offset = instr.imm;      
    uint32_t pc    = cpu.getPC();    

    bool takeBranch = false;

    switch (instr.funct3)
    {
        case 0b000: // BEQ
            takeBranch = (rs1Val == rs2Val);
            break;

        case 0b001: // BNE
            takeBranch = (rs1Val != rs2Val);
            break;

        case 0b100: // BLT (signed)
            takeBranch = (static_cast<int32_t>(rs1Val) < static_cast<int32_t>(rs2Val));
            break;

        case 0b101: // BGE (signed)
            takeBranch = (static_cast<int32_t>(rs1Val) >= static_cast<int32_t>(rs2Val));
            break;

        case 0b110: // BLTU (unsigned)
            takeBranch = (rs1Val < rs2Val);
            break;

        case 0b111: // BGEU (unsigned)
            takeBranch = (rs1Val >= rs2Val);
            break;

        default:
            std::cout << "[ERRO] funct3 desconhecido no B-Type.\n";
            return;
    }

    if (takeBranch) {
        int64_t next = static_cast<int64_t>(pc) + static_cast<int64_t>(offset);
        cpu.setPC(static_cast<uint32_t>(next));
    } else {
        cpu.setPC(pc + 4);
    }
}

void Executor::executeUType(const Instruction& instr, CPU& cpu) {
    uint32_t imm = static_cast<uint32_t>(instr.imm);

    switch (instr.opcode) {

        case 0b0110111:  // LUI
            cpu.writeReg(instr.rd, imm);
            break;

        case 0b0010111:  // AUIPC
            cpu.writeReg(instr.rd, cpu.getPC() + imm);
            break;

        default:
            std::cout << "[ERRO] Opcode desconhecido no U-Type.\n";
            break;
    }
}

void Executor::executeJType(const Instruction& instr, CPU& cpu) {
    uint32_t pc = cpu.getPC();
    int32_t offset = instr.imm;
    
    cpu.writeReg(instr.rd, pc + 4);

    int64_t newPC = static_cast<int64_t>(pc) + static_cast<int64_t>(offset);
    cpu.setPC(static_cast<uint32_t>(newPC));
}


