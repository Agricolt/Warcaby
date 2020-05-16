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
    try
    {
        if (CredentialsValidation::Validate(login, password) == true)
        {
            Menu *m = new Menu(nullptr, login);
            Widget::on_pushButtonExit_clicked();
            m->show();
        }
    }
    catch(CredentialsValidationError e)
    {
        qDebug() << QString::fromStdString(e.what());
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

void Widget::on_pushButton_register_clicked()
{
    QString login = ui->lineEditLogin->text();
    QString password = ui->lineEditPassword->text();
    bool register_complete = false;
    try
    {
        if (login.isEmpty() != true && password.isEmpty() != true)
            register_complete = CredentialsValidation::Register(login, password);
    }
    catch ( CredentialsValidationError e)
    {
        qDebug() << QString::fromStdString(e.what());
    }
    if (register_complete == true)
    {
        QColor color = Qt::green;
        QPalette palette = ui->label_IncorrectCredentials->palette();
        palette.setColor(QPalette::WindowText, color);
        ui->label_IncorrectCredentials->setPalette(palette);
        ui->label_IncorrectCredentials->setText("Pomyślnie zarejestrowano!");
    }
    else
    {
        QColor color = Qt::red;
        QPalette palette = ui->label_IncorrectCredentials->palette();
        palette.setColor(QPalette::WindowText, color);
        ui->label_IncorrectCredentials->setPalette(palette);
        ui->label_IncorrectCredentials->setText("Dany login jest już zajęty!");
    }
}
