#ifndef ENGINE_H
#define ENGINE_H

#include "menu.h"
#include "CONSTANTS.h"

#include <QObject>
#include <QGraphicsView>
#include <vector>
#include <boardtile.h>
#include <pawn.h>
#include <player.h>
#include <QtDebug>
#include <QPushButton>
#include <QMouseEvent>
#include <typeinfo>
#include <QStyleOptionGraphicsItem>

class Engine : public QGraphicsView
{
    Q_OBJECT

    QGraphicsScene * scene;

    int **game_board_int;
    boardTile **game_board_T;

    std::vector<Pawn> player_1_pawns;
    std::vector<Pawn> player_2_pawns;


    void initializeBoard(int board_size);
    void placePawns(int pawns_count, int board_size);

    void mousePressEvent(QMouseEvent *ev);
public slots:
    void handleExitButton();

public:
    Engine();
    void printIntTable(int board_size);
};

#endif // ENGINE_H
