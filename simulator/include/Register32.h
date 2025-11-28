#ifndef REGISTER32_H
#define REGISTER32_H

#include <cstdint>
#include <array>
#include <iostream>

class Register32 {
private:
    std::array<uint32_t, 32> regs;

public:
    Register32();

    void write(int index, uint32_t value);
    uint32_t read(int index) const;

    void dump() const;
};

#endif
