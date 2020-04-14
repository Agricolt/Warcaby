/********************************************************************************
** Form generated from reading UI file 'menu.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MENU_H
#define UI_MENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Menu
{
public:
    QLabel *label_Welcome;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton_startGameHotseat;
    QPushButton *pushButton_StartGameWithAI;
    QPushButton *pushButton_LogOutAndExit;

    void setupUi(QWidget *Menu)
    {
        if (Menu->objectName().isEmpty())
            Menu->setObjectName(QString::fromUtf8("Menu"));
        Menu->resize(800, 600);
        label_Welcome = new QLabel(Menu);
        label_Welcome->setObjectName(QString::fromUtf8("label_Welcome"));
        label_Welcome->setGeometry(QRect(10, 20, 501, 171));
        QFont font;
        font.setFamily(QString::fromUtf8("MV Boli"));
        font.setPointSize(48);
        label_Welcome->setFont(font);
        layoutWidget = new QWidget(Menu);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(280, 240, 217, 98));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_startGameHotseat = new QPushButton(layoutWidget);
        pushButton_startGameHotseat->setObjectName(QString::fromUtf8("pushButton_startGameHotseat"));

        verticalLayout->addWidget(pushButton_startGameHotseat);

        pushButton_StartGameWithAI = new QPushButton(layoutWidget);
        pushButton_StartGameWithAI->setObjectName(QString::fromUtf8("pushButton_StartGameWithAI"));

        verticalLayout->addWidget(pushButton_StartGameWithAI);

        pushButton_LogOutAndExit = new QPushButton(layoutWidget);
        pushButton_LogOutAndExit->setObjectName(QString::fromUtf8("pushButton_LogOutAndExit"));

        verticalLayout->addWidget(pushButton_LogOutAndExit);


        retranslateUi(Menu);

        QMetaObject::connectSlotsByName(Menu);
    } // setupUi

    void retranslateUi(QWidget *Menu)
    {
        Menu->setWindowTitle(QCoreApplication::translate("Menu", "Form", nullptr));
        label_Welcome->setText(QCoreApplication::translate("Menu", "Witaj <login>", nullptr));
        pushButton_startGameHotseat->setText(QCoreApplication::translate("Menu", "Rozpocznij gr\304\231 na 2 osoby (hotseat)", nullptr));
        pushButton_StartGameWithAI->setText(QCoreApplication::translate("Menu", "Rozpocznij gr\304\231 z komputerem", nullptr));
        pushButton_LogOutAndExit->setText(QCoreApplication::translate("Menu", "Wyloguj i wyjd\305\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Menu: public Ui_Menu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MENU_H
