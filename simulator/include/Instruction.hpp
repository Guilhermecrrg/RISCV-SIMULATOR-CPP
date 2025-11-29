#ifndef INSTRUCTION_HPP
#define INSTRUCTION_HPP

#include <cstdint>

enum class InstructionType {
    R_TYPE,
    I_TYPE,
    S_TYPE,
    B_TYPE,
    U_TYPE,
    J_TYPE,
    UNKNOWN
};

struct Instruction {
    InstructionType type = InstructionType::UNKNOWN;

    uint32_t opcode = 0;
    uint32_t rd     = 0;
    uint32_t funct3 = 0;
    uint32_t rs1    = 0;
    uint32_t rs2    = 0;
    uint32_t funct7 = 0;
    int32_t imm = 0;  
};

#endif
