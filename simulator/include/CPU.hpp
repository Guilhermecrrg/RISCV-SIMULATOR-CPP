#ifndef CPU_HPP
#define CPU_HPP

#include "Register.hpp"
#include "Instruction.hpp"

class CPU {
private:
    Register regs;

public:
    CPU();

    //Register
    void writeReg(size_t index, uint32_t value);
    uint32_t readReg(size_t index) const;
    void dump() const;
    
    // Executor
    void execute(const Instruction& instr);   
    void executeR(const Instruction& instr);
    void executeI(const Instruction& instr);
};

#endif
