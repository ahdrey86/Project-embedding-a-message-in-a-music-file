#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMap>

class MyTcpServer : public QObject
{
    Q_OBJECT
public:
    explicit MyTcpServer(QObject *parent = nullptr);
    ~MyTcpServer();
public slots:
    void slotNewConnection();
    void slotClientDisconnected();
    void slotServerRead();
private:
    QTcpServer * mTcpServer;
    QMap<int, QTcpSocket*> mTcpSockets;

    void handleRequest(const QString &request, QTcpSocket *socket);
    void processAuthRequest(QTcpSocket *socket);
    void processRegRequest(QTcpSocket *socket);
    void processStatRequest(QTcpSocket *socket);
    void processCheckRequest(QTcpSocket *socket);
};

#endif // MYTCPSERVER_H
