#ifndef MENU_WINDOW_H
#define MENU_WINDOW_H

#include <QDialog>
#include "function.h"
#include "stat.h"
#include "task1.h"
#include "task2.h"

namespace Ui {
class menu_window;
}

class menu_window : public QDialog
{
    Q_OBJECT

public:
    explicit menu_window(QWidget *parent = nullptr);
    ~menu_window();
    void username(QString username);

private slots:
    void on_pushButton_task1_clicked();

    void on_pushButton_task2_clicked();

    void on_pushButton_exit_clicked();

    void on_pushButton_stat_clicked();

private:
    Ui::menu_window *ui;
    Stat *stat_ui;
    Task1 *task1_ui;
    Task2 *task2_ui;
};

#endif // MENU_WINDOW_H
