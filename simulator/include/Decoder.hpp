#ifndef DECODER_HPP
#define DECODER_HPP

#include <cstdint>
#include "Instruction.hpp"

class Decoder {
public:
    Instruction decode(uint32_t instructionWord);
};

#endif
