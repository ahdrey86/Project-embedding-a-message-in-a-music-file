#ifndef FUNCTION_H
#define FUNCTION_H

#include <QObject>
#include <QTcpSocket>
#include "database.h"

// Класс Function для обработки различных типов запросов, наследует QObject
class Function : public QObject
{
    Q_OBJECT
public:
    // Конструктор класса, принимает необязательный параметр parent
    explicit Function(QObject *parent = nullptr);

    // Метод для обработки входящих запросов
    void handleRequest(const QString &request, QTcpSocket *socket);

    // Метод для проверки подключения к базе данных
    bool isDatabaseConnected();

private:
    // Указатель на объект базы данных
    Database *mDatabase;

    // Метод для обработки запроса аутентификации
    void processAuthRequest(const QString &request, QTcpSocket *socket);

    // Метод для обработки запроса регистрации
    void processRegRequest(const QString &request, QTcpSocket *socket);

    // Метод для обработки запроса на метод Ньютона
    void processNewtonRequest(const QString &request, QTcpSocket *socket);

    // Метод для получения логина из запроса
    QString getLoginFromRequest(const QString &request);

    // Новые методы для реализации метода Ньютона

    // Метод для вычисления значения выражения при заданном x
    double evaluate_expression(const std::string& expression_str, double x);

    // Метод для нахождения корня уравнения методом Ньютона
    double newton_method(const std::string& f, const std::string& df, double x0, double epsilon, int max_iterations);
};

#endif // FUNCTION_H
