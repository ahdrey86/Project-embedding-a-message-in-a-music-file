#include "myserver.h"

MyServer::MyServer(QObject *parent) : QObject(parent)
{
    mTcpServer = new QTcpServer(this);

    connect(mTcpServer, &QTcpServer::newConnection,
            this, &MyServer::slotNewConnection);

    if (!mTcpServer->listen(QHostAddress::Any, 5555)) {
        qDebug() << "Сервер не запустился";
    } else {
        qDebug() << "Сервер запустился";
    }
}

void MyServer::slotNewConnection()
{
    QTcpSocket *newSocket = mTcpServer->nextPendingConnection();
    mTcpSockets.append(newSocket);

    connect(newSocket, &QTcpSocket::readyRead, this, &MyServer::slotServerRead);
    connect(newSocket, &QTcpSocket::disconnected, this, &MyServer::slotClientDisconnected);
}

void MyServer::slotServerRead()
{
    QTcpSocket *curr_mTcpSocket = qobject_cast<QTcpSocket*>(sender());
    if (curr_mTcpSocket)
    {
        QString request = "";
        while (curr_mTcpSocket->bytesAvailable() > 0)
        {
            request.append(curr_mTcpSocket->readAll());
        }
        qDebug()<<request;
        QByteArray response = parsing(request) + "\r\n";
        qDebug()<<response;
        curr_mTcpSocket->write(response);
    }
}

void MyServer::slotClientDisconnected()
{
    QTcpSocket *disconnectedSocket = qobject_cast<QTcpSocket*>(sender());
    if (disconnectedSocket) {
        mTcpSockets.removeOne(disconnectedSocket);
        disconnectedSocket->deleteLater();
    }
}
