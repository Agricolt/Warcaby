#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QColor>

enum class Colour
{
    White,
    Black
};

enum class tileState
{
    Empty,
    WhitePawn,
    BlackPawn,
    WhiteQueen,
    BlackQueen,
    Killed
};

enum class gameType
{
    Brazilian,
    International_Polish,
    English
};

const int BOARD_TILE_SIZE = 50;
const int DEBUG_BOARD_SIZE = 8;

const QColor light_tile = QColor(255, 255, 255);
const QColor dark_tile = QColor(162, 145, 107);
const QColor wrong_tile = QColor(143, 12, 18);

const QColor light_pawn = QColor(207, 221, 250);
const QColor dark_pawn = QColor(32, 23, 4);
const QColor light_queen = QColor(253, 244, 83);
const QColor dark_queen = QColor(194, 185, 3);
const QColor wrong_pawn = QColor(241, 84, 91);
const QColor selected_pawn = QColor(34, 177, 76);



#endif // CONSTANTS_H
