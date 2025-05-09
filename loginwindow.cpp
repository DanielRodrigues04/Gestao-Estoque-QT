#include "LoginWindow.h"
#include "MainWindow.h"  // Inclusão da classe MainWindow
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QFileDialog>

LoginWindow::LoginWindow(QWidget *parent)
    : QWidget(parent)
{
    setupUi();
}

LoginWindow::~LoginWindow() {}

void LoginWindow::setupUi() {
    usernameLineEdit = new QLineEdit(this);
    passwordLineEdit = new QLineEdit(this);
    passwordLineEdit->setEchoMode(QLineEdit::Password);

    loginButton = new QPushButton("Login", this);
    cadastrarFuncionarioButton = new QPushButton("Cadastrar Funcionário", this);
    statusLabel = new QLabel(this);

    QFormLayout *formLayout = new QFormLayout();
    formLayout->addRow("Username", usernameLineEdit);
    formLayout->addRow("Password", passwordLineEdit);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(loginButton);
    mainLayout->addWidget(cadastrarFuncionarioButton);
    mainLayout->addWidget(statusLabel);

    setLayout(mainLayout);

    connect(loginButton, &QPushButton::clicked, this, &LoginWindow::onLoginClicked);
    connect(cadastrarFuncionarioButton, &QPushButton::clicked, this, &LoginWindow::onCadastrarFuncionarioClicked);
}

void LoginWindow::onLoginClicked() {
    if (!validarCredenciais()) {
        QMessageBox::warning(this, "Erro", "Credenciais inválidas.");
        return;
    }

    QMessageBox::information(this, "Sucesso", "Login bem-sucedido.");

    // Criar e abrir a janela principal após o login bem-sucedido
    MainWindow *mainWindow = new MainWindow();
    mainWindow->show();  // Exibir a janela principal
    close();  // Fechar a janela de login
}

bool LoginWindow::validarCredenciais() {
    QString username = usernameLineEdit->text();
    QString password = passwordLineEdit->text();

    QFile file("credenciais.txt");  // Arquivo de persistência de credenciais
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Erro", "Não foi possível abrir o arquivo de credenciais.");
        return false;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList credentials = line.split(",");  // Separando usuário e senha
        if (credentials.size() == 2 && credentials[0] == username && credentials[1] == password) {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}

void LoginWindow::onCadastrarFuncionarioClicked() {
    QString username = usernameLineEdit->text();
    QString password = passwordLineEdit->text();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Erro", "Por favor, preencha todos os campos.");
        return;
    }

    if (usuarioExiste(username)) {
        QMessageBox::warning(this, "Erro", "Usuário já existe.");
        return;
    }

    if (cadastrarFuncionario(username, password)) {
        QMessageBox::information(this, "Sucesso", "Funcionário cadastrado com sucesso.");
    } else {
        QMessageBox::warning(this, "Erro", "Não foi possível cadastrar o funcionário.");
    }
}

bool LoginWindow::usuarioExiste(const QString &username) {
    QFile file("credenciais.txt");  // Verificando se o usuário já existe no arquivo
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;  // Se o arquivo não existe, podemos cadastrar o usuário
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList credentials = line.split(",");
        if (credentials[0] == username) {
            file.close();
            return true;  // Usuário encontrado
        }
    }

    file.close();
    return false;
}

bool LoginWindow::cadastrarFuncionario(const QString &username, const QString &password) {
    QFile file("credenciais.txt");  // Abrindo o arquivo de credenciais para gravação
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        return false;
    }

    QTextStream out(&file);
    out << username << "," << password << "\n";  // Salvando as credenciais no arquivo
    file.close();
    return true;
}
