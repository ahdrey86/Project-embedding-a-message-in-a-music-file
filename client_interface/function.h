#ifndef FUNCTION_H
#define FUNCTION_H
#include <QObject>
#include "singleclient.h"
#include <QDebug>

bool auth(QString login, QString password);
bool reg(QString login, QString password, QString email);
bool check(QString variant_num, QString variant, QString result_client, QString login);
QString get_stat(QString login);
QString get_task1();
QString get_task2();

#endif // FUNCTION_H
