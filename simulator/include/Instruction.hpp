#ifndef INSTRUCTION_HPP
#define INSTRUCTION_HPP

#include <cstdint>
#include <iostream>

struct Instruction {
    uint32_t opcode;
    uint32_t rd;
    uint32_t funct3;
    uint32_t rs1;
    uint32_t rs2;
    uint32_t funct7;

    void dump() const {
        std::cout << "opcode: " << opcode << "\n"
                  << "rd:     " << rd << "\n"
                  << "funct3: " << funct3 << "\n"
                  << "rs1:    " << rs1 << "\n"
                  << "rs2:    " << rs2 << "\n"
                  << "funct7: " << funct7 << "\n";
    }
};

#endif
