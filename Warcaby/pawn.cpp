#include "pawn.h"

void Pawn::set_selected()
{
    this->setBrush(QBrush(QColor(34, 177, 76)));
}

Pawn::Pawn(Colour pC, pawnType pT, QRect rect, QObject *parent) :
    QObject(parent), type(pT), colour(pC), selected(false)
{
    setRect(rect);
    if (pC == Colour::Black)
        this->setBrush(QBrush(dark_pawn));
    else
        this->setBrush(QBrush(light_pawn));
    setPen(QPen(QBrush(), 0));
}
