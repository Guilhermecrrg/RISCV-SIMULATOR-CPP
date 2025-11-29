#include "../include/ALU.hpp"

uint32_t ALU::xorOp(uint32_t a, uint32_t b) {
    return a ^ b;
}

uint32_t ALU::orOp(uint32_t a, uint32_t b) {
    return a | b;
}

uint32_t ALU::andOp(uint32_t a, uint32_t b) {
    return a & b;
}

int32_t ALU::addSigned(int32_t a, int32_t b) {
    return a + b; 
}

int32_t ALU::subSigned(int32_t a, int32_t b) {
    return a - b;
}

uint32_t ALU::sltSigned(int32_t a, int32_t b) {
    return a < b ? 1 : 0;
}
