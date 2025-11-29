#include "../include/ALU.hpp"

uint32_t ALU::addOp(uint32_t a, uint32_t b) { return a + b; }
uint32_t ALU::subOp(uint32_t a, uint32_t b) { return a - b; }
uint32_t ALU::andOp(uint32_t a, uint32_t b) { return a & b; }
uint32_t ALU::orOp(uint32_t a, uint32_t b)  { return a | b; }
uint32_t ALU::xorOp(uint32_t a, uint32_t b) { return a ^ b; }
uint32_t ALU::sltOp(int32_t a, int32_t b)   { return (a < b) ? 1 : 0; }
