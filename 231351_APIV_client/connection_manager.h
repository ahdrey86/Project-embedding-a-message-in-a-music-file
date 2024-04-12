#ifndef CONNECTION_MANAGER_H
#define CONNECTION_MANAGER_H

#include <QObject>
#include <QTcpSocket>

class ConnectionManager : public QObject
{
    Q_OBJECT
public:
    static ConnectionManager* getInstance();
    bool connectToServer(const QString& ipAddress, int port);
    void sendDataToServer(const QString& data);
    void sendLoginToServer(const QString& login, const QString& password);
    void sendRegToServer(const QString& eMail, const QString& login, const QString& password);
    bool receiveLoginResponse();
    bool receiveRegResponse();

private slots:
    QString processServerResponse(const QString& who);

private:
    explicit ConnectionManager(QObject *parent = nullptr);
    static ConnectionManager* instance;
    QTcpSocket *tcpSocket;
};


#endif // CONNECTION_MANAGER_H
