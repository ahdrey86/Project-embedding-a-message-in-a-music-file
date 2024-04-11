#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class MyTcpServer : public QObject
{
    Q_OBJECT
public:
    explicit MyTcpServer(QObject *parent = nullptr);
    ~MyTcpServer();

public slots:
    void start(); // Метод для запуска сервера
    void stop(); // Метод для остановки сервера

private slots:
    void newConnection(); // Слот, вызываемый при новом входящем подключении
    void readyRead(); // Слот, вызываемый при получении данных от клиента

private:
    QTcpServer *m_server; // Объект сервера
};

#endif
