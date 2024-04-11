#ifndef WINDOWS_MANAGER_H
#define WINDOWS_MANAGER_H

#include "connect_setup.h"
#include "auth_window.h"
#include "register_window.h"
#include "client_interface.h"

#include <QObject>

class WindowsManager: public QObject
{
    Q_OBJECT
public:
    explicit WindowsManager(QObject *parent = nullptr);

public slots:
    void show_connect_window();
    void show_auth_window();
    void show_reg_window();
    void show_client_window();

private:
    ConnectSetup * connectForm;
    auth_window * authForm;
    register_window * regForm;
    client_interface * mainForm;

};

#endif // WINDOWSMANAGER_H
