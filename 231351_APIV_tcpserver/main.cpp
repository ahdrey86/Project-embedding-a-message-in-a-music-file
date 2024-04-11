#include <QCoreApplication>
#include "mytcpserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Создаем объект сервера
    MyTcpServer server;

    // Запускаем сервер
    server.start();

    // Обрабатываем сигналы завершения программы для корректной остановки сервера
    QObject::connect(&a, &QCoreApplication::aboutToQuit, [&server]() {
        server.stop();
    });

    return a.exec();
}
