#include "task2.h"
#include "ui_task2.h"

Task2::Task2(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Task2)
{
    ui->setupUi(this);
    ui->label_login->setVisible(false);

}

Task2::~Task2()
{
    delete ui;
}
void Task2::username(QString username) {
    ui->label_login->setText(username);
}

void Task2::on_pushButton_exit_clicked()
{
    this->close();
}


void Task2::on_pushButton_check_clicked()
{

}

