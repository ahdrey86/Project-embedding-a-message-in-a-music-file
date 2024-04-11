#ifndef CONNECT_SETUP_H
#define CONNECT_SETUP_H

#include <QMainWindow>
#include <QTcpSocket>
#include "ui_connect_setup.h"


QT_BEGIN_NAMESPACE
namespace Ui { class ConnectSetup; }
QT_END_NAMESPACE

class ConnectSetup : public QMainWindow
{
    Q_OBJECT

public:
    ConnectSetup(QWidget *parent = nullptr);
    ~ConnectSetup();

private slots:
    void handleConnectButton(); // Обработчик нажатия кнопки подключения
    QString getCurrentTime() const; //Получение текущего времени
    void emitSwitchAuthWindow();

private:
    Ui::connect_setup ui;
    //QTcpSocket *tcpSocket;

signals:
    void switchAuthWindow(); // Сигнал для показа окна авторизации
};

#endif // CONNECT_SETUP_H
