#include "CPU.hpp"
#include "Decoder.hpp"
#include "InteractiveConsole.hpp"
#include <iostream>
#include <string>

// A InteractiveConsole será a interface para interagir ou iniciar a simulação.
// Contudo, se você quiser apenas rodar o programa e ver o resultado, 
// a parte da InteractiveConsole pode ser comentada.

int main() {
    // Definimos 1 MiB (1024 * 1024 bytes) de memória para o simulador.
    // Isso é mais que suficiente para RAM, VRAM e a ROM de teste.
    const size_t MEMORY_SIZE = 0x100000u; 
    
    // 1. Inicializa o processador (CPU)
    CPU cpu(MemMap::ADDRESS_SPACE_SZ); 
    
    // 2. Inicializa o Decodificador
    Decoder decoder;
    
    // --- Configuração do Programa ---
    const std::string BINARY_FILE = "rv32ui-p-addi.hex"; 
    // O endereço de entrada deve corresponder ao endereço de mapeamento da ROM (0x1000u)
    const uint32_t ENTRY_POINT = 0x80000000u;

    // 3. Carrega o programa binário para a memória ROM e configura o PC
    if (cpu.loadProgram(BINARY_FILE, ENTRY_POINT)) {
        
        std::cout << "\n--- SIMULACAO INICIADA ---\n";

        // 4. Executa o programa
        // O loop de FDE está contido dentro de cpu.run(decoder).
        // Ele rodará até que o PC seja 0 ou uma exceção ocorra.
        cpu.run();
        
        // Exibe o estado final dos registradores
        std::cout << "\n--- REGISTRADORES FINAIS ---\n";
        cpu.dump();

    } else {
        std::cerr << "Falha ao carregar o programa. Verifique o caminho do arquivo.\n";
        std::cin.get();
        return 1;
    }
    std::cin.get();
    return 0;
}