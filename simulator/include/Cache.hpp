#pragma once

#include <cstdint>
#include <array>
#include "Bus.hpp"
#include "MemoryMap.hpp"

class Cache {
public:
    // Tamanho de linha e número de linhas
    static constexpr std::uint32_t LINE_SIZE  = 16;
    static constexpr std::uint32_t NUM_LINES  = 64;

    explicit Cache(Bus* lowerBus);

    // Leitura
    std::uint8_t  readByte (std::uint32_t addr) const;
    std::uint16_t readHalf (std::uint32_t addr) const;
    std::uint32_t readWord (std::uint32_t addr) const;

    // Escrita
    void writeByte (std::uint32_t addr, std::uint8_t  value) const;
    void writeHalf (std::uint32_t addr, std::uint16_t value) const;
    void writeWord (std::uint32_t addr, std::uint32_t value) const;

    std::uint64_t getHits()   const { return hits; }
    std::uint64_t getMisses() const { return misses; }

private:
    struct Line {
        bool valid;
        std::uint32_t tag;
        std::array<std::uint8_t, LINE_SIZE> data;
    };

    Bus* bus;  // nível abaixo (RAM via Bus)
    mutable std::array<Line, NUM_LINES> lines;
    mutable std::uint64_t hits;
    mutable std::uint64_t misses;

    bool isCacheable(std::uint32_t addr) const;
    void fillLine(std::uint32_t addr) const;

    static std::uint32_t lineIndex(std::uint32_t addr) {
        return (addr / LINE_SIZE) % NUM_LINES;
    }

    static std::uint32_t lineTag(std::uint32_t addr) {
        return (addr / LINE_SIZE) / NUM_LINES;
    }

    static std::uint32_t lineBase(std::uint32_t addr) {
        return (addr / LINE_SIZE) * LINE_SIZE;
    }
};
