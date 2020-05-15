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

    QImage image(":/new/backgrounds/background_main_army.jpg");
    QPixmap transparent(image.size());
    transparent.fill(Qt::transparent);
    QPainter p;
    p.begin(&transparent);
    p.setCompositionMode(QPainter::CompositionMode_Source);
    p.drawPixmap(0, 0, QPixmap::fromImage(image));
    p.setCompositionMode(QPainter::CompositionMode_DestinationIn);
    p.fillRect(transparent.rect(), QColor(0, 0, 0, 100));
    p.end();
    QGraphicsScene *scene = new QGraphicsScene(0, 0, 800, 600, this);
    ui->graphicsView_background->setScene(scene);
    ui->graphicsView_background->scene()->setBackgroundBrush(QBrush(transparent));
    ui->graphicsView_background->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView_background->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
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
