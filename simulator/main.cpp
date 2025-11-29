#include "include/CPU.hpp"

int main() {
    CPU cpu;

    cpu.writeReg(1, 0b0000111111111111);
    cpu.writeReg(2, 0b0101010101010101);
    cpu.writeReg(3, 0b0000000000000001);
    cpu.writeReg(0, 0b0101010101001010); 

    cpu.dump();


    std::cin.get();
    return 0;
}
