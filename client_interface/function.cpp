#include "function.h"

bool auth(QString login, QString password) {
    QByteArray msg;
    msg = "auth&" + login.toUtf8() + "&" + password.toUtf8() + "\r\n";
    QStringList parts = singleclient::getInstance()->send_msg_to_server(msg).split("&");
    if (parts[0] == "auth+") {
        return true;
    } else {
        return false;
    }
}
bool reg(QString login, QString password, QString email) {
    QByteArray msg;
    msg = "reg&" + login.toUtf8() + "&" + password.toUtf8() + "&" + email.toUtf8() + "\r\n";
    QStringList parts = singleclient::getInstance()->send_msg_to_server(msg).split("&");
    if (parts[0] == "reg+") {
        return true;
    } else {
        return false;
    }
}
bool check(QString variant_num, QString variant, QString result_client, QString login) {
    QByteArray msg;
    msg = "check&" + variant_num.toUtf8() + "&" + variant.toUtf8() + "&" + result_client.toUtf8() + "&" + login.toUtf8() + "\r\n";
    qDebug()<<msg;
    QStringList parts = singleclient::getInstance()->send_msg_to_server(msg).split("&");
    if (parts[0] == "check+") {
        return true;
    } else {
        return false;
    }
}
QString get_stat(QString login) {

}
QString get_task1() {

}
QString get_task2() {

}
