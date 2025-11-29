#include <iostream>
#include "include\Register.hpp"

int main() {
    Register rf;

    rf.write(1, 10);
    rf.write(2, 0xDEADBEEF);
    rf.write(0, 123);  

    std::cout << "x1 = " << rf.read(1) << std::endl;
    std::cout << "x2 = 0x" << std::hex << rf.read(2) << std::endl;
    std::cout << "x0 = " << rf.read(0) << std::endl;  

    std::cout << "\nDump dos registradores:\n";
    rf.dump();

    std::cin.get();
    return 0;
}
