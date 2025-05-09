#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QMessageBox>

class LoginWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private slots:
    void onLoginClicked();
    void onCadastrarFuncionarioClicked();  // Novo slot para cadastrar um funcionário

private:
    QLineEdit *usernameLineEdit;
    QLineEdit *passwordLineEdit;
    QPushButton *loginButton;
    QPushButton *cadastrarFuncionarioButton;  // Novo botão para cadastro de funcionário
    QLabel *statusLabel;

    void setupUi();
    bool validarCredenciais();
    bool usuarioExiste(const QString &username);  // Verificar se o usuário já existe
    bool cadastrarFuncionario(const QString &username, const QString &password);  // Cadastrar o usuário
};

#endif // LOGINWINDOW_H
