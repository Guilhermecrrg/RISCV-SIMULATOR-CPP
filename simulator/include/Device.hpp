#ifndef DEVICE_HPP
#define DEVICE_HPP

#include <cstdint>
#include <cstddef>

class Device {
public:
    virtual ~Device() = default;

    virtual void writeByte(uint32_t addr, uint8_t value) = 0;
    virtual void writeHalf(uint32_t addr, uint16_t value) = 0;
    virtual void writeWord(uint32_t addr, uint32_t value) = 0;

    virtual uint8_t  readByte(uint32_t addr) const = 0;
    virtual uint16_t readHalf(uint32_t addr) const = 0;
    virtual uint32_t readWord(uint32_t addr) const = 0;
};
#endif
