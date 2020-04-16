#include "menu.h"
#include "ui_menu.h"
#include "engine.h"

void Menu::setLabel_Welcome(QString name)
{
    QString text = "Witaj ";
    text += name;
    this->ui->label_Welcome->setText(text);
}

Menu::Menu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);
}

Menu::~Menu()
{
    delete ui;
}

void Menu::on_pushButton_LogOutAndExit_clicked()
{
    this->close();
}

void Menu::on_pushButton_startGameHotseat_clicked()
{
    Engine *eng = new Engine(gameType::Brazilian);
    eng->show();
    this->on_pushButton_LogOutAndExit_clicked();
}
