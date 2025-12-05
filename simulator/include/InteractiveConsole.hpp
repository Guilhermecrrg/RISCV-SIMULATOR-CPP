#pragma once

#include <cstdint>

class CPU;

// Interface de texto para interagir com o simulador
class InteractiveConsole {
public:
    explicit InteractiveConsole(CPU& cpu);

    // Loop principal
    void run();

private:
    CPU& cpu;

    void printMenu() const;
    void showPC() const;
    void showMemoryWindow() const;
    void editMemoryWord();
};
