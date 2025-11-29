#include "include/CPU.hpp"
#include "include/Decoder.hpp"
#include "include/Instruction.hpp"

int main() {
    
    CPU cpu;
    Decoder dec;

    cpu.writeReg(1, 10);
    cpu.writeReg(2, 20);

    // Instrução ADD x3 = x1 + x2
    uint32_t instrWord = 0b0000000'00010'00001'000'00011'0110011;
    Instruction I = dec.decode(instrWord);

    cpu.executeR(I);

    cpu.dump();

    std::cin.get();
    return 0;
}
