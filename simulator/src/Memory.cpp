#include "../include/Memory.hpp"
#include <stdexcept>

Memory::Memory(size_t size)
    : mem(size, 0)
{
}

void Memory::writeByte(uint32_t addr, uint8_t value) {
    mem.at(addr) = value;
}

void Memory::writeHalf(uint32_t addr, uint16_t value) {
    mem.at(addr)     = static_cast<uint8_t>(value & 0xFF);        
    mem.at(addr + 1) = static_cast<uint8_t>((value >> 8) & 0xFF); 
}

void Memory::writeWord(uint32_t addr, uint32_t value) {
    mem.at(addr)     = static_cast<uint8_t>(value & 0xFF);          
    mem.at(addr + 1) = static_cast<uint8_t>((value >> 8) & 0xFF);   
    mem.at(addr + 2) = static_cast<uint8_t>((value >> 16) & 0xFF);  
    mem.at(addr + 3) = static_cast<uint8_t>((value >> 24) & 0xFF);  
}

uint8_t Memory::readByte(uint32_t addr) const {
    return mem.at(addr);
}

uint16_t Memory::readHalf(uint32_t addr) const {
    return static_cast<uint16_t>(mem.at(addr))
         | static_cast<uint16_t>(mem.at(addr + 1) << 8);
}

uint32_t Memory::readWord(uint32_t addr) const {
    return static_cast<uint32_t>(mem.at(addr))
         | (static_cast<uint32_t>(mem.at(addr + 1)) << 8)
         | (static_cast<uint32_t>(mem.at(addr + 2)) << 16)
         | (static_cast<uint32_t>(mem.at(addr + 3)) << 24);
}
