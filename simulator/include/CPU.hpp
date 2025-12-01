#ifndef CPU_HPP
#define CPU_HPP

#include "Register.hpp"
#include "Instruction.hpp"
#include "Bus.hpp"
#include <cstdint>
#include <cstddef>

class CPU {
private:
    Register regs;
    Bus bus;
    uint32_t pc;

public:
    // Constructor
    CPU(size_t memorySize);

    // Register
    void writeReg(size_t index, uint32_t value);
    uint32_t readReg(size_t index) const;
    void dump() const;

    // Memory by Bus
    uint8_t loadByte(uint32_t addr) const;
    uint16_t loadHalf(uint32_t addr) const;
    uint32_t loadWord(uint32_t addr) const;

    void storeByte(uint32_t addr, uint8_t value);
    void storeHalf(uint32_t addr, uint16_t value);
    void storeWord(uint32_t addr, uint32_t value);

    // PC 
    uint32_t getPC() const { return pc; }
    void setPC(uint32_t value) { pc = value; }
    void advancePC() { pc += 4; }

    // Execute
    void execute(const Instruction& instr);
};

#endif
