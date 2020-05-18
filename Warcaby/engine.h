#ifndef ENGINE_H
#define ENGINE_H

#include "menu.h"
#include "pawn.h"
#include "boardtile.h"
#include "CONSTANTS_ENUMS.h"
#include "lista.h"
#include "gamerules.h"
#include "saveandloadgame.h"

#include "Windows.h"

#include <iostream>
#include <QObject>
#include <QGraphicsView>
#include <vector>
#include <QtDebug>
#include <QPushButton>
#include <QLabel>
#include <QMouseEvent>
#include <typeinfo>
#include <QImage>
#include <QTimer>
#include <QMediaPlayer>
#include <QString>
#include <thread>

#include <QApplication>
#include <QWidget>



class Engine : public QGraphicsView, public saveAndLoadGame
{
    Q_OBJECT

    QGraphicsScene * scene;
    std::vector<std::vector<tileState>> game_board_state;
    std::vector<std::vector<boardTile*>> game_board_T;

    std::vector<Pawn*> player_1_pawns;  //biale
    std::vector<Pawn*> player_2_pawns;  //czarne

    Pawn * selected_pawn;               //aktualnie zaznaczony pionek
    boardTile * selected_boardTile;     //aktualnie zaznaczona kafelka planszy
    GameRules *gr; //Singleton obsługujący zasady gry

    int board_size;
    QString player_name;
    QLabel *label;

    //0 - ruch zostal wykonany
    //1 - ruch zostal wykoanny z biciem
    //2 - ruch zostal wykonany bez bicia
    int last_move;
    bool game_ended;
    bool whiteMove;  //jesli true to jest ruch gracza bialego

    //**************INICJALIZACJA****************
    void initializeBoard(int board_size);
    void placePawns(int pawns_count, int board_size);
    void placePawns(std::string saved);
    //**************ZDARZENIA********************
    void mousePressEvent(QMouseEvent *ev);
    //**************GRA**************************
    void movePawn();                             //Przemieszcza pionka na wskazaną plytke i wywoluje metode clearPawnAndTileAfterTime()
    void wrongMove();                            //koloruje pionek i plytke na czerwono i wywoluje metode clearPawnAndTileAfterTime()
    void clearPawnAndTileAfterTime(int time);    //Ustawia domyslny kolor i ZERUJE wskazniki na pionek i plytke!!!
    void removeKillesPawns();                    //Usuwa pionki, ktore zostaly zabite
    void checkForQueens();                       //sprawdza czy są nowe damki
    int checkForFinish();                        //Sprawdza czy gra sie zakonczyla. 1 - gre wygraly biale, 2 - gre wygraly czarne 0 - gra sie nie zakonczyla
    Pawn * findDeletingPawn();                   //znajduje zabijany pionek
    Pawn * selectPawnFromVector(QPoint pt, bool which_colour); //Znajduje pionek o podanej pozycji we wskazanym kolorze
    //********************************************
public slots:
    void handleExitButton();
public:
    Engine(gameType gT, QString player_name);    //kontruktor domyślny
    Engine(gameType gT, QString player_name, bool have_a_saved_game);   //konstuktor wczytujący grę
    //***********DEBUG*********************
    void printPawns(int pawns_in_row);
    void printBoardState(int board_size);
    void printBoardWithPawns(int board_size);
    //*************************************
};

#endif // ENGINE_H
