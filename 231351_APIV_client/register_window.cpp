#include "register_window.h"
#include "ui_register_window.h"
#include <QMessageBox>

register_window::register_window(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::register_window)
{
    ui->setupUi(this);

    connect (ui->pushButton_backToLogin, &QPushButton::clicked, this, &register_window::switchToAuth);
    connect (ui->pushButton_toRegister, &QPushButton::clicked, this, &register_window::attemptRegister);
}

register_window::~register_window()
{
    delete ui;
}

void register_window::attemptRegister()
{
    QString email = ui->lineEdit_emailToReg->text();
    QString login = ui->lineEdit_loginToReg->text();
    QString password = ui->lineEdit_passToReg->text();
    QString passwordAgain = ui->lineEdit_passToRegAgain->text();

    // Проверка на пустые поля
    if (login.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, tr("Предупреждение"), tr("Пожалуйста, введите логин и пароль. (login - user, pass - 12345"));
        return;
    }

    // Проверка на равность паролей
    if (password != passwordAgain) {
        QMessageBox::critical(this, tr("Ошибка"), tr("Пароли должны совпадать"));
        return;
    }

    if (ConnectionManager* connectionManager = ConnectionManager::getInstance()) {
        // Отправка данных на сервер
        connectionManager->sendRegToServer(email, login, password);

        // Ожидание ответа от сервера и обработка ответа
        bool regSuccessful = connectionManager->receiveRegResponse();

        if (regSuccessful) {
            // Обновление статуса в случае успешной регистрации
            ui->lineEdit_serverStatus->setText(tr("Регистрация прошла успешно!"));

        } else {
            // Обновление статуса в случае неудачной регистрации
            ui->lineEdit_serverStatus->setText(tr("Ошибка регистрации!"));
        }
    } else {
        QMessageBox::critical(this, tr("Ошибка"), tr("Не удалось подключиться к серверу."));
    }

}

void register_window::switchToAuth() {
    emit switchAuthWindow();
}
