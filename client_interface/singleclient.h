#ifndef SINGLECLIENT_H
#define SINGLECLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>
//#include "database.h" // Включаем определение класса Database
#include "sha_1.h" // Включаем определение класса SHA1

// Объявляем класс SingletonDestroyer
class SingletonDestroyer;

class singleclient : public QObject
{
    Q_OBJECT

private:
    static singleclient* p_instance; // Статический указатель на экземпляр класса
    static SingletonDestroyer destroyer; // Экземпляр класса для уничтожения
    QTcpSocket *mTcpSocket; // Сокет для обмена данными по TCP
    explicit singleclient(QObject *parent = nullptr); // Конструктор

public:
    static singleclient* getInstance(); // Получение единственного экземпляра класса
    QString send_msg_to_server(QString query); // Отправка сообщения на сервер
//    QByteArray reg(QString login, QString password); // Метод для регистрации
    ~singleclient(); // Деструктор

private slots:
    void slotReadyRead(); // Слот для обработки полученных данных от сервера
};

// Класс для уничтожения единственного экземпляра класса
class SingletonDestroyer
{
private:
    singleclient* p_instance; // Указатель на экземпляр класса
public:
    ~SingletonDestroyer(); // Деструктор
    void initialize(singleclient* p); // Инициализация указателя
};

#endif // SINGLECLIENT_H
