#include "connection_manager.h"
#include <QCryptographicHash>

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
    connect(tcpSocket, &QTcpSocket::readyRead, this, [=]() {
        this->processServerResponse("S");
    });
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
    //Хэширование пароля
    QByteArray passwordHash = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha1);
    QString hashedPassword = QString::fromLatin1(passwordHash.toHex());
    // Отправка логина и пароля на сервер
    QString data = "L_LP:" + login + ";" + hashedPassword;
    if (tcpSocket->state() == QAbstractSocket::ConnectedState) {
        tcpSocket->write(data.toUtf8());
    }
}

void ConnectionManager::sendRegToServer(const QString& eMail, const QString& login, const QString& password)
{
    //Хэширование пароля
    QByteArray passwordHash = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha1);
    QString hashedPassword = QString::fromLatin1(passwordHash.toHex());
    // Отправка почты, логина и пароля на сервер
    QString data = "R_ELP:" + eMail + ";" + login + ";" + hashedPassword;
    if (tcpSocket->state() == QAbstractSocket::ConnectedState) {
        tcpSocket->write(data.toUtf8());
    }
}

QString ConnectionManager::processServerResponse(const QString& who)
{
    // Ждем появления данных в сокете
    if (!tcpSocket->waitForReadyRead(5000)) {
        // Если данные не появились в течение таймаута, выводим сообщение об ошибке и выходим
        qDebug() << "Timeout waiting for data.";
        return "Timeout";
    }

    QByteArray responseData = tcpSocket->readAll();

    // Преобразуем ответ в строку
    QString response = QString::fromUtf8(responseData);

    // Обработка ответа в зависимости от его содержания
    if (response.startsWith("LOGIN_RESPONSE:") && who.trimmed() == "L") {
        return response.mid(15);
    } else if (response.startsWith("REG_RESPONSE:") && who.trimmed() == "R") {
        return response.mid(15);
    } else {
        return "Missed";
    }
}

bool ConnectionManager::receiveLoginResponse()
{
    QString response = processServerResponse("L");
    if (response.trimmed() == "Success")
        return true;
    else
        return false;
}

bool ConnectionManager::receiveRegResponse() {
    QString response = processServerResponse("R");
    if (response.trimmed() == "Success")
        return true;
    else
        return false;
}


