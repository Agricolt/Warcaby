/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QWidget *widget;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QLabel *labelLogin;
    QLabel *labelPassword;
    QVBoxLayout *verticalLayout;
    QLineEdit *lineEditLogin;
    QLineEdit *lineEditPassword;
    QPushButton *pushButtonLogIn;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(800, 600);
        widget = new QWidget(Widget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(300, 230, 192, 90));
        verticalLayout_3 = new QVBoxLayout(widget);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        labelLogin = new QLabel(widget);
        labelLogin->setObjectName(QString::fromUtf8("labelLogin"));

        verticalLayout_2->addWidget(labelLogin);

        labelPassword = new QLabel(widget);
        labelPassword->setObjectName(QString::fromUtf8("labelPassword"));

        verticalLayout_2->addWidget(labelPassword);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        lineEditLogin = new QLineEdit(widget);
        lineEditLogin->setObjectName(QString::fromUtf8("lineEditLogin"));
        lineEditLogin->setEnabled(true);

        verticalLayout->addWidget(lineEditLogin);

        lineEditPassword = new QLineEdit(widget);
        lineEditPassword->setObjectName(QString::fromUtf8("lineEditPassword"));

        verticalLayout->addWidget(lineEditPassword);


        horizontalLayout->addLayout(verticalLayout);


        verticalLayout_3->addLayout(horizontalLayout);

        pushButtonLogIn = new QPushButton(widget);
        pushButtonLogIn->setObjectName(QString::fromUtf8("pushButtonLogIn"));

        verticalLayout_3->addWidget(pushButtonLogIn);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Warcaby - Zaloguj Si\304\231", nullptr));
        labelLogin->setText(QCoreApplication::translate("Widget", "Login: ", nullptr));
        labelPassword->setText(QCoreApplication::translate("Widget", "Has\305\202o: ", nullptr));
        pushButtonLogIn->setText(QCoreApplication::translate("Widget", "Zaloguj", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
