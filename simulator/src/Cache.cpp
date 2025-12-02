#include "../include/Cache.hpp"

using namespace MemMap;

Cache::Cache(Bus* lowerBus)
    : bus(lowerBus), hits(0), misses(0)
{
    for (auto& line : lines) {
        line.valid = false;
        line.tag   = 0;
        line.data.fill(0);
    }
}

bool Cache::isCacheable(std::uint32_t addr) const {
    // Cache só para RAM + VRAM
    return addr >= RAM_START && addr <= VRAM_END;
}

void Cache::fillLine(std::uint32_t addr) const {
    if (!bus) return;

    const std::uint32_t base = lineBase(addr);
    const std::uint32_t idx  = lineIndex(addr);
    const std::uint32_t tag  = lineTag(addr);

    Line& line = const_cast<Line&>(lines[idx]);

    for (std::uint32_t i = 0; i < LINE_SIZE; ++i) {
        line.data[i] = bus->readByte(base + i);
    }

    line.valid = true;
    line.tag   = tag;
    ++misses;
}

std::uint8_t Cache::readByte(std::uint32_t addr) const {
    // Bypass para endereços não-cacheáveis
    if (!isCacheable(addr) || !bus) {
        return bus->readByte(addr);
    }

    const std::uint32_t idx  = lineIndex(addr);
    const std::uint32_t tag  = lineTag(addr);
    const std::uint32_t off  = addr % LINE_SIZE;

    Line& line = const_cast<Line&>(lines[idx]);

    if (!line.valid || line.tag != tag) {
        fillLine(addr);
    } else {
        ++hits;
    }

    return line.data[off];
}

std::uint16_t Cache::readHalf(std::uint32_t addr) const {
    // Assumindo alinhamento correto; lê via bytes para reutilizar cache
    std::uint16_t b0 = readByte(addr);
    std::uint16_t b1 = readByte(addr + 1);
    return static_cast<std::uint16_t>(b0 | (b1 << 8));
}

std::uint32_t Cache::readWord(std::uint32_t addr) const {
    std::uint32_t b0 = readByte(addr);
    std::uint32_t b1 = readByte(addr + 1);
    std::uint32_t b2 = readByte(addr + 2);
    std::uint32_t b3 = readByte(addr + 3);
    return b0 | (b1 << 8) | (b2 << 16) | (b3 << 24);
}

void Cache::writeByte(std::uint32_t addr, std::uint8_t value) const {
    if (isCacheable(addr)) {
        const std::uint32_t idx  = lineIndex(addr);
        const std::uint32_t tag  = lineTag(addr);
        const std::uint32_t off  = addr % LINE_SIZE;
        Line& line = const_cast<Line&>(lines[idx]);

        // write-allocate: se a linha correspondente já está válida e com a mesma tag, atualiza
        if (line.valid && line.tag == tag) {
            line.data[off] = value;
        }
    }

    // write-through sempre escreve na memória principal
    if (bus) {
        bus->writeByte(addr, value);
    }
}

void Cache::writeHalf(std::uint32_t addr, std::uint16_t value) const {
    writeByte(addr,     static_cast<std::uint8_t>(value & 0xFF));
    writeByte(addr + 1, static_cast<std::uint8_t>((value >> 8) & 0xFF));
}

void Cache::writeWord(std::uint32_t addr, std::uint32_t value) const {
    writeByte(addr,     static_cast<std::uint8_t>(value & 0xFF));
    writeByte(addr + 1, static_cast<std::uint8_t>((value >> 8) & 0xFF));
    writeByte(addr + 2, static_cast<std::uint8_t>((value >> 16) & 0xFF));
    writeByte(addr + 3, static_cast<std::uint8_t>((value >> 24) & 0xFF));
}
