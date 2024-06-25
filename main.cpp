#include <QCoreApplication>
#include "mytcpserver.h"

int main(int argc, char *argv[])
{
    // Инициализация объекта QCoreApplication, который управляет основным циклом приложения
    QCoreApplication a(argc, argv);

    // Создание и запуск объекта MyTcpServer для обработки TCP-соединений
    MyTcpServer myserv;

    // Запуск основного цикла приложения
    return a.exec();
}
