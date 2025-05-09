#include "Estoque.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <algorithm> // Para std::sort

Estoque::Estoque() : inicio(nullptr), fim(nullptr) {
    carregarProdutos();
}

Estoque::~Estoque() {
    salvarProdutos();  // Salva antes de destruir para garantir persistência
    Nodo *atual = inicio;
    while (atual != nullptr) {
        Nodo *temp = atual;
        atual = atual->proximo;
        delete temp->produto;  // Libera o Produto alocado
        delete temp;
    }
}

void Estoque::carregarProdutos() {
    QFile file("estoque.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(",");
        if (fields.size() == 4) {
            int id = fields[0].toInt();
            QString nome = fields[1];
            QString fornecedor = fields[2];
            int quantidade = fields[3].toInt();

            Produto* produto = new Produto(id, nome, fornecedor, quantidade);
            adicionarProduto(produto);
        }
    }
    file.close();
}

void Estoque::salvarProdutos() {
    QFile file("estoque.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Erro", "Não foi possível salvar os produtos.");
        return;
    }

    QTextStream out(&file);
    Nodo* atual = inicio;
    while (atual != nullptr) {
        Produto* p = atual->produto;
        out << p->getId() << ","
            << p->getNome() << ","
            << p->getFornecedor() << ","
            << p->getQuantidade() << "\n";
        atual = atual->proximo;
    }
    file.close();
}

void Estoque::adicionarProduto(Produto* produto) {
    Nodo *novoNodo = new Nodo(produto);
    if (inicio == nullptr) {
        inicio = fim = novoNodo;
    } else {
        fim->proximo = novoNodo;
        novoNodo->anterior = fim;
        fim = novoNodo;
    }

    salvarProdutos();  // Salva os produtos no arquivo após adicionar um novo produto
}

int Estoque::obterProximoId() {
    int maxId = 0;
    Nodo* atual = inicio;
    while (atual != nullptr) {
        if (atual->produto->getId() > maxId) {
            maxId = atual->produto->getId();
        }
        atual = atual->proximo;
    }
    return maxId + 1;
}

void Estoque::removerProduto(int id) {
    Nodo *atual = inicio;
    while (atual != nullptr) {
        if (atual->produto->getId() == id) {
            // Se o produto a ser removido for o primeiro
            if (atual->anterior == nullptr) {
                inicio = atual->proximo;
            } else {
                atual->anterior->proximo = atual->proximo;
            }

            // Se o produto a ser removido for o último
            if (atual->proximo == nullptr) {
                fim = atual->anterior;
            } else {
                atual->proximo->anterior = atual->anterior;
            }

            delete atual->produto;
            delete atual;
            salvarProdutos();  // Salva após a remoção
            return;
        }
        atual = atual->proximo;
    }
}

Produto* Estoque::buscarProduto(int id) {
    Nodo *atual = inicio;
    while (atual != nullptr) {
        if (atual->produto->getId() == id) {
            return atual->produto;
        }
        atual = atual->proximo;
    }
    return nullptr;
}

QList<Produto*> Estoque::listarProdutos() {
    QList<Produto*> produtos;
    Nodo *atual = inicio;
    while (atual != nullptr) {
        produtos.append(atual->produto);
        atual = atual->proximo;
    }
    return produtos;
}

void Estoque::ordenarProdutos() {
    if (inicio == nullptr || inicio->proximo == nullptr) return;  // Caso a lista seja vazia ou tenha um único produto

    // Utilizando std::sort para ordenar pela quantidade de produtos
    QList<Produto*> lista = listarProdutos();
    std::sort(lista.begin(), lista.end(), [](Produto* a, Produto* b) {
        return a->getQuantidade() < b->getQuantidade();
    });

    // Recriando a lista encadeada com os produtos ordenados
    Nodo* novoInicio = nullptr;
    Nodo* novoFim = nullptr;
    for (Produto* p : lista) {
        Nodo* novoNodo = new Nodo(p);
        if (novoInicio == nullptr) {
            novoInicio = novoFim = novoNodo;
        } else {
            novoFim->proximo = novoNodo;
            novoNodo->anterior = novoFim;
            novoFim = novoNodo;
        }
    }

    // Atualiza os ponteiros de início e fim
    inicio = novoInicio;
    fim = novoFim;
}

void Estoque::ordenarPorNome() {
    if (inicio == nullptr || inicio->proximo == nullptr) return;

    QList<Produto*> lista = listarProdutos();
    std::sort(lista.begin(), lista.end(), [](Produto* a, Produto* b) {
        return a->getNome() < b->getNome();
    });

    Nodo* novoInicio = nullptr;
    Nodo* novoFim = nullptr;
    for (Produto* p : lista) {
        Nodo* novoNodo = new Nodo(p);
        if (novoInicio == nullptr) {
            novoInicio = novoFim = novoNodo;
        } else {
            novoFim->proximo = novoNodo;
            novoNodo->anterior = novoFim;
            novoFim = novoNodo;
        }
    }

    inicio = novoInicio;
    fim = novoFim;
}

void Estoque::ordenarPorFornecedor() {
    if (inicio == nullptr || inicio->proximo == nullptr) return;

    QList<Produto*> lista = listarProdutos();
    std::sort(lista.begin(), lista.end(), [](Produto* a, Produto* b) {
        return a->getFornecedor() < b->getFornecedor();
    });

    Nodo* novoInicio = nullptr;
    Nodo* novoFim = nullptr;
    for (Produto* p : lista) {
        Nodo* novoNodo = new Nodo(p);
        if (novoInicio == nullptr) {
            novoInicio = novoFim = novoNodo;
        } else {
            novoFim->proximo = novoNodo;
            novoNodo->anterior = novoFim;
            novoFim = novoNodo;
        }
    }

    inicio = novoInicio;
    fim = novoFim;
}

void Estoque::tratarEstoqueZero() {
    Nodo *atual = inicio;
    while (atual != nullptr) {
        Nodo *proximo = atual->proximo;
        if (atual->produto->getQuantidade() == 0) {
            removerProduto(atual->produto->getId());
        }
        atual = proximo;
    }
}
