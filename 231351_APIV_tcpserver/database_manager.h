#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H

#include <QObject>
#include <QSqlDatabase>

class DatabaseManager : public QObject
{
    Q_OBJECT
public:
    static DatabaseManager* getInstance();

public slots:
    bool registerUser(const QString &userData);
    bool authenticateUser(const QString &userData);

private:
    explicit DatabaseManager(QObject *parent = nullptr);
    static DatabaseManager* instance;
    QSqlDatabase db;
};

#endif // DATABASE_MANAGER_H
