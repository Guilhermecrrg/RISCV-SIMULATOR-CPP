#ifndef EXECUTOR_HPP
#define EXECUTOR_HPP

#include <cstdint>
#include "Instruction.hpp"
#include "CPU.hpp"

class Executor {
public:
    static void executeRType(const Instruction& instr, CPU& cpu);
    static void executeIType(const Instruction& instr, CPU& cpu);
    static void executeSType(const Instruction& instr, CPU& cpu);
    static void executeBType(const Instruction& instr, CPU& cpu);
    static void executeUType(const Instruction& instr, CPU& cpu);
    static void executeJType(const Instruction& instr, CPU& cpu);
};

#endif
