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
            std::cout << "[ERRO] funct3 desconhecido no R-Type!\n";
            return;
    }

    cpu.writeReg(instr.rd, result);
}


void Executor::executeIType(const Instruction& instr, CPU& cpu) {
    int32_t rs1 = static_cast<int32_t>(cpu.readReg(instr.rs1));
    int32_t imm = instr.imm;  

    uint32_t result = 0;

    switch (instr.funct3) {

        case 0b000: // ADDI
            result = static_cast<uint32_t>(ALU::addSigned(rs1, imm));
            break;

        case 0b100: // XORI
            result = ALU::xorOp(static_cast<uint32_t>(rs1), static_cast<uint32_t>(imm));
            break;

        case 0b110: // ORI
            result = ALU::orOp(static_cast<uint32_t>(rs1), static_cast<uint32_t>(imm));
            break;

        case 0b111: // ANDI
            result = ALU::andOp(static_cast<uint32_t>(rs1), static_cast<uint32_t>(imm));
            break;

        case 0b010: // SLTI signed
            result = ALU::sltSigned(rs1, imm);
            break;

        default:
            std::cout << "[ERRO] funct3 desconhecido no I-Type!\n";
            return;
    }

    cpu.writeReg(instr.rd, result);
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
            std::cout << "[ERRO] funct3 desconhecido no S-Type!\n";
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
            std::cout << "[ERRO] Opcode desconhecido no U-Type!\n";
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


