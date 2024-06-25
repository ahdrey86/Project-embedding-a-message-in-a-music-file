#include "database.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QSqlQuery> // Добавляем включение для класса QSqlQuery
Database* Database::instance;


Database::Database() {
    // Конструктор класса, можете инициализировать переменные здесь
}

Database::~Database() {
    // Деструктор класса, можете освободить ресурсы здесь
}

Database* Database::getInstance() {
    // Единственный экземпляр класса
    if(instance == nullptr)
    {    instance = new Database();
        instance->connect();
    }
        return instance;
}

bool Database::connect() {
    m_database = QSqlDatabase::addDatabase("QSQLITE"); // Устанавливаем тип базы данных
    m_database.setDatabaseName("example.db"); // Устанавливаем имя базы данных
    if (!m_database.open()) { // Пытаемся открыть базу данных
        qDebug() << "Error: Failed to connect to database:" << m_database.lastError().text();
        return false;
    }

    // Выполняем запрос на создание таблицы "Users"
    QSqlQuery query(m_database);
    bool success = query.exec("CREATE TABLE IF NOT EXISTS Users (id INTEGER PRIMARY KEY AUTOINCREMENT, username TEXT NOT NULL, password TEXT NOT NULL)");
    if (!success) {
        qDebug() << "Error creating table:" << query.lastError().text();
    }

    return true;
}

void Database::disconnect() {
    m_database.close(); // Закрываем соединение с базой данных
}

bool Database::isConnected() const {
    return m_database.isOpen(); // Проверяем, установлено ли соединение с базой данных
}

QStringList Database::executeQuery(const QString &queryStr) {
    QStringList result;
    QSqlQuery query(m_database);
    if (!query.exec(queryStr)) { // Выполняем запрос
        qDebug() << "Error executing query:" << query.lastError().text();
        return result;
    }

    while (query.next()) { // Получаем результаты запроса
        //поправить!!!!!!!!!
        result.append(query.value(0).toString()); // Добавляем результат в список
    }

    return result;
}
