#ifndef STAT_H
#define STAT_H

#include <QWidget>

namespace Ui {
class Stat;
}

class Stat : public QWidget
{
    Q_OBJECT

public:
    explicit Stat(QWidget *parent = nullptr);
    ~Stat();
    void username(QString username);

private slots:
    void on_pushButton_exit_clicked();

    void on_pushButton_update_clicked();

private:
    Ui::Stat *ui;
};

#endif // STAT_H
