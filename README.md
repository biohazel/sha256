# Implementação do SHA-256 em C++

Este repositório contém uma implementação do algoritmo de hash criptográfico SHA-256 em C++. Este projeto faz parte do curso Full Stack Bitcoin da Scalar School.

## Visão Geral

SHA-256 (Secure Hash Algorithm 256-bit) é uma função de hash criptográfica que recebe uma entrada e produz um valor de hash de tamanho fixo de 256 bits (32 bytes). É uma função de mão única, o que significa que é computacionalmente inviável reverter a função e recuperar a entrada original a partir do valor de hash. O SHA-256 é amplamente utilizado em várias aplicações e protocolos de segurança, incluindo o Bitcoin.

## Uso no Bitcoin

No Bitcoin, o SHA-256 é utilizado em vários componentes críticos:
1. **Mineração**: O mecanismo de prova de trabalho na mineração de Bitcoin usa hashing duplo SHA-256. Os mineradores devem encontrar um valor de hash que seja menor do que um alvo especificado, o que requer a repetição de hashing de cabeçalhos de bloco até que o valor desejado seja encontrado.
2. **Hash de Blocos**: Cada bloco na blockchain do Bitcoin possui um hash único gerado usando SHA-256. Esse hash vincula cada bloco ao anterior, formando uma cadeia segura.
3. **Hash de Transações**: As transações de Bitcoin são identificadas por um ID de transação (TXID), que é um hash SHA-256 dos dados da transação.
4. **Geração de Endereços**: Os endereços de Bitcoin são derivados de chaves públicas usando SHA-256 e hashing RIPEMD-160.

## Estrutura do Repositório

O repositório contém os seguintes arquivos:
- `main.cpp`: O arquivo principal que contém a implementação do algoritmo SHA-256 e uma demonstração de hashing da string "hello world".
- `README.md`: Este arquivo readme explicando o projeto, seu propósito e seu uso.

## Exemplo de Código

Abaixo está um exemplo de como usar a implementação do SHA-256 neste repositório:

```cpp
#include <iostream>
#include "sha256.h"

int main() {
    SHA256 sha256;
    std::string input = "hello world";
    std::string output = sha256.update(input).final();
    std::cout << "SHA-256 de \"" << input << "\" é: " << output << std::endl;
    return 0;
}
```

Para compilar e executar o exemplo, use os seguintes comandos:

```sh
g++ -o sha256 main.cpp
./sha256
```

## Explicação do Algoritmo

A implementação segue estes passos:

1. **Inicialização**: Inicializa os valores de hash e constantes.
2. **Pré-processamento**: Preenche a mensagem de entrada para garantir que seu comprimento seja congruente a 448 módulo 512, seguido pela adição do comprimento original da mensagem.
3. **Cálculo do Hash**: Processa a mensagem em blocos de 512 bits, atualizando os valores de hash com base em uma série de operações lógicas e adições constantes.
4. **Finalização**: Produz o valor final do hash.

## Curso Full Stack Bitcoin

Este projeto faz parte do curso Full Stack Bitcoin oferecido pela Scalar School. O curso abrange vários aspectos da tecnologia Bitcoin, incluindo:
- Protocolo e rede Bitcoin
- Estruturas de dados da blockchain
- Algoritmos criptográficos usados no Bitcoin
- Bitcoin Core e operações de nós
- Lightning Network e soluções de camada 2

Para mais informações sobre o curso e a Scalar School, visite o [site da Scalar School](https://www.scalarschool.org).

## Licença

Este projeto é licenciado sob a Licença MIT. Veja o arquivo LICENSE para detalhes.

## Contribuindo

Contribuições são bem-vindas! Se você tiver sugestões, relatórios de bugs ou melhorias, crie um problema ou envie um pull request.

---

# SHA-256 Implementation in C++

This repository contains an implementation of the SHA-256 cryptographic hash algorithm in C++. This project is part of the Full Stack Bitcoin course at Scalar School.

## Overview

SHA-256 (Secure Hash Algorithm 256-bit) is a cryptographic hash function that takes an input and produces a 256-bit (32-byte) fixed-size hash value. It is a one-way function, meaning it is computationally infeasible to reverse the function and retrieve the original input from the hash value. SHA-256 is widely used in various security applications and protocols, including Bitcoin.

## Usage in Bitcoin

In Bitcoin, SHA-256 is utilized in several critical components:
1. **Mining**: The proof-of-work mechanism in Bitcoin mining uses double SHA-256 hashing. Miners must find a hash value that is lower than a specified target, which requires repeatedly hashing block headers until the desired value is found.
2. **Block Hashing**: Every block in the Bitcoin blockchain has a unique hash generated using SHA-256. This hash links each block to the previous one, forming a secure chain.
3. **Transaction Hashing**: Bitcoin transactions are identified by a transaction ID (TXID), which is a SHA-256 hash of the transaction data.
4. **Address Generation**: Bitcoin addresses are derived from public keys using SHA-256 and RIPEMD-160 hashing.

## Repository Structure

The repository contains the following files:
- `main.cpp`: The main file that contains the implementation of the SHA-256 algorithm and a demonstration of hashing the string "hello world".
- `README.md`: This readme file explaining the project, its purpose, and its usage.

## Code Example

Below is an example of how to use the SHA-256 implementation in this repository:

```cpp
#include <iostream>
#include "sha256.h"

int main() {
    SHA256 sha256;
    std::string input = "hello world";
    std::string output = sha256.update(input).final();
    std::cout << "SHA-256 of \"" << input << "\" is: " << output << std::endl;
    return 0;
}
```

To compile and run the example, use the following commands:

```sh
g++ -o sha256 main.cpp
./sha256
```

## Explanation of the Algorithm

The implementation follows these steps:

1. **Initialization**: Initialize hash values and constants.
2. **Pre-processing**: Pad the input message to ensure its length is congruent to 448 modulo 512, followed by appending the original message length.
3. **Hash Computation**: Process the message in 512-bit chunks, updating the hash values based on a series of logical operations and constant additions.
4. **Finalization**: Output the final hash value.

## Full Stack Bitcoin Course

This project is part of the Full Stack Bitcoin course offered by Scalar School. The course covers various aspects of Bitcoin technology, including:
- Bitcoin protocol and network
- Blockchain data structures
- Cryptographic algorithms used in Bitcoin
- Bitcoin Core and node operations
- Lightning Network and layer-2 solutions

For more information about the course and Scalar School, please visit [Scalar School's website](https://www.scalarschool.org).

## License

This project is licensed under the MIT License. See the LICENSE file for details.

## Contributing

Contributions are welcome! If you have any suggestions, bug reports, or improvements, please create an issue or submit a pull request.
