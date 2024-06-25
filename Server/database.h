#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
#include <QtSql/QSqlDatabase>

#include <QString>
#include <QtSql/QSqlDatabase>

class Database
{
public:
    static Database* getInstance(); // Метод для получения единственного экземпляра класса
    ~Database(); // Закрытый деструктор

QStringList executeQuery(const QString &queryStr);

    // Другие методы для работы с базой данных, например, для выполнения SQL-запросов, добавления, обновления и удаления данных и т. д.

private:
    bool connect();
    void disconnect();
    bool isConnected() const;




    Database(); // Закрытый конструктор
    Database(const Database&) = delete; // Запрет копирования
    Database& operator=(const Database&) = delete; // Запрет присваивания

    static Database* instance;
    QSqlDatabase m_database;
};

#endif // DATABASE_H
