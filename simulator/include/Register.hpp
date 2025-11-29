#ifndef REGISTER_H
#define REGISTER_H

#include <array>
#include <cstdint>
#include <cstddef>
#include <iostream>

class Register {
private:
    std::array<uint32_t, 32> regs;
public:
    Register();
    void write(std::size_t index, uint32_t value);
    uint32_t read(std::size_t index) const;
    void dump() const;
    void reset();
};

#endif
