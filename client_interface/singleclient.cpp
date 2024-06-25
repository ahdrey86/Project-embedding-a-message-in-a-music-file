#include "singleclient.h"
#include "sha_1.h" // Включаем определение класса SHA1

singleclient* singleclient::p_instance = nullptr; // Инициализация статического указателя
SingletonDestroyer singleclient::destroyer; // Создание экземпляра класса для уничтожения

singleclient::singleclient(QObject *parent) : QObject(parent)
{
    mTcpSocket = new QTcpSocket(this);
    mTcpSocket->connectToHost("127.0.0.1", 5555); // Подключение к серверу

    connect(mTcpSocket, SIGNAL(readyRead()),
            this, SLOT(slotReadyRead())); // Подключение слота к сигналу готовности к чтению
}

singleclient* singleclient::getInstance() {
    if (!p_instance){
        p_instance = new singleclient(); // Создаем экземпляр класса
        destroyer.initialize(p_instance); // Инициализируем экземпляр для уничтожения
    }
    return p_instance; // Возвращаем указатель на экземпляр класса
}

QString singleclient::send_msg_to_server(QString query) {
    mTcpSocket->write(query.toUtf8()); // Отправляем запрос на сервер
    mTcpSocket->waitForReadyRead(); // Ожидаем ответ
    QString msg = "";
    while (mTcpSocket->bytesAvailable()>0) {
        QByteArray array = mTcpSocket->readAll(); // Читаем данные
        msg.append(array);
    }
    return msg; // Возвращаем ответ
}

/*
QByteArray singleclient::reg(QString login, QString password) {
    SHA1 sha1; // Создаем экземпляр класса для хеширования
    std::string sha_password = sha1.calculatePasswordHash(password.toStdString()); // Хешируем пароль
    password = QString::fromUtf8(sha_password.c_str()); // Переводим в строку

    QString query = QString("INSERT INTO Users (username, password) VALUES ('%1', '%2');").arg(login, password); // Формируем SQL-запрос

    // Отправляем запрос на сервер для регистрации
    QString response = send_msg_to_server(query);

    // Проверяем ответ сервера
    if (response == "Success") {
        // Если регистрация прошла успешно, сохраняем данные в локальную базу данных
        Database *db = &Database::getInstance(); // Получаем единственный экземпляр класса Database
        if (db->connect()) {
            // Выполняем запрос к локальной базе данных для сохранения данных
            QStringList result = db->executeQuery(query, false);
            if (result.isEmpty()) {
                qDebug() << "Ошибка сохранения данных пользователя в локальной базе данных";
            } else {
                qDebug() << "Данные пользователя успешно сохранены в локальной базе данных";
            }
            db->disconnect(); // Закрываем соединение с локальной базой данных
        } else {
            qDebug() << "Ошибка соединения с локальной базой данных";
        }
    }

    return response.toUtf8(); // Возвращаем ответ
}
*/
void singleclient::slotReadyRead() {
    // Обработка полученных данных от сервера
}

singleclient::~singleclient()
{
    mTcpSocket->close(); // Закрываем соединение
    delete mTcpSocket; // Удаляем сокет
}

// Реализация деструктора SingletonDestroyer
SingletonDestroyer::~SingletonDestroyer() {
    delete p_instance; // Удаляем экземпляр класса
}

// Инициализация указателя на экземпляр класса
void SingletonDestroyer::initialize(singleclient* p) {
    p_instance = p; // Присваиваем указатель на экземпляр класса
}
