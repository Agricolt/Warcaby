#include <string>
#include "widget.h"
#include "ui_widget.h"

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
    QString login = ui->lineEditLogin->text();
    QString password = this->ui->lineEditPassword->text();
    std::string l = login.toStdString();
    std::string p = password.toStdString();
}
