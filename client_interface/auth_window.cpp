#include "auth_window.h"
#include "ui_auth_window.h"
#include <QMessageBox>

auth_window::auth_window(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::auth_window)
{
    ui->setupUi(this);
    ui->lineEdit_email->setVisible(false);
    ui->pushButton_register->setVisible(false);
}

auth_window::~auth_window()
{
    delete ui;
}

void auth_window::on_pushButton_auth_clicked()
{
    // Получаем данные из полей ввода
    QString username1 = ui->lineEdit_log->text();
    QString password = ui->lineEdit_pass->text();
    // Проверяем, что поля не пустые
    if (username1.isEmpty() || password.isEmpty()) {
        QMessageBox::information(this, "Ошибка", "Пожалуйста, заполните все поля.");
    }
    bool check_auth = auth(username1, password);
    if (check_auth) {
        QMessageBox::information(this, "Авторизация", "Авторизация прошла успешно!");
        main_ui = new menu_window;
        this->close();
        main_ui->show();
    }
    else {
        QMessageBox::information(this, "Авторизация", "Вы ввели неверный пароль или логин!");
    }

    /*// Подключаемся к базе данных
    Database &db = Database::getInstance();
    if (db.connect()) {
        // Выполняем запрос на проверку авторизации
        QString query = QString("SELECT * FROM Users WHERE username='%1' AND password='%2'").arg(username, password);
        QStringList result = db.executeQuery(query, true);

        // Если пользователь найден, открываем окно меню, иначе показываем сообщение об ошибке
        if (!result.isEmpty()) {
            menu_window *menuWindow = new menu_window(this);
            menuWindow->show();
            this->hide();
        } else {
            QMessageBox::critical(this, "Ошибка", "Неправильное имя пользователя или пароль.");
        }

        db.disconnect(); // Отключаемся от базы данных
    } else {
        QMessageBox::critical(this, "Ошибка", "Не удалось подключиться к базе данных.");
    }
*/
}


void auth_window::on_pushButton_register_clicked()
{
    QString username1 = ui->lineEdit_log->text();
    QString password = ui->lineEdit_pass->text();
    QString email = ui->lineEdit_email->text();

    // Проверяем, что поля не пустые
    if (username1.isEmpty() || password.isEmpty() || email.isEmpty()) {
        QMessageBox::information(this, "Ошибка", "Пожалуйста, заполните все поля.");
    }
    bool check_reg = reg(username1, password, email);
    if (check_reg) {
        QMessageBox::information(this, "Регистрация", "Регистрация прошла успешно!");
        main_ui = new menu_window;
        this->close();
        main_ui->show();
        main_ui->username(username1);
    }
    else {
        QMessageBox::information(this, "Регистрация", "Зарегистрироваться не удалось!");
    }

}


void auth_window::on_pushButton_exit_clicked()
{
    // Создаем диалоговое окно для подтверждения выхода
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Подтверждение выхода", "Вы уверены, что хотите выйти?",
                                  QMessageBox::Yes | QMessageBox::No);

    // Если пользователь выбрал "Yes", завершаем приложение
    if (reply == QMessageBox::Yes) {
        qApp->exit();
    }

}


void auth_window::on_pushButton_change_clicked()
{
    bool set_flag = ui->pushButton_register->isVisible();
    ui->pushButton_auth->setVisible(set_flag);
    ui->pushButton_register->setVisible(!set_flag);
    ui->lineEdit_email->setVisible(!set_flag);
}

