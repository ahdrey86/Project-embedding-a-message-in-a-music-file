// mytcpserver.cpp

#include "mytcpserver.h"
#include "database_manager.h"
#include <QDebug>

MyTcpServer* MyTcpServer::instance = nullptr;

MyTcpServer* MyTcpServer::getInstance() {
    if (!instance) {
        instance = new MyTcpServer();
    }
    return instance;
}

MyTcpServer::MyTcpServer(QObject *parent) : QObject(parent), m_server(new QTcpServer(this))
{
    connect(m_server, &QTcpServer::newConnection, this, &MyTcpServer::newConnection);
}

MyTcpServer::~MyTcpServer()
{
    delete m_server;
}

void MyTcpServer::start()
{
    // Проверяем, не запущен ли сервер
    if (!m_server->isListening()) {
        // Пытаемся запустить сервер на всех сетевых интерфейсах на порту 5555
        if (!m_server->listen(QHostAddress::Any, 5555)) {
            qDebug() << "Ошибка: Невозможно запустить сервер";
            return;
        }
        // Получаем IP-адрес сервера
        QString ipAddress = m_server->serverAddress().toString();
        qDebug() << "Сервер запущен на IP:" << ipAddress << "Порт:" << m_server->serverPort();
    }
}

void MyTcpServer::stop()
{
    // Проверяем, запущен ли сервер
    if (m_server->isListening()) {
        // Останавливаем сервер
        m_server->close();
        qDebug() << "Сервер остановлен";
    }
}

void MyTcpServer::newConnection()
{
    // Пока есть ожидающие подключения
    while (m_server->hasPendingConnections()) {
        // Принимаем новое подключение
        QTcpSocket *clientSocket = m_server->nextPendingConnection();
        connect(clientSocket, &QTcpSocket::readyRead, this, &MyTcpServer::readyRead);
        //Оповещение в терминал о новом подключении
        qDebug() << "Новое подключение";
    }
}

void MyTcpServer::readyRead()
{
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());
    if (clientSocket) {
        QByteArray requestData = clientSocket->readAll();
        qDebug() << "Получены данные от клиента:" << requestData;

        QString request = QString::fromUtf8(requestData);
        bool answer;

        DatabaseManager *dbManager = DatabaseManager::getInstance();
        if (request.startsWith("R_ELP:")) {
            answer = dbManager->registerUser(request.mid(6));
            if (answer) {
                clientSocket->write("REG_RESPONSE:Success");
            } else {
                clientSocket->write("REG_RESPONSE:Fail");
            }

        } else if (request.startsWith("L_LP:")){
            answer = dbManager->authenticateUser(request.mid(5));
            if (answer) {
                clientSocket->write("LOGIN_RESPONSE:Success");
            } else {
                clientSocket->write("LOGIN_RESPONSE:Fail");
            }

        } else {
            qDebug() << "Не распознан тип обращения к серверу";
        }

    }
}
