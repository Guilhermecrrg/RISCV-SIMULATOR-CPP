#include "../include/Executor.hpp"
#include "../include/ALU.hpp"
#include "../include/CPU.hpp"

void Executor::executeRType(const Instruction& instr, CPU& cpu) {
    int32_t rs1 = static_cast<int32_t>(cpu.readReg(instr.rs1));
    int32_t rs2 = static_cast<int32_t>(cpu.readReg(instr.rs2));

    uint32_t result = 0;

    switch (instr.funct3) {

        case 0b000: // ADD/SUB
            if (instr.funct7 == 0b0100000)
                result = ALU::subSigned(rs1, rs2);
            else
                result = ALU::addSigned(rs1, rs2);
            break;

        case 0b111: // AND
            result = ALU::andOp(rs1, rs2);
            break;

        case 0b110: // OR
            result = ALU::orOp(rs1, rs2);
            break;

        case 0b100: // XOR
            result = ALU::xorOp(rs1, rs2);
            break;

        case 0b010: // SLT
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
            result = ALU::addSigned(rs1, imm);
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

        case 0b010: // SLTI
            result = ALU::sltSigned(rs1, imm);
            break;

        default:
            std::cout << "[ERRO] funct3 desconhecido no I-Type!\n";
            return;
    }

    cpu.writeReg(instr.rd, result);
}

