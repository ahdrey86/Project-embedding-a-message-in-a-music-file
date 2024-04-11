#include <QApplication>
#include "windows_manager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    WindowsManager manager;

    manager.show_connect_window();

    return a.exec();
}
