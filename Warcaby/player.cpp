#include "player.h"

Player::Player(Colour colour, int x_board_size, int y_board_size, int starting_pawn_number, QGraphicsScene &scene)
    : pawn_colour(colour), killed_pawns(0), own_pawns(starting_pawn_number)
{
}

