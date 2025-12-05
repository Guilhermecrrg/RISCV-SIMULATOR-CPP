#include "CPU.hpp"
#include "MemoryMap.hpp"
#include "InteractiveConsole.hpp"

#include <iostream>
#include <iomanip>

InteractiveConsole::InteractiveConsole(CPU& cpuRef)
    : cpu(cpuRef) {}

void InteractiveConsole::printMenu() const {
    std::cout << "\n==== RISC-V SIMULATOR ====\n";
    std::cout << "1) Mostrar PC\n";
    std::cout << "2) Mostrar janela de memoria\n";
    std::cout << "3) Editar palavra na memoria\n";
    std::cout << "0) Sair\n";
    std::cout << "Opcao: ";
}

void InteractiveConsole::showPC() const {
    std::cout << "PC = 0x"
              << std::hex << cpu.pc
              << std::dec << "\n";
}

void InteractiveConsole::showMemoryWindow() const {
    std::uint32_t base = 0;
    std::uint32_t bytes = 0;

    std::cout << "\n--- JANELA DE MEMORIA ---\n";
    std::cout << "Endereco base (hex, ex: "
              << std::hex << MemMap::RAM_START
              << "): 0x";
    std::cin >> std::hex >> base;

    std::cout << "Quantidade de bytes (multiplo de 4, ex: 64): ";
    std::cin >> std::dec >> bytes;

    if (bytes == 0 || bytes % 4 != 0) {
        std::cout << "Quantidade invalida.\n";
        return;
    }

    std::cout << "\nEndereco    Valor\n";
    std::cout << "----------------------\n";

    for (std::uint32_t off = 0; off < bytes; off += 4) {
        std::uint32_t addr = base + off;

        std::uint32_t value = cpu.loadWord(addr);

        std::cout << "0x"
                  << std::setw(8) << std::setfill('0') << std::hex << addr
                  << " : 0x"
                  << std::setw(8) << std::setfill('0') << value
                  << std::dec << "\n";
    }
}

void InteractiveConsole::editMemoryWord() {
    std::uint32_t addr = 0;
    std::uint32_t value = 0;

    std::cout << "\n--- EDITAR MEMORIA ---\n";
    std::cout << "Endereco (hex): 0x";
    std::cin >> std::hex >> addr;

    std::cout << "Novo valor (hex, 32 bits): 0x";
    std::cin >> std::hex >> value;
    std::cin >> std::dec;

    cpu.storeWord(addr, value);

    std::cout << "Endereco 0x"
              << std::hex << addr
              << " atualizado para 0x"
              << value
              << std::dec << "\n";
}

void InteractiveConsole::run() {
    bool running = true;

    while (running) {
        printMenu();
        int option = -1;
        std::cin >> option;

        switch (option) {
        case 1:
            showPC();
            break;
        case 2:
            showMemoryWindow();
            break;
        case 3:
            editMemoryWord();
            break;
        case 0:
            running = false;
            break;
        default:
            std::cout << "Opcao invalida.\n";
            break;
        }
    }
}
