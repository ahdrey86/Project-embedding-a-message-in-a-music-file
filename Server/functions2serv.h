#ifndef FUNC_H
#define FUNC_H
#include <QByteArray>
#include <QString>
#include <QLatin1Char>
#include <QObject>
#include <QDebug>
#include "task1.h"
#include "task2.h"

QByteArray parsing(QString);
QByteArray is_auth(QString login, QString password);
QByteArray is_reg(QString login, QString password, QString email);
QByteArray get_stat(QString login);
QByteArray check_task(QString var, QString number_task, QString result_client, QString login);
#endif // FUNC_H
