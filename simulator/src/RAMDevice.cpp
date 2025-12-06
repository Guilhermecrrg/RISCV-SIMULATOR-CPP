#include "../include/RAMDevice.hpp"

RAMDevice::RAMDevice(size_t size) : mem(size) {}

void RAMDevice::writeByte(uint32_t addr, uint8_t value) { 
    mem.writeByte(addr, value); 
}

void RAMDevice::writeHalf(uint32_t addr, uint16_t value) { 
    mem.writeHalf(addr, value); 
}

void RAMDevice::writeWord(uint32_t addr, uint32_t value) { 
    mem.writeWord(addr, value); 
}

uint8_t  RAMDevice::readByte(uint32_t addr) const { 
    return mem.readByte(addr); 
}

uint16_t RAMDevice::readHalf(uint32_t addr) const { 
    return mem.readHalf(addr); 
}

uint32_t RAMDevice::readWord(uint32_t addr) const { 
    return mem.readWord(addr); 
}
