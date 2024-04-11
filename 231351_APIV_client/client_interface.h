#ifndef CLIENT_INTERFACE_H
#define CLIENT_INTERFACE_H

#include <QMainWindow>

namespace Ui {
class client_interface;
}

class client_interface : public QMainWindow
{
    Q_OBJECT

public:
    explicit client_interface(QWidget *parent = nullptr);
    ~client_interface();

private:
    Ui::client_interface *ui;
};

#endif // CLIENT_INTERFACE_H
