#include "widget.h"
#include "exceptions.h"

#include <QApplication>
#include <QPixmap>
#include <QSplashScreen>
#include <QMediaPlayer>
#include <QThread>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //muzyka
    QMediaPlayer* player = new QMediaPlayer;
    try
    {
        player->setMedia(QUrl("qrc:/music/mainthemeorg.mp3"));
        if (player->mediaStatus() == QMediaPlayer::NoMedia)
            throw musicLoadError();
        player->setVolume(50);
        player->play();
    }
    catch (musicLoadError e)
    {
        std::cout << e.what();
        delete player;
    }

    Widget w;

    try
    {
        QPixmap pixmap(":/new/backgrounds/splash.jpg");
        if (pixmap.isNull())
            throw graphicsLoadError();
        QSplashScreen splash(pixmap);
        splash.show();
        QThread::sleep(2);
        splash.finish(&w);
    }
    catch (graphicsLoadError e)
    {
        std::cout << e.what();
    }
    w.show();
    return a.exec();
}
