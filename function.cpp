#include "function.h"
#include <cmath>
#include <sstream>
#include <iostream>
#include <iomanip>
#include "exprtk.hpp"

// Конструктор класса Function, принимает необязательный параметр parent
Function::Function(QObject *parent) : QObject(parent)
{
    // Инициализация объекта базы данных
    mDatabase = new Database();
}

// Метод для обработки входящих запросов
void Function::handleRequest(const QString &request, QTcpSocket *socket)
{
    // Проверка типа запроса и вызов соответствующего метода обработки
    if (request.startsWith("auth&")) {
        processAuthRequest(request, socket);
    } else if (request.startsWith("reg&")) {
        processRegRequest(request, socket);
    } else if (request.startsWith("newton&")) {
        processNewtonRequest(request, socket);
    } else {
        qDebug() << "Invalid request format";
        socket->write("Invalid request format\r\n");
    }
}

// Метод для обработки запросов аутентификации
void Function::processAuthRequest(const QString &request, QTcpSocket *socket)
{
    qDebug() << "Processing authentication request:" << request;
    QStringList parts = request.split("&");
    // Проверка корректности формата запроса
    if (parts.size() != 3) {
        qDebug() << "Invalid authentication request format";
        socket->write("Invalid auth request format\r\n");
        return;
    }
    QString login = parts[1];
    QString password = parts[2].trimmed();

    // Проверка авторизации пользователя
    if (mDatabase->authorizationUser(login, password)) {
        qDebug() << "Authentication successful for user:" << login;
        socket->write("auth+&success\r\n");
    } else {
        qDebug() << "Authentication failed for user:" << login;
        socket->write("auth+&fail\r\n");
    }
}

// Метод для обработки запросов регистрации
void Function::processRegRequest(const QString &request, QTcpSocket *socket)
{
    qDebug() << "Processing registration request:" << request;
    QStringList parts = request.split("&");
    // Проверка корректности формата запроса
    if (parts.size() != 4) {
        qDebug() << "Invalid registration request format";
        socket->write("Invalid reg request format\r\n");
        return;
    }
    QString login = parts[1];
    QString password = parts[2];
    QString email = parts[3].trimmed();

    // Регистрация нового пользователя
    if (mDatabase->registrationUser(login, password, email)) {
        qDebug() << "Registration successful for user:" << login;
        socket->write("reg+&success\r\n");
    } else {
        qDebug() << "Registration failed for user:" << login;
        socket->write("reg+&fail\r\n");
    }
}

// Метод для вычисления значения выражения при заданном x
double Function::evaluate_expression(const std::string& expression_str, double x) {
    typedef exprtk::symbol_table<double> symbol_table_t;
    typedef exprtk::expression<double> expression_t;
    typedef exprtk::parser<double> parser_t;

    double y = 0;
    symbol_table_t symbol_table;
    // Добавление переменной x в таблицу символов
    symbol_table.add_variable("x", x);
    symbol_table.add_constants();

    expression_t expression;
    expression.register_symbol_table(symbol_table);

    parser_t parser;
    // Компиляция выражения
    parser.compile(expression_str, expression);

    // Возвращение значения выражения
    return expression.value();
}

// Метод для нахождения корня уравнения методом Ньютона
double Function::newton_method(const std::string& f, const std::string& df, double x0, double epsilon, int max_iterations) {
    double x = x0;
    for (int i = 0; i < max_iterations; ++i) {
        double fx = evaluate_expression(f, x);
        double dfx = evaluate_expression(df, x);
        // Проверка, не слишком ли мала производная
        if (std::abs(dfx) < epsilon) {
            std::cerr << "Производная слишком близка к нулю. Метод Ньютона не применим.\n";
            return x;
        }
        double x_new = x - fx / dfx;
        // Проверка на достижение заданной точности
        if (std::abs(x_new - x) < epsilon) {
            return x_new;
        }
        x = x_new;
    }
    std::cerr << "Достигнуто максимальное количество итераций. Решение может быть неточным.\n";
    return x;
}

// Метод для обработки запросов на метод Ньютона
void Function::processNewtonRequest(const QString &request, QTcpSocket *socket)
{
    qDebug() << "Processing Newton's method request:" << request;
    QStringList parts = request.split("&");
    // Проверка корректности формата запроса
    if (parts.size() != 6) {
        qDebug() << "Invalid Newton request format";
        socket->write("Invalid Newton request format\r\n");
        return;
    }

    // Парсинг параметров
    std::string function_str = parts[1].toStdString();
    std::string derivative_str = parts[2].toStdString();
    double epsilon = parts[3].toDouble();
    int max_iterations = parts[4].toInt();
    double initial_guess = parts[5].toDouble();

    // Вызов метода Ньютона для нахождения корня
    double root = newton_method(function_str, derivative_str, initial_guess, epsilon, max_iterations);

    // Формирование строки результата
    QString result;
    result += QString("Найденный корень: %1\n").arg(root, 0, 'f', 5);

    // Отправка результата клиенту
    socket->write(result.toUtf8());
}

// Метод для проверки подключения к базе данных
bool Function::isDatabaseConnected()
{
    return mDatabase->connectToDatabase();
}

// Метод для получения логина из запроса
QString Function::getLoginFromRequest(const QString &request)
{
    QStringList parts = request.split("&");
    if (parts.size() > 1) {
        return parts[1];
    }
    return QString();
}

