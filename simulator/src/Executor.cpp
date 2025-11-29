#include "../include/Executor.hpp"
#include "../include/ALU.hpp"
#include "../include/CPU.hpp"

void Executor::executeRType(const Instruction& instr, CPU& cpu) {
    uint32_t rs1Val = cpu.readReg(instr.rs1);
    uint32_t rs2Val = cpu.readReg(instr.rs2);

    uint32_t result = 0;

    switch (instr.funct3) {

        case 0x0: // ADD ou SUB
            if (instr.funct7 == 0x20)
                result = ALU::subOp(rs1Val, rs2Val);
            else
                result = ALU::addOp(rs1Val, rs2Val);
            break;

        case 0x7: // AND
            result = ALU::andOp(rs1Val, rs2Val);
            break;

        case 0x6: // OR
            result = ALU::orOp(rs1Val, rs2Val);
            break;

        case 0x4: // XOR
            result = ALU::xorOp(rs1Val, rs2Val);
            break;

        case 0x2: // SLT
            result = ALU::sltOp((int32_t)rs1Val, (int32_t)rs2Val);
            break;
    }

    cpu.writeReg(instr.rd, result);
}
