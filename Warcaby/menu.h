#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include <QGraphicsView>

#include <QObject>
#include <QGraphicsView>

#include "widget.h"
namespace Ui {
class Menu;
}

class Menu : public QWidget
{
    Q_OBJECT

public:
    void setLabel_Welcome(QString name);
    explicit Menu(QWidget *parent = nullptr, QString player_name = "");
    ~Menu();

private slots:
    void on_pushButton_LogOutAndExit_clicked();

    void on_pushButton_startGameHotseat_clicked();

    void on_pushButton_ExitOnly_clicked();

    void on_pushButton_LoadLastGame_clicked();

private:
    Ui::Menu *ui;
    QString player_name;
};

#endif // MENU_H
