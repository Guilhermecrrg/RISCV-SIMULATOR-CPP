#ifndef ALU_HPP
#define ALU_HPP

#include <cstdint>

class ALU {
public:
    static uint32_t xorOp(uint32_t a, uint32_t b);
    static uint32_t orOp(uint32_t a, uint32_t b);
    static uint32_t andOp(uint32_t a, uint32_t b);
    static int32_t addSigned(int32_t a, int32_t b);
    static int32_t subSigned(int32_t a, int32_t b);
    static uint32_t sltSigned(int32_t a, int32_t b);
    static uint32_t sllOp(uint32_t a, uint32_t shamt);
    static uint32_t srlOp(uint32_t a, uint32_t shamt);
    static uint32_t sraOp(int32_t a, uint32_t shamt);
};

#endif
