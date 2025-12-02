#pragma once

#include <cstdint>

namespace MemMap {

constexpr std::uint32_t RAM_START        = 0x00000u;
constexpr std::uint32_t RAM_END          = 0x7FFFFu;

constexpr std::uint32_t VRAM_START       = 0x80000u;
constexpr std::uint32_t VRAM_END         = 0x8FFFFu;

constexpr std::uint32_t RESERVED_START   = 0x90000u;
constexpr std::uint32_t RESERVED_END     = 0x9FBFFu;

constexpr std::uint32_t IO_START         = 0x9FC00u;
constexpr std::uint32_t IO_END           = 0x9FFFFu;

constexpr std::uint32_t RAM_SIZE         = RAM_END      - RAM_START + 1;
constexpr std::uint32_t VRAM_SIZE        = VRAM_END     - VRAM_START + 1;
constexpr std::uint32_t ADDRESS_SPACE_SZ = IO_END       - RAM_START + 1;

constexpr std::uint32_t VRAM_COLS        = 32u;
} 
