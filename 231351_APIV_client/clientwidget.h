#ifndef CLIENTWIDGET_H
#define CLIENTWIDGET_H

#include <QMainWindow>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class ClientWidget; }
QT_END_NAMESPACE

class ClientWidget : public QMainWindow
{
    Q_OBJECT

public:
    ClientWidget(QWidget *parent = nullptr); // Конструктор класса
    ~ClientWidget(); // Деструктор класса

private slots:
    void on_pushButton_connect_clicked(); // Слот для кнопки "Подключить"
    void on_pushButton_toSend_clicked(); // Слот для кнопки "Отправить"
    void connected(); // Слот для обработки события успешного подключения
    void disconnected(); // Слот для обработки события разрыва соединения
    void displayConnectionStatus(bool connected); // Метод для отображения статуса подключения
    void readyRead(); // Объявляем слот для обработки полученных данных от сервера

private:
    Ui::ClientWidget *ui; // Указатель на объект интерфейса
    QTcpSocket *tcpSocket; // Указатель на объект сокета
};

#endif
