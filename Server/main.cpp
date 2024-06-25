#include <QCoreApplication>
#include "myserver.h"
#include "database.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    MyServer w;

    Database::getInstance()->executeQuery("select * from Users");
    return a.exec();
}
