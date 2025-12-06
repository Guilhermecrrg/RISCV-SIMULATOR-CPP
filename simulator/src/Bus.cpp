#include "../include/Bus.hpp"
#include <stdexcept>

std::shared_ptr<Device> Bus::findDevice(uint32_t addr) const {
    for (const auto &r : regions) {
        if (addr >= r.base && addr < r.base + r.size)
            return r.dev;
    }
    return nullptr;
}

void Bus::addDevice(uint32_t base, uint32_t size, std::shared_ptr<Device> dev) {
    regions.push_back({base, size, dev});
}

void Bus::writeByte(uint32_t addr, uint8_t value) {
    auto d = findDevice(addr);
    if (!d) throw std::out_of_range("Bus writeByte: address unmapped");
    for (const auto &r : regions) {
        if (addr >= r.base && addr < r.base + r.size) {
            d->writeByte(addr - r.base, value);
            return;
        }
    }
}

void Bus::writeHalf(uint32_t addr, uint16_t value) {
    auto d = findDevice(addr);
    if (!d) throw std::out_of_range("Bus writeHalf: address unmapped");
    for (const auto &r : regions) {
        if (addr >= r.base && addr < r.base + r.size) {
            d->writeHalf(addr - r.base, value);
            return;
        }
    }
}

void Bus::writeWord(uint32_t addr, uint32_t value) {
    auto d = findDevice(addr);
    if (!d) throw std::out_of_range("Bus writeWord: address unmapped");
    for (const auto &r : regions) {
        if (addr >= r.base && addr < r.base + r.size) {
            d->writeWord(addr - r.base, value);
            return;
        }
    }
}

uint8_t Bus::readByte(uint32_t addr) const {
    auto d = findDevice(addr);
    if (!d) throw std::out_of_range("Bus readByte: address unmapped");
    for (const auto &r : regions) {
        if (addr >= r.base && addr < r.base + r.size) {
            return d->readByte(addr - r.base);
        }
    }
    return 0;
}

uint16_t Bus::readHalf(uint32_t addr) const {
    auto d = findDevice(addr);
    if (!d) throw std::out_of_range("Bus readHalf: address unmapped");
    for (const auto &r : regions) {
        if (addr >= r.base && addr < r.base + r.size) {
            return d->readHalf(addr - r.base);
        }
    }
    return 0;
}

uint32_t Bus::readWord(uint32_t addr) const {
    auto d = findDevice(addr);
    if (!d) throw std::out_of_range("Bus readWord: address unmapped");
    for (const auto &r : regions) {
        if (addr >= r.base && addr < r.base + r.size) {
            return d->readWord(addr - r.base);
        }
    }
    return 0;
}
