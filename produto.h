#ifndef PRODUTO_H
#define PRODUTO_H

#include <QString>

class Produto {
private:
    int id;
    QString nome;
    QString fornecedor;
    int quantidade;

public:
    Produto();  // Construtor padrão
    Produto(int id, const QString& nome, const QString& fornecedor, int quantidade);
    ~Produto();

    int getId() const;
    QString getNome() const;
    QString getFornecedor() const;
    int getQuantidade() const;
    void setQuantidade(int qtd);
};

#endif // PRODUTO_H
