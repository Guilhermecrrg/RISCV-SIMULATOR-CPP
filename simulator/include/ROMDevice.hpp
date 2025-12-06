#ifndef ROM_DEVICE_HPP
#define ROM_DEVICE_HPP

#include "Device.hpp"
#include "Memory.hpp"
#include <vector>
#include <cstdint>

class ROMDevice : public Device {
private:
    Memory mem;
public:
    ROMDevice(const std::vector<uint8_t>& initialData);
    
    void writeByte(uint32_t addr, uint8_t value) override;
    void writeHalf(uint32_t addr, uint16_t value) override;
    void writeWord(uint32_t addr, uint32_t value) override;

    uint8_t  readByte(uint32_t addr) const override;
    uint16_t readHalf(uint32_t addr) const override;
    uint32_t readWord(uint32_t addr) const override;
};

#endif
