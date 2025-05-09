#include "MainWindow.h"
#include <QTableWidgetItem>
#include <QHeaderView>
#include "CadastroItemWindow.h"
#include "Estoque.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QTableWidget>
#include <QPalette>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), estoque(new Estoque())
{
    cadastroWindow = new CadastroItemWindow(estoque, this);
    setupUi();
}

MainWindow::~MainWindow() {
    delete cadastroWindow;
    delete estoque;
}

void MainWindow::setupUi() {
    // Configuração da tabela de produtos
    produtosTable = new QTableWidget(this);
    produtosTable->setColumnCount(4);
    produtosTable->setHorizontalHeaderLabels({"ID", "Nome", "Fornecedor", "Quantidade"});
    produtosTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Estilo da tabela
    produtosTable->setStyleSheet("QTableWidget {"
                                 "border: 1px solid #333;"
                                 "border-radius: 5px;"
                                 "background-color: #f9f9f9;"
                                 "color: #333;"
                                 "font-size: 14px;"
                                 "}"
                                 "QHeaderView::section {"
                                 "background-color: #4CAF50;"
                                 "color: white;"
                                 "padding: 10px;"
                                 "border: 1px solid #ddd;"
                                 "}"
                                 "QTableWidget::item {"
                                 "padding: 10px;"
                                 "border-bottom: 1px solid #ddd;"
                                 "}"
                                 "QTableWidget::item:selected {"
                                 "background-color: #4CAF50;"
                                 "color: white;"
                                 "}");

    setCentralWidget(produtosTable);

    // Configuração dos botões
    cadastrarButton = new QPushButton("Cadastrar Produto", this);
    listarButton = new QPushButton("Listar Produtos", this);
    ordenarButton = new QPushButton("Ordenar Produtos", this);

    // Estilo dos botões
    cadastrarButton->setStyleSheet("QPushButton {"
                                   "background-color: #4CAF50;"
                                   "color: white;"
                                   "border: none;"
                                   "border-radius: 5px;"
                                   "padding: 10px 20px;"
                                   "font-size: 14px;"
                                   "}"
                                   "QPushButton:hover {"
                                   "background-color: #45a049;"
                                   "}");

    listarButton->setStyleSheet("QPushButton {"
                                "background-color: #4CAF50;"
                                "color: white;"
                                "border: none;"
                                "border-radius: 5px;"
                                "padding: 10px 20px;"
                                "font-size: 14px;"
                                "}"
                                "QPushButton:hover {"
                                "background-color: #45a049;"
                                "}");

    ordenarButton->setStyleSheet("QPushButton {"
                                 "background-color: #4CAF50;"
                                 "color: white;"
                                 "border: none;"
                                 "border-radius: 5px;"
                                 "padding: 10px 20px;"
                                 "font-size: 14px;"
                                 "}"
                                 "QPushButton:hover {"
                                 "background-color: #45a049;"
                                 "}");

    // Layout
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(cadastrarButton);
    layout->addWidget(listarButton);
    layout->addWidget(ordenarButton);

    QWidget *container = new QWidget();
    container->setLayout(layout);
    setMenuWidget(container);

    // Conectar sinais aos slots
    connect(cadastrarButton, &QPushButton::clicked, this, &MainWindow::onCadastroProduto);
    connect(listarButton, &QPushButton::clicked, this, &MainWindow::onListarProdutos);
    connect(ordenarButton, &QPushButton::clicked, this, &MainWindow::onOrdenarProdutos);
}

void MainWindow::onCadastroProduto() {
    cadastroWindow->show();  // Abre a janela de cadastro de produtos
}

void MainWindow::onListarProdutos() {
    listarProdutosNaTabela();  // Atualiza a tabela com os produtos cadastrados
}

void MainWindow::onOrdenarProdutos() {
    estoque->ordenarProdutos();  // Ordena os produtos conforme definido
    listarProdutosNaTabela();  // Atualiza a tabela após ordenação
}

void MainWindow::listarProdutosNaTabela() {
    produtosTable->setRowCount(0);  // Limpa a tabela

    // Adiciona produtos à tabela
    QList<Produto*> produtos = estoque->listarProdutos();  // Obtém a lista de produtos
    for (Produto* produto : produtos) {
        int row = produtosTable->rowCount();  // Obtém o número de linhas atuais
        produtosTable->insertRow(row);  // Insere uma nova linha na tabela
        produtosTable->setItem(row, 0, new QTableWidgetItem(QString::number(produto->getId())));  // ID
        produtosTable->setItem(row, 1, new QTableWidgetItem(produto->getNome()));  // Nome
        produtosTable->setItem(row, 2, new QTableWidgetItem(produto->getFornecedor()));  // Fornecedor
        produtosTable->setItem(row, 3, new QTableWidgetItem(QString::number(produto->getQuantidade())));  // Quantidade
    }
}
