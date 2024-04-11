/********************************************************************************
** Form generated from reading UI file 'clientwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENTWIDGET_H
#define UI_CLIENTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLineEdit *lineEdit_IP;
    QLineEdit *lineEdit_Port;
    QPushButton *pushButton_connect;
    QTextEdit *textEdit_toSend;
    QPushButton *pushButton_Send;
    QTextEdit *textEdit_toGet;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName("Form");
        Form->resize(663, 474);
        verticalLayoutWidget = new QWidget(Form);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(30, 20, 601, 431));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        lineEdit_IP = new QLineEdit(verticalLayoutWidget);
        lineEdit_IP->setObjectName("lineEdit_IP");

        verticalLayout->addWidget(lineEdit_IP);

        lineEdit_Port = new QLineEdit(verticalLayoutWidget);
        lineEdit_Port->setObjectName("lineEdit_Port");

        verticalLayout->addWidget(lineEdit_Port);

        pushButton_connect = new QPushButton(verticalLayoutWidget);
        pushButton_connect->setObjectName("pushButton_connect");

        verticalLayout->addWidget(pushButton_connect);

        textEdit_toSend = new QTextEdit(verticalLayoutWidget);
        textEdit_toSend->setObjectName("textEdit_toSend");

        verticalLayout->addWidget(textEdit_toSend);

        pushButton_Send = new QPushButton(verticalLayoutWidget);
        pushButton_Send->setObjectName("pushButton_Send");

        verticalLayout->addWidget(pushButton_Send);

        textEdit_toGet = new QTextEdit(verticalLayoutWidget);
        textEdit_toGet->setObjectName("textEdit_toGet");

        verticalLayout->addWidget(textEdit_toGet);


        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QCoreApplication::translate("Form", "Form", nullptr));
        pushButton_connect->setText(QCoreApplication::translate("Form", "\320\237\320\276\320\264\320\272\320\273\321\216\321\207\320\270\321\202\321\214\321\201\321\217", nullptr));
        pushButton_Send->setText(QCoreApplication::translate("Form", "\320\236\321\202\320\277\321\200\320\260\320\262\320\270\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENTWIDGET_H
