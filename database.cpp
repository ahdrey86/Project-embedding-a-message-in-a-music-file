#include "database.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QVariant>

// Конструктор класса Database, принимает необязательный параметр parent
Database::Database(QObject *parent) : QObject(parent)
{
}

// Деструктор класса Database
Database::~Database()
{
    // Закрытие соединения с базой данных, если оно открыто
    if (mDatabase.isOpen()) {
        mDatabase.close();
    }
}

// Метод для подключения к базе данных
bool Database::connectToDatabase()
{
    // Установка типа базы данных как SQLite
    mDatabase = QSqlDatabase::addDatabase("QSQLITE");
    // Указание имени файла базы данных
    mDatabase.setDatabaseName("database.db");

    // Открытие соединения с базой данных
    if (!mDatabase.open()) {
        // Вывод сообщения об ошибке, если не удалось подключиться
        qDebug() << "Failed to connect to database:" << mDatabase.lastError().text();
        return false;
    }

    // Создание таблиц в базе данных, если они не существуют
    if (!createTables()) {
        // Вывод сообщения об ошибке, если не удалось создать таблицы
        qDebug() << "Failed to create tables";
        return false;
    }

    return true;
}

// Метод для авторизации пользователя по логину и паролю
bool Database::authorizationUser(const QString &login, const QString &password)
{
    QSqlQuery query;
    // Подготовка SQL-запроса для проверки логина и пароля пользователя
    query.prepare("SELECT * FROM Users WHERE login = :login AND password = :password");
    query.bindValue(":login", login);
    query.bindValue(":password", password);

    // Выполнение SQL-запроса
    if (!query.exec()) {
        // Вывод сообщения об ошибке, если запрос не выполнен
        qDebug() << "Error executing authorization query:" << query.lastError().text();
        return false;
    }

    // Проверка наличия результатов запроса (если есть совпадение логина и пароля)
    return query.next();
}

// Метод для регистрации нового пользователя с логином, паролем и email
bool Database::registrationUser(const QString &login, const QString &password, const QString &email)
{
    QSqlQuery query;
    // Подготовка SQL-запроса для вставки нового пользователя в таблицу Users
    query.prepare("INSERT INTO Users (login, password, email) VALUES (:login, :password, :email)");
    query.bindValue(":login", login);
    query.bindValue(":password", password);
    query.bindValue(":email", email);

    // Выполнение SQL-запроса
    if (!query.exec()) {
        // Вывод сообщения об ошибке, если запрос не выполнен
        qDebug() << "Error executing registration query:" << query.lastError().text();
        return false;
    }

    return true;
}

// Метод для создания таблиц в базе данных
bool Database::createTables()
{
    QSqlQuery query;

    // Создание таблицы Users, если она не существует
    if (!query.exec("CREATE TABLE IF NOT EXISTS Users (id INTEGER PRIMARY KEY, login TEXT, password TEXT, email TEXT)")) {
        // Вывод сообщения об ошибке, если запрос не выполнен
        qDebug() << "Error creating Users table:" << query.lastError().text();
        return false;
    }

    // Создание таблицы Tasks, если она не существует
    if (!query.exec("CREATE TABLE IF NOT EXISTS Tasks (id INTEGER PRIMARY KEY, task_number INTEGER, variant INTEGER, correct_answer TEXT, question TEXT)")) {
        // Вывод сообщения об ошибке, если запрос не выполнен
        qDebug() << "Error creating Tasks table:" << query.lastError().text();
        return false;
    }

    // Создание таблицы UserStats, если она не существует
    if (!query.exec("CREATE TABLE IF NOT EXISTS UserStats (user_id INTEGER, task_number INTEGER, solved BOOLEAN, PRIMARY KEY(user_id, task_number), FOREIGN KEY(user_id) REFERENCES Users(id))")) {
        // Вывод сообщения об ошибке, если запрос не выполнен
        qDebug() << "Error creating UserStats table:" << query.lastError().text();
        return false;
    }

    return true;
}
