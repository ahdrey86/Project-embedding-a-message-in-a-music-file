#include "database_manager.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QFile>

DatabaseManager* DatabaseManager::instance = nullptr;

DatabaseManager* DatabaseManager::getInstance() {
    if (!instance) {
        instance = new DatabaseManager();
    }
    return instance;
}

DatabaseManager::DatabaseManager(QObject *parent) : QObject(parent) {

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("user_database.db");

    if (!db.open()) {
        qDebug() << "Ошибка при открытии базы данных:" << db.lastError().text();
        return;
    }

    QSqlQuery query(db);

    // Создаем таблицу users, если она еще не создана
    QString createTableQuery = R"(
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            email TEXT NOT NULL UNIQUE,
            login TEXT NOT NULL UNIQUE,
            password TEXT NOT NULL
        )
    )";

    if (!query.exec(createTableQuery)) {
        qDebug() << "Ошибка при создании таблицы пользователей:" << query.lastError().text();
    } else {
        qDebug() << "Таблица 'users' успешно создана или уже существует.";
    }
}

bool DatabaseManager::registerUser(const QString &userData)
{
    QStringList userDataList = userData.split(';');
    if (userDataList.size() != 3) {
        qDebug() << "Ошибка: некорректный формат данных пользователя";
        return false;
    }

    QString email = userDataList[0];
    QString login = userDataList[1];
    QString passwordHash = userDataList[2];

    // Проверяем наличие такого email или логина в базе
    QSqlQuery query_check;
    query_check.prepare("SELECT COUNT(*) FROM users WHERE login = :login OR email = :email");
    query_check.bindValue(":email", email);
    query_check.bindValue(":login", login);

    // Получаем результат запроса
    query_check.next();
    if (query_check.value(0).toInt() > 0){
        qDebug() << "Ошибка при регистрации пользователя (уже существует "
                    "пользователь с такой почтой или логином:" << query_check.lastError().text();
        return false;
    }

    // Подготвливаем SQL-запрос для вставки нового пользователя в базу данных
    QSqlQuery query_reg;
    query_reg.prepare("INSERT INTO users (email, login, password) VALUES (:email, :login, :password)");
    query_reg.bindValue(":email", email);
    query_reg.bindValue(":login", login);
    query_reg.bindValue(":password", passwordHash);

    // Выполняем запрос
    if (!query_reg.exec()) {
        qDebug() << "Ошибка при регистрации пользователя:" << query_reg.lastError().text();
        return false;
    }

    qDebug() << "Пользователь успешно зарегистрирован!";
    return true;
}

bool DatabaseManager::authenticateUser(const QString &userData)
{
    QStringList userDataList = userData.split(';');
    if (userDataList.size() != 2) {
        qDebug() << "Ошибка: некорректный формат данных пользователя";
        return false;
    }

    QString login = userDataList[0];
    QString passwordHash = userDataList[1];

    // Подготавливаем SQL-запрос для проверки сущствования пользователя в базе данных
    QSqlQuery query_auth;
    query_auth.prepare("SELECT COUNT(*) FROM users WHERE login = :login AND password = :password");
    query_auth.bindValue(":login", login);
    query_auth.bindValue(":password", passwordHash);

    // Выполняем запрос
    if (!query_auth.exec()) {
        qDebug() << "Ошибка при аутентификации пользователя:" << query_auth.lastError().text();
        return false;
    }

    // Получаем результат запроса
    query_auth.next();
    int count = query_auth.value(0).toInt();

    // Если найден пользователь с указанным логином и хэшированным паролем, возвращаем true
    return (count > 0);
}
