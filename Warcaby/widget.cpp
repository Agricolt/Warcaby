#include <string>
#include <QObject>
#include <QColorDialog>
#include "widget.h"
#include "ui_widget.h"
#include "menu.h"
#include "credentialsvalidation.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
   delete ui;
}


void Widget::on_pushButtonLogIn_clicked()
{
    //pobranie loginu i hasla do dalszej walidacji
    QString login = ui->lineEditLogin->text();
    QString password = ui->lineEditPassword->text();
    if (CredentialsValidation::validate(login, password) == true)
    {
        Menu *m = new Menu();
        Widget::on_pushButtonExit_clicked();
        m->setLabel_Welcome(login);
        m->show();
    }
    else
    {
        QColor color = Qt::red;
        QPalette palette = ui->label_IncorrectCredentials->palette();
        palette.setColor(QPalette::WindowText, color);
        ui->label_IncorrectCredentials->setPalette(palette);
        ui->label_IncorrectCredentials->setText("Niepoprawne dane logowania");
    }
}
void Widget::on_pushButtonExit_clicked()
{
    this->close();
}
