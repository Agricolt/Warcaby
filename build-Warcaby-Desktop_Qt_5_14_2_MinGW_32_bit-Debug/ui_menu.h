/********************************************************************************
** Form generated from reading UI file 'menu.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MENU_H
#define UI_MENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
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
    QPushButton *pushButton_ExitOnly;
    QPushButton *pushButton_LogOutAndExit;
    QGraphicsView *graphicsView_background;
    QLabel *label;

    void setupUi(QWidget *Menu)
    {
        if (Menu->objectName().isEmpty())
            Menu->setObjectName(QString::fromUtf8("Menu"));
        Menu->resize(800, 600);
        Menu->setAutoFillBackground(true);
        label_Welcome = new QLabel(Menu);
        label_Welcome->setObjectName(QString::fromUtf8("label_Welcome"));
        label_Welcome->setGeometry(QRect(10, 20, 751, 101));
        QFont font;
        font.setFamily(QString::fromUtf8("MV Boli"));
        font.setPointSize(64);
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

        pushButton_ExitOnly = new QPushButton(layoutWidget);
        pushButton_ExitOnly->setObjectName(QString::fromUtf8("pushButton_ExitOnly"));

        verticalLayout->addWidget(pushButton_ExitOnly);

        pushButton_LogOutAndExit = new QPushButton(layoutWidget);
        pushButton_LogOutAndExit->setObjectName(QString::fromUtf8("pushButton_LogOutAndExit"));

        verticalLayout->addWidget(pushButton_LogOutAndExit);

        graphicsView_background = new QGraphicsView(Menu);
        graphicsView_background->setObjectName(QString::fromUtf8("graphicsView_background"));
        graphicsView_background->setGeometry(QRect(0, 0, 801, 601));
        graphicsView_background->setSceneRect(QRectF(0, 0, 800, 600));
        label = new QLabel(Menu);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 130, 761, 71));
        QFont font1;
        font1.setFamily(QString::fromUtf8("MV Boli"));
        font1.setPointSize(36);
        label->setFont(font1);
        graphicsView_background->raise();
        layoutWidget->raise();
        label_Welcome->raise();
        label->raise();

        retranslateUi(Menu);

        QMetaObject::connectSlotsByName(Menu);
    } // setupUi

    void retranslateUi(QWidget *Menu)
    {
        Menu->setWindowTitle(QCoreApplication::translate("Menu", "Warcaby - Menu g\305\202\303\263wne", nullptr));
        label_Welcome->setText(QCoreApplication::translate("Menu", "Witaj <login>", nullptr));
        pushButton_startGameHotseat->setText(QCoreApplication::translate("Menu", "Rozpocznij gr\304\231 na 2 osoby (hotseat)", nullptr));
        pushButton_ExitOnly->setText(QCoreApplication::translate("Menu", "Wyjd\305\272", nullptr));
        pushButton_LogOutAndExit->setText(QCoreApplication::translate("Menu", "Wyloguj i wyjd\305\272", nullptr));
        label->setText(QCoreApplication::translate("Menu", "Pi\304\231kna pogoda na parti\304\231 warcab!", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Menu: public Ui_Menu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MENU_H
