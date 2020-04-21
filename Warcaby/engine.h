#ifndef ENGINE_H
#define ENGINE_H

#include "menu.h"
#include "pawn.h"
#include "boardtile.h"
#include "CONSTANTS_ENUMS.h"
#include "lista.h"
#include "gamerules.h"

#include "Windows.h"

#include <iostream>
#include <QObject>
#include <QGraphicsView>
#include <vector>
#include <QtDebug>
#include <QPushButton>
#include <QMouseEvent>
#include <typeinfo>
#include <QImage>
#include <QTimer>

#include <QApplication>
#include <QWidget>



class Engine : public QGraphicsView
{
    Q_OBJECT

    QGraphicsScene * scene;

    tileState **game_board_state;
    boardTile **game_board_T;

    std::vector<Pawn*> player_1_pawns;
    std::vector<Pawn*> player_2_pawns;

    Pawn * selected_pawn;
    boardTile * selected_boardTile;
    GameRules *gr;

    int board_size;

    //**************INICJALIZACJA****************
    void initializeBoard(int board_size);
    void placePawns(int pawns_count, int board_size);
    //**************ZDARZENIA********************
    void mousePressEvent(QMouseEvent *ev);
    //**************GRA**************************
    void movePawn();                             //Przemieszcza pionka na wskazaną plytke i wywoluje metode clearPawnAndTileAfterTime()
    void wrongMove();                            //koloruje pionek i plytke na czerwono i wywoluje metode clearPawnAndTileAfterTime()
    void clearPawnAndTileAfterTime(int time);    //Ustawia domyslny kolor i ZERUJE wskazniki na pionek i plytke!!!
    //********************************************
public slots:
    void handleExitButton();
public:
    Engine(gameType gT);
    void printPawns(int pawns_in_row);
    void printBoardState(int board_size);
    void printBoardWithPawns(int board_size);
};

#endif // ENGINE_H
