#ifndef CADASTROITEMWINDOW_H
#define CADASTROITEMWINDOW_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include "Estoque.h"

class CadastroItemWindow : public QDialog {
    Q_OBJECT

public:
    explicit CadastroItemWindow(Estoque* estoque, QWidget *parent = nullptr);
    ~CadastroItemWindow();

private slots:
    void cadastrarProduto();

private:
    Estoque* estoque;
    QLineEdit *nomeEdit;
    QLineEdit *fornecedorEdit;
    QLineEdit *quantidadeEdit;
    QPushButton *cadastrarButton;

    void setupUi();
    void limparCampos();
};

#endif // CADASTROITEMWINDOW_H
