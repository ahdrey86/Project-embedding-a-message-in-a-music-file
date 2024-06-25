#include "auth_window.h"
//#include "myserver.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    auth_window w;
   // MyServer server;
    w.show();
    return a.exec();
}
