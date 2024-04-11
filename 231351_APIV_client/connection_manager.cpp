#include "connection_manager.h"

ConnectionManager* ConnectionManager::instance = nullptr;

ConnectionManager* ConnectionManager::getInstance() {
    if (!instance) {
        instance = new ConnectionManager();
    }
    return instance;
}

ConnectionManager::ConnectionManager(QObject *parent) : QObject(parent)
{
    tcpSocket = new QTcpSocket(this);
    connect(tcpSocket, &QTcpSocket::readyRead, this, &ConnectionManager::processServerResponse);
}

bool ConnectionManager::connectToServer(const QString& ipAddress, int port)
{
    tcpSocket->connectToHost(ipAddress, port);
    return tcpSocket->waitForConnected();
}

void ConnectionManager::sendDataToServer(const QString& data)
{
    if (tcpSocket->state() == QAbstractSocket::ConnectedState) {
        tcpSocket->write(data.toUtf8());
    }
}

void ConnectionManager::sendLoginToServer(const QString& login, const QString& password)
{
    // Отправка логина и пароля на сервер
    QString data = "LP:" + login + ";" + password;
    if (tcpSocket->state() == QAbstractSocket::ConnectedState) {
        tcpSocket->write(data.toUtf8());
    }
}

bool ConnectionManager::receiveLoginResponse()
{
    // Ждем появления данных в сокете
    if (!tcpSocket->waitForReadyRead()) {
        // Если данные не появились в течение таймаута, возвращаем false
        qDebug() << "Timeout waiting for data.";
        return false;
    }

    QByteArray responseData = tcpSocket->readAll();

    //Временное решение
    QString response = QString::fromUtf8(responseData);

    if (response.trimmed() == "yes") {
        return true;
    } else if (response.trimmed() == "no") {
        return false;
    } else {
        return false;
    }
}

void ConnectionManager::processServerResponse()
{
    //QByteArray responseData = tcpSocket->readAll();
    // Обработка ответа от сервера
}
