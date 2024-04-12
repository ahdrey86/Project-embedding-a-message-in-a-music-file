// mytcpserver.h

#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>



class MyTcpServer : public QObject
{
    Q_OBJECT
public:
    static MyTcpServer* getInstance();
    void start();
    void stop();

signals:

private slots:
    void newConnection();
    void readyRead();

private:
    explicit MyTcpServer(QObject *parent = nullptr);
    ~MyTcpServer();

    QTcpServer *m_server;
    static MyTcpServer* instance;
};

#endif // MYTCPSERVER_H
