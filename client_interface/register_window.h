#ifndef REGISTER_WINDOW_H
#define REGISTER_WINDOW_H

#include <QDialog>

namespace Ui {
class register_window;
}

class register_window : public QDialog
{
    Q_OBJECT

public:
    explicit register_window(QWidget *parent = nullptr);
    ~register_window();
    void setUserData(const QString &name, const QString &mail, const QString &pass);
    void saveUserDataToFile();

private slots:
    void on_pushButton_register_clicked();

    void on_pushButton_back_clicked();

private:
    Ui::register_window *ui;
    QString username;
    QString email;
    QString password;
};

#endif // REGISTER_WINDOW_H
