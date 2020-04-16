#ifndef ENGINE_H
#define ENGINE_H

#include "menu.h"
#include "pawn.h"
#include "boardtile.h"
#include "CONSTANTS_ENUMS.h"
#include "list.h"

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

#include <QApplication>
#include <QWidget>

enum class tileState
{
    Empty,
    WhitePawn,
    BlackPawn,
    WhiteQueen,
    BlackQueen
};

enum class gameType
{
    Brazilian,
    International_Polish,
    English
};

class Engine : public QGraphicsView
{
    Q_OBJECT

    QGraphicsScene * scene;

    tileState **game_board_state;
    boardTile **game_board_T;

    std::vector<Pawn> player_1_pawns;
    std::vector<Pawn> player_2_pawns;

    Pawn * selected_pawn;
    boardTile * selected_boardTile;
    gameType gt;

    //**************INICJALIZACJA****************
    void initializeBoard(int board_size);
    void placePawns(int pawns_count, int board_size);
    //**************ZDARZENIA****************
    void mousePressEvent(QMouseEvent *ev);
    //**************GRA****************
    bool checkMove();
public slots:
    void handleExitButton();

public:
    Engine(gameType gT);
    void printIntTable(int board_size);
};

#endif // ENGINE_H
