#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <cstdint>
#include <vector>

class Memory {
private:
    std::vector<uint8_t> mem;

public:
    Memory(size_t size);

    void writeWord(uint32_t addr, uint32_t value);
    void writeHalf(uint32_t addr, uint16_t value);
    void writeByte(uint32_t addr, uint8_t value);

    uint32_t readWord(uint32_t addr) const;
    uint16_t readHalf(uint32_t addr) const;
    uint8_t  readByte(uint32_t addr) const;
};

#endif
