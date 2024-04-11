#include "connect_setup.h"
#include "ui_connect_setup.h"
#include "connection_manager.h"
#include <QMessageBox> // Для окон с ошибками
#include <QDateTime> // Для времени

ConnectSetup::ConnectSetup(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    // Подключение кнопок к сигналам
    connect(ui.pushButton_toConnect, &QPushButton::clicked, this, &ConnectSetup::handleConnectButton);
    connect(ui.pushButton_toAuth, &QPushButton::clicked, this, &ConnectSetup::emitSwitchAuthWindow);
}

void ConnectSetup::emitSwitchAuthWindow()
{
    emit switchAuthWindow();
}

ConnectSetup::~ConnectSetup()
{
}

QString ConnectSetup::getCurrentTime() const
{
    // Получение текущего времени
    QDateTime currentDateTime = QDateTime::currentDateTime();
    return currentDateTime.toString("hh:mm:ss");
}

void ConnectSetup::handleConnectButton()
{
    // Получение IP-адреса и порта
    QString ipAddress = ui.lineEdit_IPadress->text();
    QString portStr = ui.lineEdit_Port->text();

    ui.progressBar_Connection->setValue(25);

    int port = portStr.toInt();

    // Проверка, не пусты ли поля IP-адреса и порта
    if (ipAddress.isEmpty() || portStr.isEmpty()) {
        // Если поля IP-адреса или порта пустые, обнуляем статус-бар
        ui.progressBar_Connection->setValue(0);

        //Вывод сообщения о плохой попытке подключения в статус
        QString errorMessage = QString("%1. Попытка подключения провалена, не введён IP-адрес и/или порт.").arg(getCurrentTime());
        ui.textEdit_connectionStatus->append(errorMessage);

        //Вывод окна с сообщением о плохой попытке
        QMessageBox::critical(this, tr("Ошибка"), tr("Пожалуйста, введите IP-адрес и порт."));

    } else {
        // Пытаемся подключиться к серверу через ConnectionManager
        ConnectionManager* connectionManager = ConnectionManager::getInstance();
        if (!connectionManager->connectToServer(ipAddress, port)) {
            // Если подключение не удалось, выводим сообщение об ошибке
            QString errorMessage = QString("%1. Попытка подключения провалена, сервер не ответил на запрос.").arg(getCurrentTime());
            ui.textEdit_connectionStatus->append(errorMessage);

            QMessageBox::critical(this, tr("Ошибка"), tr("Не удалось подключиться к серверу."));
            ui.progressBar_Connection->setValue(0);
            return; // Выходим из метода
        }


        // Включаем кнопку toAuth
        ui.pushButton_toAuth->setEnabled(true);

        // Выводим сообщение об успешном подключении
        QString succesMessage = QString("%1. Попытка подключения успешна!").arg(getCurrentTime());
        ui.textEdit_connectionStatus->append(succesMessage);

        ui.progressBar_Connection->setValue(100);
        QMessageBox::information(this, tr("Успешное подключение"), tr("Подключение к серверу успешно!"));



        // ui.progressBar_Connection->setValue(100); // Прогресс 100%
        // ui.textEdit_connectionStatus->append("123");
    }
}


