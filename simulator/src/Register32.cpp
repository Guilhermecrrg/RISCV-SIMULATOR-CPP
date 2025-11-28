#include "../include/Register32.h"

Register32::Register32() {
    regs.fill(0);
    regs[0] = 0;
}

void Register32::write(int index, uint32_t value) {
    if (index == 0) return; 
    if (index < 0 || index >= 32) return;
    regs[index] = value;
}

uint32_t Register32::read(int index) const {
    if (index < 0 || index >= 32) return 0;
    return regs[index];
}

void Register32::dump() const {
    for (int i = 0; i < 32; i++) {
        std::cout << "x" << i << " = 0x"
                  << std::hex << regs[i]
                  << std::dec << "\n";
    }
}
