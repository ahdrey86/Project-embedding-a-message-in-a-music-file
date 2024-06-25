#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

// Класс Database для работы с базой данных, наследует QObject
class Database : public QObject
{
    Q_OBJECT
public:
    // Конструктор класса, принимает необязательный параметр parent
    explicit Database(QObject *parent = nullptr);

    // Деструктор класса
    ~Database();

    // Метод для подключения к базе данных
    bool connectToDatabase();

    // Метод для авторизации пользователя по логину и паролю
    bool authorizationUser(const QString &login, const QString &password);

    // Метод для регистрации нового пользователя с логином, паролем и email
    bool registrationUser(const QString &login, const QString &password, const QString &email);

private:
    // Объект базы данных
    QSqlDatabase mDatabase;

    // Метод для создания таблиц в базе данных
    bool createTables();
};

#endif // DATABASE_H
