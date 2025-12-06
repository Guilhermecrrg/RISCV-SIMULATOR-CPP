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

uint32_t ALU::sllOp(uint32_t a, uint32_t shamt) {
    return a << (shamt & 0x1F);  
}

uint32_t ALU::srlOp(uint32_t a, uint32_t shamt) {
    return a >> (shamt & 0x1F);  
}

uint32_t ALU::sraOp(int32_t a, uint32_t shamt) {
    return static_cast<uint32_t>(a >> (shamt & 0x1F)); 
}
