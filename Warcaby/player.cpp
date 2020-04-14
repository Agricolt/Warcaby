#include "player.h"

Player::Player(pawnColour colour, int x_board_size, int y_board_size, int starting_pawn_number, QGraphicsScene &scene)
    : pawn_colour(colour), killed_pawns(0), own_pawns(starting_pawn_number)
{
    for (int i = 0; i < x_board_size; i++)
    {
        for (int j = 0; j < y_board_size; j++)
        {
            Pawn *p = new Pawn();
            p->setRect(0, 0, 50, 50);
        }
    }
}
