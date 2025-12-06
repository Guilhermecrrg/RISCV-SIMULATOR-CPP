
#ifndef RAM_DEVICE_HPP
#define RAM_DEVICE_HPP

#include "Device.hpp"
#include "Memory.hpp"
#include <cstdint>

class RAMDevice : public Device {
private:
    Memory mem;
public:
    RAMDevice(size_t size);

    void writeByte(uint32_t addr, uint8_t value) override;
    void writeHalf(uint32_t addr, uint16_t value) override;
    void writeWord(uint32_t addr, uint32_t value) override;

    uint8_t  readByte(uint32_t addr) const override;
    uint16_t readHalf(uint32_t addr) const override;
    uint32_t readWord(uint32_t addr) const override;
};
#endif
