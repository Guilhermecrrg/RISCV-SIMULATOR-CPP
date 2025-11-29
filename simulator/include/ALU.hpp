#ifndef ALU_HPP
#define ALU_HPP

#include <cstdint>

class ALU {
public:
    static uint32_t addOp(uint32_t a, uint32_t b);
    static uint32_t subOp(uint32_t a, uint32_t b);
    static uint32_t andOp(uint32_t a, uint32_t b);
    static uint32_t orOp(uint32_t a, uint32_t b);
    static uint32_t xorOp(uint32_t a, uint32_t b);
    static uint32_t sltOp(int32_t a, int32_t b);
};

#endif
