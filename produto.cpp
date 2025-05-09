#include "Produto.h"
#include <QString>

Produto::Produto() : id(0), nome(""), fornecedor(""), quantidade(0) {}

Produto::Produto(int id, const QString& nome, const QString& fornecedor, int quantidade)
    : id(id), nome(nome), fornecedor(fornecedor), quantidade(quantidade) {}

Produto::~Produto() {}

int Produto::getId() const {
    return id;
}

QString Produto::getNome() const {
    return nome;
}

QString Produto::getFornecedor() const {
    return fornecedor;
}

int Produto::getQuantidade() const {
    return quantidade;
}

void Produto::setQuantidade(int qtd) {
    quantidade = qtd;
}
