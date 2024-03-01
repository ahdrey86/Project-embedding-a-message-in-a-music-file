#include "mytcpserver.h"
#include <QDebug>
#include <QCoreApplication>

MyTcpServer::~MyTcpServer()
{
    mTcpServer->close();
}

MyTcpServer::MyTcpServer(QObject *parent) : QObject(parent)
{
    mTcpServer = new QTcpServer(this);

    connect(mTcpServer, &QTcpServer::newConnection,
            this, &MyTcpServer::slotNewConnection);

    if (!mTcpServer->listen(QHostAddress::Any, 33333)) {
        qDebug() << "server is not started";
    } else {
        qDebug() << "server is started";
    }
}

void MyTcpServer::slotNewConnection()
{
    QTcpSocket *curr_mTcpSocket = mTcpServer->nextPendingConnection();
    curr_mTcpSocket->write("Hello, World!!! I am echo server!\r\n");
    connect(curr_mTcpSocket, &QTcpSocket::readyRead, this, &MyTcpServer::slotServerRead);
    connect(curr_mTcpSocket, &QTcpSocket::disconnected, this, &MyTcpServer::slotClientDisconnected);
    mTcpSockets.insert(curr_mTcpSocket->socketDescriptor(), curr_mTcpSocket);
}

void MyTcpServer::slotServerRead()
{
    QTcpSocket *curr_mTcpSocket = qobject_cast<QTcpSocket*>(sender());
    if (!curr_mTcpSocket)
        return;

    QByteArray array = curr_mTcpSocket->readAll();
    QString request = QString::fromUtf8(array).trimmed(); // Преобразуем в строку и удаляем лишние пробелы

    // Анализ и обработка запроса
    handleRequest(request, curr_mTcpSocket);
}

void MyTcpServer::handleRequest(const QString &request, QTcpSocket *socket)
{
    if (request.startsWith("auth&")) {
        processAuthRequest(socket);
    } else if (request.startsWith("reg&")) {
        processRegRequest(socket);
    } else if (request.startsWith("stat&")) {
        processStatRequest(socket);
    } else if (request.startsWith("check&")) {
        processCheckRequest(socket);
    } else {
        // В случае неправильного формата запроса
        socket->write("Invalid request format");
    }
}

void MyTcpServer::processAuthRequest(QTcpSocket *socket)
{

    socket->write("auth+&username");
}

void MyTcpServer::processRegRequest(QTcpSocket *socket)
{

    socket->write("reg+&username");
}

void MyTcpServer::processStatRequest(QTcpSocket *socket)
{

    socket->write("stat&3$6&21");
}

void MyTcpServer::processCheckRequest(QTcpSocket *socket)
{

    socket->write("check+");
}

void MyTcpServer::slotClientDisconnected()
{
    QTcpSocket *curr_mTcpSocket = qobject_cast<QTcpSocket*>(sender());
    if (!curr_mTcpSocket)
        return;

    mTcpSockets.remove(curr_mTcpSocket->socketDescriptor());
    curr_mTcpSocket->deleteLater();
}

