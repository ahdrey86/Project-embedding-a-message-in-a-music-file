#include "register_window.h"
#include "ui_register_window.h"

register_window::register_window(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::register_window)
{
    ui->setupUi(this);
}

register_window::~register_window()
{
    delete ui;
}
