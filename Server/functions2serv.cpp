#include "functions2serv.h"
#include "database.h"
#include <QStringList>

QByteArray parsing(QString msg_from_server)
{
    msg_from_server = msg_from_server.left(msg_from_server.length() - 2);
    QStringList parts = msg_from_server.split("&");
    qDebug() << "\n";
    if (parts.isEmpty())
        return QByteArray(); // Если запрос пустой, возвращаем пустой ответ

    QString response;

    // Обработка запросов
    if (parts[0] == "auth") {
        // Запрос на аутентификацию
        QString username = parts[1];
        QString password = parts[2];
        response = is_auth(username, password);
    } else if (parts[0] == "reg") {
        // Запрос на регистрацию
        QString username = parts[1];
        QString password = parts[2];
        QString email = parts[3];
        response = is_reg(username, password, email);
    } else if (parts[0] == "stat") {
        QString username = parts[1];
        response = get_stat(username);
    } else if (parts[0] == "check") {
        // Запрос проверки ответа на задание
        QString task_number = parts[1];
        QString variant = parts[2];
        QString answer = parts[3];
        QString username = parts[4];
        response = check_task(variant, task_number, answer, username);
    }

    return response.toUtf8();
}
QByteArray is_auth(QString login, QString password) {
    QByteArray response;
    // запрос с баззы данных
    if (login == "user" && password == "123") {
        response = "auth+&" + login.toUtf8() + "&";
    } else {
        response = "auth-&";
    }
    return response;
}
QByteArray is_reg(QString login, QString password, QString email) {
    QByteArray response;
    // запрос с баззы данных
    if (login == "user" && password == "123" && email == "1@gmail.com") {
        response = "reg+&" + login.toUtf8() + "&";
    } else {
        response = "reg-&";
    }
    return response;
}
QByteArray get_stat(QString login) {
    // Запрос статистики

    // Ваша логика для получения статистики пользователя
    //response = "stat&"+DataBase::stat(socked_ID);
    // Предположим, что статистика успешно получена
    QByteArray response = "stat+&3$6&";
    return response;
}
QByteArray check_task(QString var, QString number_task, QString result_client, QString login) {
    QString check;
    QByteArray response;
    if (number_task == "1") {
        QStringList var1 = var.split("_");
        check = newtonMethod(var1[0], var1[1], var1[2], var1[3]);
    } else if (number_task == "2") {
        // вызвать функцию на проверку 2 задания
    }
    qDebug()<<check;
    if (check == result_client) {
        response = "check+&";
        // записываем в базу данных статистику
    } else {
        response = "check-&";
    }
    return response;
}
