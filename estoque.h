#ifndef ESTOQUE_H
#define ESTOQUE_H

#include "Produto.h"  // Incluindo Produto.h onde Produto é definido

class Nodo {
public:
    Produto* produto;  // Agora, é um ponteiro para Produto
    Nodo* proximo;
    Nodo* anterior;

    Nodo(Produto* produto) : produto(produto), proximo(nullptr), anterior(nullptr) {}
};


class Estoque {
public:
    Estoque();
    ~Estoque();

    void adicionarProduto(Produto* produto);
    void removerProduto(int id);
    Produto* buscarProduto(int id);
    QList<Produto*> listarProdutos();
    void ordenarProdutos();
    void ordenarPorNome();
    void ordenarPorFornecedor();
    void tratarEstoqueZero();

    // Funções adicionais para persistência
    void carregarProdutos();
    void salvarProdutos();
    int obterProximoId();

private:
    Nodo* inicio;
    Nodo* fim;
};

#endif // ESTOQUE_H
