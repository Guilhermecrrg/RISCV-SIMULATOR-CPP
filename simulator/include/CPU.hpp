#ifndef CPU_HPP
#define CPU_HPP

#include "Register.hpp"

class CPU {
private:
    Register regs;

public:
    CPU();

    
    void writeReg(size_t index, uint32_t value);
    uint32_t readReg(size_t index) const;

    
    void dump() const;
};

#endif
