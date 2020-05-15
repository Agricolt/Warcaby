#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include <QGraphicsView>

#include <QObject>
#include <QGraphicsView>
namespace Ui {
class Menu;
}

class Menu : public QWidget
{
    Q_OBJECT

public:
    void setLabel_Welcome(QString name);
    explicit Menu(QWidget *parent = nullptr);
    ~Menu();

private slots:
    void on_pushButton_LogOutAndExit_clicked();

    void on_pushButton_startGameHotseat_clicked();

private:
    Ui::Menu *ui;
};

#endif // MENU_H
