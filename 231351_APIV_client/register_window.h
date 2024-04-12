#ifndef REGISTER_WINDOW_H
#define REGISTER_WINDOW_H

#include <QMainWindow>
#include "connection_manager.h"

namespace Ui {
class register_window;
}

class register_window : public QMainWindow
{
    Q_OBJECT

public:
    explicit register_window(QWidget *parent = nullptr);
    ~register_window();

private slots:
    void switchToAuth(); // Слот для обработки нажатия кнопки "Назад к окну входа"
    void attemptRegister(); // Слот для обработки нажатия кнопки "Зарегистрироваться"


private:
    Ui::register_window *ui;
    ConnectionManager *connectionManager;

signals:
    void switchAuthWindow(); // Сигнал для переключения на окно клиента
};

#endif // REGISTER_WINDOW_H



