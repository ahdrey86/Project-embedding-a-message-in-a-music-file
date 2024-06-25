#include "task1.h"
#include "ui_task1.h"

Task1::Task1(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Task1)
{
    ui->setupUi(this);
    ui->lineEdit_a_b->setReadOnly(true);
    ui->lineEdit_f->setReadOnly(true);
    ui->lineEdit_n->setReadOnly(true);
    ui->label_login->setVisible(false);
    ui->label_var->setVisible(false);
}

Task1::~Task1()
{
    delete ui;
}

void Task1::on_pushButton_exit_clicked()
{
    this->close();
}


void Task1::on_pushButton_check_clicked()
{
    bool flag = check("1", ui->label_var->text(), ui->lineEdit_result->text(), ui->label_login->text());
    if (flag){
        QMessageBox::information(this, "Task1", "Верно решено!");
        ui->pushButton_check->setEnabled(false);
    } else {
        QMessageBox::information(this, "Task1", "Не верное решение!");
    }
}
void Task1::username(QString username) {
    ui->label_login->setText(username);
}

void Task1::update_task1() {
    ui->pushButton_check->setEnabled(true);
    ui->lineEdit_result->setText("");
    const QStringList function_str1 = {"12 + x", "12 + x*x", "12x + 1"};
    QString a = QString::number(-(QRandomGenerator::global()->bounded(0, 101)));
    QString b = QString::number(QRandomGenerator::global()->bounded(0, 101));
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(0.001, 0.1);
    QString eps = QString::number(dis(gen));
    QString number_var = QString::number(QRandomGenerator::global()->bounded(0, 3));
    ui->lineEdit_a_b->setText("[" + a + "," + b + "]");
    ui->lineEdit_n->setText(eps);
    ui->lineEdit_f->setText(function_str1[number_var.toInt()]);
    ui->label_var->setText(number_var + "_" + a + "_" + b  + "_" + eps);
}
