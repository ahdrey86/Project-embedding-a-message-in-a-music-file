#include "windows_manager.h"
#include <QMessageBox>

WindowsManager::WindowsManager(QObject *parent) : QObject(parent)
{

    connectForm = new ConnectSetup();
    authForm = new auth_window();
    regForm = new register_window();
    mainForm = new client_interface();

    // Подключение сигналов к слотам
    connect(connectForm, &ConnectSetup::switchAuthWindow, this, &WindowsManager::show_auth_window);
    connect(authForm, &auth_window::switchRegisterWindow, this, &WindowsManager::show_reg_window);
    connect(regForm, &register_window::switchAuthWindow, this, &WindowsManager::show_auth_window);
    connect(authForm, &auth_window::switchClientWindow, this, &WindowsManager::show_client_window);
}

void WindowsManager::show_connect_window()
{
    connectForm->show();
    authForm->hide();
    regForm->hide();
    mainForm->hide();
}

void WindowsManager::show_auth_window()
{
    authForm->show();
    mainForm->hide();
    regForm->hide();
    connectForm->hide();
}

void WindowsManager::show_reg_window()
{
    regForm->show();
    mainForm->hide();
    authForm->hide();
    connectForm->hide();
}

void WindowsManager::show_client_window()
{
    mainForm->show();
    authForm->hide();
    regForm->hide();
    connectForm->hide();
}
