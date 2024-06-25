#include "stat.h"
#include "ui_stat.h"

Stat::Stat(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Stat)
{
    ui->setupUi(this);
    ui->label_login->setVisible(false);
}

Stat::~Stat()
{
    delete ui;
}

void Stat::on_pushButton_exit_clicked()
{
    this->close();
}


void Stat::on_pushButton_update_clicked()
{

}

void Stat::username(QString username) {
    ui->label_login->setText(username);
}
