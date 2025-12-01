#include "../include/ROMDevice.hpp"
#include <stdexcept>

ROMDevice::ROMDevice(const std::vector<uint8_t>& initialData)
    : mem(initialData.size())
{
    for (size_t i = 0; i < initialData.size(); ++i) {
        mem.writeByte(static_cast<uint32_t>(i), initialData[i]);
    }
}

void ROMDevice::writeByte(uint32_t, uint8_t) { 
    throw std::runtime_error("ROM writeByte"); 
}

void ROMDevice::writeHalf(uint32_t, uint16_t) { 
    throw std::runtime_error("ROM writeHalf"); 
}

void ROMDevice::writeWord(uint32_t, uint32_t) { 
    throw std::runtime_error("ROM writeWord"); 
}

uint8_t  ROMDevice::readByte(uint32_t addr) const { 
    return mem.readByte(addr); 
}

uint16_t ROMDevice::readHalf(uint32_t addr) const { 
    return mem.readHalf(addr); 
}

uint32_t ROMDevice::readWord(uint32_t addr) const { 
    return mem.readWord(addr); 
}
