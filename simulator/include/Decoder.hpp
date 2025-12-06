#ifndef DECODER_HPP
#define DECODER_HPP

#include <cstdint>
#include "Instruction.hpp"

class Decoder {
public:
    Instruction decode(uint32_t instrWord);
    Instruction decodeR(uint32_t instrWord);
    Instruction decodeI(uint32_t instrWord);
    Instruction decodeS(uint32_t instrWord);
    Instruction decodeB(uint32_t instrWord);
    Instruction decodeU(uint32_t instrWord);
    Instruction decodeJ(uint32_t instrWord);
};

#endif
