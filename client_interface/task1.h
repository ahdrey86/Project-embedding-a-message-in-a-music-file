#ifndef TASK1_H
#define TASK1_H

#include <QWidget>
#include "function.h"
#include <QRandomGenerator>
#include <QVariant>
#include <QObject>
#include <QMessageBox>

namespace Ui {
class Task1;
}

class Task1 : public QWidget
{
    Q_OBJECT

public:
    explicit Task1(QWidget *parent = nullptr);
    ~Task1();
    void username(QString username);
    void update_task1();

private slots:
    void on_pushButton_exit_clicked();

    void on_pushButton_check_clicked();

private:
    Ui::Task1 *ui;
};

#endif // TASK1_H
