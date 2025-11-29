#include "include/CPU.hpp"
#include "include/Decoder.hpp"

int main() {
    
    //Test CPU
    CPU cpu;

    cpu.writeReg(1, 0b0000111111111111);
    cpu.writeReg(2, 0b0101010101010101);
    cpu.writeReg(3, 0b0000000000000001);
    cpu.writeReg(0, 0b0101010101001010); 

    cpu.dump();

    //Test Decoder
    Decoder decoder;

    uint32_t instr = 0x00A50533; // ADD x10, x10, x10
    Instruction decoded = decoder.decode(instr);

    decoded.dump();

    std::cin.get();
    return 0;
}
