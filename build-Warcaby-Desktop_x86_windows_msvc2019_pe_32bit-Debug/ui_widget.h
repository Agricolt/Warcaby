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
#include <QtWidgets/QCheckBox>
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
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QLabel *labelLogin;
    QLabel *labelPassword;
    QVBoxLayout *verticalLayout;
    QLineEdit *lineEditLogin;
    QLineEdit *lineEditPassword;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_IncorrectCredentials;
    QCheckBox *checkBox;
    QPushButton *pushButtonLogIn;
    QPushButton *pushButtonExit;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->setWindowModality(Qt::WindowModal);
        Widget->resize(300, 200);
        Widget->setMinimumSize(QSize(300, 200));
        Widget->setMaximumSize(QSize(300, 200));
        layoutWidget = new QWidget(Widget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(60, 20, 192, 174));
        verticalLayout_4 = new QVBoxLayout(layoutWidget);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        labelLogin = new QLabel(layoutWidget);
        labelLogin->setObjectName(QString::fromUtf8("labelLogin"));

        verticalLayout_2->addWidget(labelLogin);

        labelPassword = new QLabel(layoutWidget);
        labelPassword->setObjectName(QString::fromUtf8("labelPassword"));

        verticalLayout_2->addWidget(labelPassword);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        lineEditLogin = new QLineEdit(layoutWidget);
        lineEditLogin->setObjectName(QString::fromUtf8("lineEditLogin"));
        lineEditLogin->setEnabled(true);

        verticalLayout->addWidget(lineEditLogin);

        lineEditPassword = new QLineEdit(layoutWidget);
        lineEditPassword->setObjectName(QString::fromUtf8("lineEditPassword"));

        verticalLayout->addWidget(lineEditPassword);


        horizontalLayout->addLayout(verticalLayout);


        verticalLayout_4->addLayout(horizontalLayout);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_IncorrectCredentials = new QLabel(layoutWidget);
        label_IncorrectCredentials->setObjectName(QString::fromUtf8("label_IncorrectCredentials"));

        verticalLayout_3->addWidget(label_IncorrectCredentials);

        checkBox = new QCheckBox(layoutWidget);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(checkBox->sizePolicy().hasHeightForWidth());
        checkBox->setSizePolicy(sizePolicy);
        checkBox->setToolTipDuration(-1);

        verticalLayout_3->addWidget(checkBox);

        pushButtonLogIn = new QPushButton(layoutWidget);
        pushButtonLogIn->setObjectName(QString::fromUtf8("pushButtonLogIn"));
        pushButtonLogIn->setFlat(false);

        verticalLayout_3->addWidget(pushButtonLogIn);

        pushButtonExit = new QPushButton(layoutWidget);
        pushButtonExit->setObjectName(QString::fromUtf8("pushButtonExit"));

        verticalLayout_3->addWidget(pushButtonExit);


        verticalLayout_4->addLayout(verticalLayout_3);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Warcaby - Zaloguj Si\304\231", nullptr));
        labelLogin->setText(QCoreApplication::translate("Widget", "Login: ", nullptr));
        labelPassword->setText(QCoreApplication::translate("Widget", "Has\305\202o: ", nullptr));
        label_IncorrectCredentials->setText(QString());
#if QT_CONFIG(tooltip)
        checkBox->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        checkBox->setText(QCoreApplication::translate("Widget", "Pozosta\305\204 zalogowanym", nullptr));
        pushButtonLogIn->setText(QCoreApplication::translate("Widget", "Zaloguj", nullptr));
        pushButtonExit->setText(QCoreApplication::translate("Widget", "Wyjd\305\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
