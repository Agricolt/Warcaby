#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QColor>

enum class Colour
{
    White,
    Black
};

const int BOARD_TILE_SIZE = 50;
const int DEBUG_BOARD_SIZE = 8;

const QColor light_tile = QColor(255, 255, 255);
const QColor dark_tile = QColor(162, 145, 107);

const QColor light_pawn = QColor(207, 221, 250);
const QColor dark_pawn = QColor(32, 23, 4);



#endif // CONSTANTS_H
