#include "clientwidget.h"
#include "ui_clientwidget.h"

ClientWidget::ClientWidget(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ClientWidget)
{
    ui->setupUi(this);

    // Создаем объект сокета
    tcpSocket = new QTcpSocket(this);

    // Изначально кнопка "Отправить" недоступна
    ui->pushButton_toSend->setEnabled(false);

    // Соединяем сигналы сокета с нашими слотами
    connect(tcpSocket, &QTcpSocket::connected, this, &ClientWidget::connected);
    connect(tcpSocket, &QTcpSocket::disconnected, this, &ClientWidget::disconnected);
    connect(tcpSocket, &QTcpSocket::readyRead, this, &ClientWidget::readyRead);
}

ClientWidget::~ClientWidget()
{
    delete ui;
}

void ClientWidget::on_pushButton_connect_clicked()
{
    // При нажатии на кнопку "Подключить"
    if (tcpSocket->state() == QAbstractSocket::UnconnectedState) {
        // Подключаемся к серверу
        QString ipAddress = ui->lineEdit_IP->text();
        int port = ui->lineEdit_port->text().toInt();
        tcpSocket->connectToHost(ipAddress, port);

        // Выводим сообщение о попытке подключения в статус
        ui->textEdit_Status->append("Пытаемся подключиться к серверу...");
    }
}


void ClientWidget::on_pushButton_toSend_clicked()
{
    // При нажатии на кнопку "Отправить"
    if (tcpSocket && tcpSocket->state() == QAbstractSocket::ConnectedState) {
        // Отправляем сообщение на сервер
        QString message = ui->textEdit_toSend->toPlainText();
        tcpSocket->write(message.toUtf8());
    } else {
        // Выводим сообщение об ошибке, если сервер не подключен
        ui->textEdit_Status->append("Ошибка: Сервер не подключен.");
    }
}

void ClientWidget::connected()
{
    // При успешном подключении к серверу
    //ui->textEdit_Status->append("Соединение установлено.");
    displayConnectionStatus(true); // Обновляем статус подключения
    ui->pushButton_toSend->setEnabled(true); // Делаем кнопку "Отправить" доступной
}

void ClientWidget::disconnected()
{
    // При разрыве соединения с сервером
    //ui->textEdit_Status->append("Соединение разорвано.");
    displayConnectionStatus(false);
    ui->pushButton_toSend->setEnabled(false); // Делаем кнопку "Отправить" недоступной
}

void ClientWidget::readyRead()
{
    // Получаем данные из сокета
    QByteArray responseData = tcpSocket->readAll();

    // Преобразуем данные в строку и отображаем их в текстовом поле
    QString response = QString::fromUtf8(responseData);
    ui->textEdit_toGet->append(response);
}


void ClientWidget::displayConnectionStatus(bool connected)
{
    // Отображение статуса подключения
    if (connected)
        ui->textEdit_Status->append("Соединение установлено.");
    else
        ui->textEdit_Status->append("Соединение разорвано.");
}
