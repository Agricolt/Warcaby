#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsScene>
#include "pawn.h"

class Player
{
    const pawnColour pawn_colour;
    int killed_pawns, own_pawns;
public:
     Player(pawnColour colour, int x_board_size, int y_board_size, int starting_pawn_number, QGraphicsScene &scene);
};

#endif // PLAYER_H
