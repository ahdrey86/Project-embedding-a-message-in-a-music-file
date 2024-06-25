#include "menu_window.h"
#include "ui_menu_window.h"

menu_window::menu_window(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::menu_window)
{
    ui->setupUi(this);
    ui->label_login->setVisible(false);
}

menu_window::~menu_window()
{
    delete ui;
}

void menu_window::on_pushButton_task1_clicked()
{
    task1_ui = new Task1;
    task1_ui->show();
    task1_ui->username(ui->label_login->text());
    task1_ui->update_task1();
}


void menu_window::on_pushButton_task2_clicked()
{
    task2_ui = new Task2;
    task2_ui->show();
    task2_ui->username(ui->label_login->text());
}


void menu_window::on_pushButton_exit_clicked()
{
    this->close();
}


void menu_window::on_pushButton_stat_clicked()
{
    stat_ui = new Stat;
    stat_ui->show();
    stat_ui->username(ui->label_login->text());
}
void menu_window::username(QString username) {
    ui->label_login->setText(username);
}
