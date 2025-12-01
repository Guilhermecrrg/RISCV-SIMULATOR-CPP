#ifndef BUS_HPP
#define BUS_HPP

#include "Device.hpp"
#include <vector>
#include <cstdint>
#include <memory>

struct Region {
    uint32_t base;
    uint32_t size;
    std::shared_ptr<Device> dev;
};

class Bus {
private:
    std::vector<Region> regions;
    std::shared_ptr<Device> findDevice(uint32_t addr) const;

public:
    Bus() = default;

    void addDevice(uint32_t base, uint32_t size, std::shared_ptr<Device> dev);

    void writeByte(uint32_t addr, uint8_t value);
    void writeHalf(uint32_t addr, uint16_t value);
    void writeWord(uint32_t addr, uint32_t value);

    uint8_t  readByte(uint32_t addr) const;
    uint16_t readHalf(uint32_t addr) const;
    uint32_t readWord(uint32_t addr) const;
};

#endif
