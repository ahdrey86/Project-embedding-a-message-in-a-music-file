#include "client_interface.h"
#include "ui_client_interface.h"
#include <QMessageBox>

client_interface::client_interface(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::client_interface)
{
    ui->setupUi(this);
}

client_interface::~client_interface()
{
    delete ui;
}
