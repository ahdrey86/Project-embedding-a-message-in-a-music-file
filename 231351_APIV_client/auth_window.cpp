#include "auth_window.h"
#include "ui_auth_window.h"
#include <QMessageBox>

auth_window::auth_window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::auth_window)
{
    ui->setupUi(this);

    // Подключение кнопки к слоту
    connect(ui->pushButton_toLogin, &QPushButton::clicked, this, &auth_window::attemptLogin);
    connect(ui->pushButton_gotoRegistr, &QPushButton::clicked, this, &auth_window::switchToRegister);
}

auth_window::~auth_window()
{
    delete ui;
}

void auth_window::attemptLogin()
{
    // Получение логина и пароля из полей ввода
    QString login = ui->lineEdit_login->text();
    QString password = ui->lineEdit_password->text();

    // Проверка на пустые поля
    if (login.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, tr("Предупреждение"), tr("Пожалуйста, введите логин и пароль. (login - user, pass - 12345"));
        return;
    }

    // Подключение к серверу и отправка данных для входа
    if (ConnectionManager* connectionManager = ConnectionManager::getInstance()) {
        // Отправка данных на сервер
        connectionManager->sendLoginToServer(login, password);

        // Ожидание ответа от сервера и обработка ответа
        bool loginSuccessful = connectionManager->receiveLoginResponse();

        if (loginSuccessful) {
            // Обновление статуса в случае успешного входа
            ui->lineEdit_status->setText(tr("Вход выполнен успешно!"));
            emit switchClientWindow();

        } else {
            // Обновление статуса в случае неудачного входа
            ui->lineEdit_status->setText(tr("Неверный логин или пароль!"));
        }
    } else {
        QMessageBox::critical(this, tr("Ошибка"), tr("Не удалось подключиться к серверу."));
    }
}

void auth_window::switchToRegister() {
    //QMessageBox::critical(this, tr("Упс!"), tr("Эта страница еще в разработке!"));
    emit switchRegisterWindow();
}
