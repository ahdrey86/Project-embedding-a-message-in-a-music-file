#include "mytcpserver.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>

MyTcpServer::~MyTcpServer()
{
    mTcpServer->close();
}

MyTcpServer::MyTcpServer(QObject *parent) : QObject(parent), mFunction(new Function())
{
    mTcpServer = new QTcpServer(this);

    connect(mTcpServer, &QTcpServer::newConnection,
            this, &MyTcpServer::slotNewConnection);

    if (!mTcpServer->listen(QHostAddress::Any, 33333)) {
        qDebug() << "server is not started";
    } else {
        qDebug() << "server is started";

        if (!mFunction.isDatabaseConnected())
        {
            qDebug() << "Error connecting to database";
        } else {
            qDebug() << "Database connection established";

            // Вывод таблицы Users
            QSqlQuery query("SELECT * FROM Users");
            if (query.exec()) {
                qDebug() << "Users table:";
                while (query.next()) {
                    qDebug() << "ID:" << query.value(0).toInt() << ", Login:" << query.value(1).toString() << ", Password:" << query.value(2).toString() << ", Email:" << query.value(3).toString();
                }
            } else {
                qDebug() << "Error retrieving data from Users table:" << query.lastError().text();
            }
        }
    }
}

void MyTcpServer::slotNewConnection()
{
    qDebug() << "New connection established";

    QTcpSocket *curr_mTcpSocket = mTcpServer->nextPendingConnection();
    curr_mTcpSocket->write("Добро пожаловать! Пожалуйста, авторизуйтесь с помощью команды auth&login&password\r\n");
    connect(curr_mTcpSocket, &QTcpSocket::readyRead, this, &MyTcpServer::slotServerRead);
    connect(curr_mTcpSocket, &QTcpSocket::disconnected, this, &MyTcpServer::slotClientDisconnected);
    mTcpSockets.insert(curr_mTcpSocket->socketDescriptor(), curr_mTcpSocket);
}

void MyTcpServer::slotServerRead()
{
    QTcpSocket *curr_mTcpSocket = qobject_cast<QTcpSocket*>(sender());
    if (!curr_mTcpSocket)
        return;

    while (curr_mTcpSocket->canReadLine()) {
        QByteArray array = curr_mTcpSocket->readLine().trimmed();
        QString request = QString::fromUtf8(array);

        mFunction.handleRequest(request, curr_mTcpSocket);
    }
}

void MyTcpServer::slotClientDisconnected()
{
    QTcpSocket *curr_mTcpSocket = qobject_cast<QTcpSocket*>(sender());
    if (!curr_mTcpSocket)
        return;

    mTcpSockets.remove(curr_mTcpSocket->socketDescriptor());
    curr_mTcpSocket->deleteLater();
}

