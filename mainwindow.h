#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QPushButton>
#include "CadastroItemWindow.h"
#include "Estoque.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onCadastroProduto();   // Exibir a janela de cadastro de produtos
    void onListarProdutos();    // Exibir a lista de produtos na tabela
    void onOrdenarProdutos();   // Ordenar os produtos

private:
    void setupUi();  // Configuração da interface gráfica
    void listarProdutosNaTabela();  // Atualiza a tabela com a lista de produtos

private:
    QTableWidget *produtosTable;
    QPushButton *cadastrarButton;
    QPushButton *listarButton;
    QPushButton *ordenarButton;

    CadastroItemWindow *cadastroWindow;
    Estoque *estoque;
};

#endif // MAINWINDOW_H
