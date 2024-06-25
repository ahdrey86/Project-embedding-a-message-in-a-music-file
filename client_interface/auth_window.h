#ifndef AUTH_WINDOW_H
#define AUTH_WINDOW_H

#include <QMainWindow>
#include "menu_window.h"
#include "function.h"
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui {
class auth_window;
}
QT_END_NAMESPACE

class auth_window : public QMainWindow
{
    Q_OBJECT

public:
    auth_window(QWidget *parent = nullptr);
    ~auth_window();

private slots:
    void on_pushButton_auth_clicked();

    void on_pushButton_register_clicked();

    void on_pushButton_exit_clicked();

    void on_pushButton_change_clicked();

private:
    Ui::auth_window *ui;
    menu_window *main_ui;
};
#endif // AUTH_WINDOW_H
