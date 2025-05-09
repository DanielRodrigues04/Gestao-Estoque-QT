#ifndef NO_PRODUTO_H
#define NO_PRODUTO_H

#include <QObject>
#include "no_produto.h"

class Estoque : public QObject
{
    Q_OBJECT

public:
    explicit Estoque(QObject *parent = nullptr);
    ~Estoque();

    void adicionarProduto(Produto* produto);
    bool removerProduto(int id);
    Produto* buscarProduto(int id);
    void atualizarQuantidade(int id, int novaQuantidade);
    void ordenarPorNome();
    void verificarEstoqueZero();
    void listarProdutos() const;
    void autoOrganizar(int id); // Move para o início se acessado
    void registrarMovimentacao(const QString& descricao);

private:
    NoProduto* cabeca;
    NoProduto* cauda;

    void trocarNos(NoProduto* a, NoProduto* b);
};

#endif // NO_PRODUTO_H
