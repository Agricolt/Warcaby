#include "widget.h"

#include <QApplication>
#include <QPixmap>
#include <QSplashScreen>
#include <QMediaPlayer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //muzyka
    QMediaPlayer* player = new QMediaPlayer;
    player->setMedia(QUrl("qrc:/music/mainthemeorg.mp3"));
    player->setVolume(50);
    player->play();
    QPixmap pixmap(":/new/backgrounds/splash.jpg");
    QSplashScreen splash(pixmap);
    splash.show();
    Widget w;
    w.show();
    splash.finish(&w);
    return a.exec();
}
