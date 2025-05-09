#include "CadastroItemWindow.h"
#include "Produto.h"
#include <QMessageBox>
#include <QVBoxLayout>  // Adicionado para resolver o erro de 'QVBoxLayout' não reconhecido
#include <QDebug>

CadastroItemWindow::CadastroItemWindow(Estoque* estoque, QWidget *parent)
    : QDialog(parent), estoque(estoque)  // Mudado de QWidget para QDialog
{
    setWindowTitle("Cadastro de Produto");
    setupUi();
}

CadastroItemWindow::~CadastroItemWindow() {}

void CadastroItemWindow::setupUi() {
    QLabel *nomeLabel = new QLabel("Nome:");
    nomeEdit = new QLineEdit();

    QLabel *fornecedorLabel = new QLabel("Fornecedor:");
    fornecedorEdit = new QLineEdit();

    QLabel *quantidadeLabel = new QLabel("Quantidade:");
    quantidadeEdit = new QLineEdit();

    cadastrarButton = new QPushButton("Cadastrar");
    connect(cadastrarButton, &QPushButton::clicked, this, &CadastroItemWindow::cadastrarProduto);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(nomeLabel);
    mainLayout->addWidget(nomeEdit);
    mainLayout->addWidget(fornecedorLabel);
    mainLayout->addWidget(fornecedorEdit);
    mainLayout->addWidget(quantidadeLabel);
    mainLayout->addWidget(quantidadeEdit);
    mainLayout->addWidget(cadastrarButton);

    setLayout(mainLayout);
}

void CadastroItemWindow::cadastrarProduto() {
    QString nome = nomeEdit->text().trimmed();
    QString fornecedor = fornecedorEdit->text().trimmed();
    int quantidade = quantidadeEdit->text().toInt();

    if (nome.isEmpty() || fornecedor.isEmpty() || quantidade <= 0) {
        QMessageBox::warning(this, "Erro", "Preencha todos os campos corretamente.");
        return;
    }

    // Gerar novo ID (simplesmente baseado no tamanho atual da lista + 1)
    int novoId = estoque->listarProdutos().size() + 1;

    Produto* novoProduto = new Produto(novoId, nome, fornecedor, quantidade);
    estoque->adicionarProduto(novoProduto);

    QMessageBox::information(this, "Sucesso", "Produto cadastrado com sucesso!");

    limparCampos();
}

void CadastroItemWindow::limparCampos() {
    nomeEdit->clear();
    fornecedorEdit->clear();
    quantidadeEdit->clear();
}
