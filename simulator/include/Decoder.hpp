#ifndef DECODER_HPP
#define DECODER_HPP

#include <cstdint>
#include "Instruction.hpp"

class Decoder {
public:
    Instruction decodeR(uint32_t instructionWord);
    Instruction decodeI(uint32_t word);

};

#endif
