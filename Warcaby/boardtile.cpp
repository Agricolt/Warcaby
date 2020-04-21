#include "boardtile.h"

boardTile::boardTile(QObject *parent) :
    QObject(parent), selected(false)
{
    //ustala wartosc piora na 0 (bez ramki)
    setPen(QPen(QBrush(), 0));
    this->setRect(0, 0, 50, 50);
}

void boardTile::setSelected()
{
    this->selected = true;
    this->setBrush(QBrush(QColor(1, 95, 36)));
}

void boardTile::setUnselected()
{
    this->selected = false;
    if (this->tile_colour == Colour::White)
        this->setBrush(light_pawn);
    else
        this->setBrush(dark_pawn);
}

void boardTile::setPosition(QPoint pos)
{
    this->position = pos;
}

QPoint boardTile::getPosition()
{
    return this->position;
}

void boardTile::setTileColour(Colour colour)
{
    this->tile_colour = colour;
    if (colour == Colour::Black)
        this->setBrush(dark_tile);
    else
        this->setBrush(light_tile);
}

void boardTile::setDefaultColour()
{
    if (this->tile_colour == Colour::Black)
        setBrush(QBrush(dark_tile));
    else
        setBrush(QBrush(light_tile));
}
