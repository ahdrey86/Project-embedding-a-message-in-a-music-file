#ifndef TASK2_H
#define TASK2_H

#include <QWidget>
#include "function.h"

namespace Ui {
class Task2;
}

class Task2 : public QWidget
{
    Q_OBJECT

public:
    explicit Task2(QWidget *parent = nullptr);
    ~Task2();
    void username(QString username);

private slots:
    void on_pushButton_exit_clicked();

    void on_pushButton_check_clicked();

private:
    Ui::Task2 *ui;
};

#endif // TASK2_H
