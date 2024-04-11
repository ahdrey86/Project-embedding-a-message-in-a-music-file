#ifndef AUTH_WINDOW_H
#define AUTH_WINDOW_H

#include <QMainWindow>
#include "connection_manager.h"

namespace Ui {
class auth_window;
}

class auth_window : public QMainWindow
{
    Q_OBJECT

public:
    explicit auth_window(QWidget *parent = nullptr);
    ~auth_window();

private slots:
    void attemptLogin(); // Метод для попытки аутентификации пользователя
    void switchToRegister(); // Метод для переключения на окно регистрации

private:
    Ui::auth_window *ui;
    ConnectionManager *connectionManager;

signals:
    void switchClientWindow();
    void switchRegisterWindow();
};

#endif // AUTH_WINDOW_H
