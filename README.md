# RISCV-SIMULATOR-CPP

Este projeto é um simulador simples da arquitetura RISC-V 32 bits (RV32I), escrito em C++.
Ele modela uma CPU com registradores, barramento, memória principal, memória de vídeo (VRAM), dispositivos de E/S mapeados em memória (UART) e uma cache de dados L1.

O objetivo é didático: permitir visualizar como instruções RV32I acessam memória, interagem com dispositivos de E/S e como a cache afeta esses acessos.

## Visão geral da arquitetura
### CPU

A CPU simulada contém:

Registradores de propósito geral.

Contador de programa (PC).

Funções de acesso à memória (leitura/escrita de byte, meia palavra e palavra).

Módulos separados para:

Decodificação de instruções (gera uma estrutura interna Instruction).

Execução de instruções (implementa a lógica de cada tipo).

São suportados os principais formatos do conjunto base RV32I:

R-TYPE

I-TYPE

S-TYPE

B-TYPE

U-TYPE

J-TYPE

### Barramento (Bus)

O barramento é responsável por:

Manter uma tabela de dispositivos mapeados em faixas de endereços.

Encaminhar cada acesso de leitura/escrita para o dispositivo correto (RAM, ROM, UART, etc.).

Detectar acessos a endereços não mapeados e sinalizar erro (exceção de “address unmapped”), o que ajuda a encontrar bugs de programa ou de configuração de memória.

Memória e dispositivos

## O simulador possui:

RAM: memória principal, onde ficam dados e, na prática, toda a faixa de endereço definida no mapa (RAM + VRAM + região reservada + IO).

ROM: região somente leitura usada para armazenar o programa de teste em RV32I.

UART: dispositivo de saída mapeado em memória, que converte escritas em caracteres exibidos no terminal do host.

Uma abstração de memória baseada em vetor de bytes, utilizada internamente pelos dispositivos.

## Cache de dados

Entre a CPU e o barramento existe uma cache de dados L1:

A CPU realiza todos os acessos de memória através da cache (e não diretamente pelo barramento).

A cache se comunica com o barramento para buscar ou gravar dados na RAM.

### Características da cache:

Cache de dados L1.

Mapeamento direto:

Cada bloco de memória só pode ficar em uma linha específica da cache.

Tamanho:

64 linhas.

16 bytes por linha.

Total de 1 KiB de cache.

Política de leitura:

A linha é carregada em caso de falta (miss) de leitura.

## Política de escrita:

Write-through: toda escrita é repassada imediatamente para a memória principal.

Em caso de falta de escrita, a linha não é automaticamente alocada; ela será carregada quando ocorrer uma leitura daquele endereço (comportamento de read-allocate e write-no-allocate em miss).

## Região cacheável:

Endereços de RAM e VRAM são cacheáveis.

Endereços da região de IO são acessados diretamente via barramento, sem passar pela cache.

## Mapa de memória

O espaço de endereçamento é definido em um cabeçalho de mapeamento (MemoryMap), com as seguintes regiões:

RAM

Início: 0x00000

Fim: 0x7FFFF

VRAM

Início: 0x80000

Fim: 0x8FFFF

Região reservada

Início: 0x90000

Fim: 0x9FBFF

IO (E/S mapeada em memória)

Início: 0x9FC00

Fim: 0x9FFFF

É definido também o tamanho total do espaço de endereçamento, do início da RAM até o final da região de IO.

## Na inicialização da CPU:

O tamanho de memória informado é ajustado (se necessário) para que, no mínimo, cubra todo esse espaço.

O barramento recebe:

Um dispositivo RAM cobrindo todo o espaço de endereços.

Um dispositivo ROM em uma faixa específica, onde o programa de teste é armazenado.

Um dispositivo UART na região de IO.

E/S programada com VRAM

O simulador demonstra E/S programada por meio da VRAM, que funciona como uma “tela de texto”:

Há um contador global de instruções executadas pela CPU.

A cada intervalo fixo de instruções (por exemplo, a cada 16 instruções), ocorre:

A varredura de toda a região de VRAM, byte a byte.

Cada byte é interpretado como caractere imprimível (ou substituído por um ponto, caso contrário).

Os caracteres são organizados em linhas, com um número fixo de colunas, e impressos no terminal.

É exibido um cabeçalho indicando após quantas instruções o dump foi feito, e um rodapé marcando o fim da VRAM.

Qualquer programa que escreva valores na faixa de endereços da VRAM gera uma representação visual desse conteúdo no terminal em forma de “tela de texto”, simulando uma saída de vídeo simples baseada em E/S programada.

## Estrutura do projeto

### Estrutura lógica (resumida):

simulator/

main.cpp: ponto de entrada do programa (loop de fetch/decode/execute).

include/:

Cabeçalhos da CPU, ALU, barramento, decodificador, executor, abstração de memória, RAM, ROM, UART, registradores, mapeamento de memória e cache.

src/:

Implementações (.cpp) correspondentes a cada componente.

.vscode/

tasks.json: configuração de build para o VS Code (chama o compilador com todos os arquivos necessários).

## Como compilar
Dependências

Compilador C++ com suporte a C++17 (ou superior), por exemplo:

g++ (Mingw-w64 / MSYS2 no Windows),

g++ ou clang em Linux.

Opcional, mas recomendado:

Visual Studio Code.

Extensão C/C++ para IntelliSense e integração com tasks.

## Compilação com VS Code

Abra a pasta do repositório no VS Code.

Tenha certeza de que o g++ está configurado no PATH.

Use o menu: Terminal → Run Build Task… e selecione a task chamada build. (cntrl + shift + b -> build)

O VS Code irá:

Compilar todos os arquivos .cpp do simulador.

Gerar um executável (por exemplo, em simulator/build/Debug/outDebug.exe), conforme configurado no tasks.json.

## Como rodar

Depois de compilar:

Abra um terminal (pode ser o terminal integrado do VS Code) ou aperte f5 no main.cpp.

Navegue até a pasta onde o executável foi gerado (por exemplo, simulator/build/Debug).

Execute o binário do simulador.

Durante a execução, você deve ver:

Saída gerada por instruções que escrevem na UART (caracteres no terminal).

Dumps periódicos da VRAM, representando o conteúdo da memória de vídeo como texto.

Fluxo de execução do simulador

O fluxo básico é:

## Inicialização

Cria-se uma instância da CPU, informando um tamanho de memória.

O tamanho é ajustado para cobrir todo o mapa de endereços.

RAM, ROM, UART, barramento e cache são configurados.

O PC é posicionado no endereço inicial do programa (por exemplo, dentro da região de ROM).

## Loop de simulação

Em cada iteração:

A CPU busca a instrução na memória usando o endereço do PC.

A instrução é decodificada.

O módulo Executor executa a instrução, alterando registradores, memória, PC e eventualmente IO.

Se a instrução não alterou o PC (não é salto/desvio), o PC é avançado para a próxima instrução.

Toda leitura/escrita passa pela cache, que decide se é um acesso com hit (cache) ou miss (acesso ao barramento e à RAM).

Interação com memória e IO

## RAM e VRAM:

Acessos são intermediados pela cache.

IO:

Acessos vão diretamente ao barramento (sem cache).

A UART traduz escritas em caracteres exibidos no terminal.

VRAM dump

Periodicamente, de acordo com o número de instruções executadas, o simulador imprime o conteúdo da VRAM no terminal, simulando uma “tela” de saída.

## Trocando o programa de teste

O programa RV32I executado pela CPU é carregado em ROM a partir de um vetor de bytes no código-fonte.

Para substituir o programa de teste:

Gere um novo programa para RV32I (por exemplo, compilando C para RV32I em um compilador adequado ou usando um assembler).

Converta as instruções para bytes em formato little-endian.

Atualize o vetor de inicialização da ROM com a nova sequência de bytes.

Recompile o simulador e execute novamente.

# [Video de apresentação do código](https://youtu.be/Zfb1D6AIhG0).
