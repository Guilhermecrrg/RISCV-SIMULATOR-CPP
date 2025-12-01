#include "../include/UARTDevice.hpp"

void UARTDevice::writeByte(uint32_t, uint8_t value) {
    std::cout << static_cast<char>(value) << std::flush;
}
void UARTDevice::writeHalf(uint32_t, uint16_t value) {
    std::cout << static_cast<char>(value & 0xFF)
              << static_cast<char>((value >> 8) & 0xFF) << std::flush;
}
void UARTDevice::writeWord(uint32_t, uint32_t value) {
    std::cout << static_cast<char>(value & 0xFF)
              << static_cast<char>((value >> 8) & 0xFF)
              << static_cast<char>((value >> 16) & 0xFF)
              << static_cast<char>((value >> 24) & 0xFF)
              << std::flush;
}

uint8_t UARTDevice::readByte(uint32_t) const { 
    return 0; 
}

uint16_t UARTDevice::readHalf(uint32_t) const { 
    return 0; 
}

uint32_t UARTDevice::readWord(uint32_t) const { 
    return 0; 
}
