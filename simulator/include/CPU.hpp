#ifndef CPU_HPP
#define CPU_HPP

#include "Register.hpp"
#include "Instruction.hpp"
#include "Bus.hpp"
#include "MemoryMap.hpp"
#include "Cache.hpp"
#include "Decoder.hpp"

#include <cstdint>
#include <cstddef>

class InteractiveConsole;

class CPU { 
    friend class InteractiveConsole; 

private:
    Register regs;
    Bus bus;
    Decoder decoder;
    uint32_t pc;

    mutable Cache cache;

public:
    // Constructor
    CPU(size_t memorySize);
    bool loadProgram(const std::string& filename, uint32_t entryPoint);

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
    uint32_t fetch() const;
    void execute(const Instruction& instr);
    void run();
    
};

#endif
