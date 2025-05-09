# Sistema de Gerenciamento de Estoque

Este é um sistema de gerenciamento de estoque desenvolvido em **C++** com **Qt Framework**, utilizando **listas duplamente encadeadas** para controle interno de produtos. O sistema possui uma interface gráfica para cadastro, listagem, ordenação e persistência dos produtos em um arquivo local (`estoque.txt`).

## Funcionalidades

* ✅ Cadastro de produtos com ID automático
* ✅ Listagem dos produtos em uma tabela com visual moderno
* ✅ Ordenação por quantidade
* ✅ Armazenamento persistente dos dados em `estoque.txt`
* ✅ Interface gráfica desenvolvida com `QWidgets`
* ✅ Estrutura de dados com listas duplamente encadeadas

## Estrutura do Projeto

* `MainWindow` – Janela principal com visualização dos produtos
* `CadastroItemWindow` – Janela para cadastrar novos produtos
* `Produto` – Classe que representa um produto no estoque
* `Estoque` – Classe que gerencia a lista de produtos e manipulação de arquivos

## Requisitos

* Qt 5 ou Qt 6
* qmake ou CMake
* Compilador C++ (GCC, MSVC, Clang)

## Como Executar

1. Clone o repositório:

   ```bash
   git clone https://github.com/SeuUsuario/estoque-qt.git
   cd estoque-qt
   ```
2. Compile o projeto com Qt Creator ou via terminal:
  ```bash
  qmake && make
   ```
3. Execute o programa:
  ```bash
./estoque-qt
  ```

4. Autores
- Daniel Rodrigues RA: 2022101144
- Yuri Richter Andolfato RA :2018102376
- João Pedro Amaral 2022100255
- Yan Percegona Weiss 2022101667
