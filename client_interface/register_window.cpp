#include "register_window.h"
#include "ui_register_window.h"
#include "auth_window.h"
#include <QMessageBox>
#include <QString>
#include <QFile>
#include <QTextStream>
#include "singleclient.h" // Включаем определение класса singleclient

register_window::register_window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::register_window)
{
    ui->setupUi(this);
}

register_window::~register_window()
{
    delete ui;
}

void register_window::on_pushButton_register_clicked()
{
    // Получаем данные о пользователе из полей ввода
    QString name = ui->lineEdit_log->text();
    QString mail = ui->lineEdit_email->text();
    QString pass = ui->lineEdit_pass->text();

    // Проверяем, что все поля заполнены
    if (name.isEmpty() || mail.isEmpty() || pass.isEmpty()) {
        QMessageBox::critical(this, "Ошибка", "Пожалуйста, заполните все поля.");
        return;
    }

    // Проверяем, что введенные пароли совпадают
    QString pass2 = ui->lineEdit_pass2->text();
    if (pass != pass2) {
        QMessageBox::critical(this, "Ошибка", "Введенные пароли не совпадают.");
        return;
    }

    // Отправляем данные пользователя на сервер
    singleclient *client = singleclient::getInstance();
    QByteArray response = "Success";//client->reg(name, pass);

    // Проверяем ответ сервера
    if (response == "Success") {
        // Отображаем сообщение об успешной регистрации
        QMessageBox::information(this, "Успех", "Вы успешно зарегистрированы!");

        // Открываем окно авторизации
        auth_window *authWindow = new auth_window(this);
        authWindow->show();

        // Закрываем текущее окно регистрации
        this->close();
    } else {
        QMessageBox::critical(this, "Ошибка", "Ошибка при регистрации пользователя. Попробуйте снова.");
    }
}

void register_window::on_pushButton_back_clicked()
{
    // Создаем и отображаем окно авторизации
    auth_window *authWindow = new auth_window(this);
    authWindow->show();

    // Скрываем текущее окно регистрации
    this->hide();
}

