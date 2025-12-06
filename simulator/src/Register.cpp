#include "../include/Register.hpp"

Register::Register() { reset(); }

void Register::reset() {
    regs.fill(0);
    regs[0] = 0;
}

void Register::write(std::size_t index, uint32_t value) {
    if (index == 0) return; 
    if (index >= regs.size()) return;
    regs[index] = value;
}

uint32_t Register::read(std::size_t index) const {
    if (index >= regs.size()) return 0;
    return regs[index];
}

void Register::dump() const {
    for (std::size_t i = 0; i < regs.size(); ++i) {
        std::cout << "x" << i << " =" << std::dec << regs[i] << std::dec << "\n";
    }
}
