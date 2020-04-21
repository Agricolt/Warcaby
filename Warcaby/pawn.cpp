#include "pawn.h"

void Pawn::set_selected()
{
    this->setBrush(QBrush(QColor(34, 177, 76)));
}

void Pawn::setPosition(QPoint point)
{
    this->position = point;
}

QPoint Pawn::getPosition()
{
    return this->position;
}

Pawn::Pawn(tileState ps, QObject *parent) :
    QObject(parent),selected(false), pawn_state(ps)
{
    this->setRect(0, 0, 40, 40);
    if (ps == tileState::BlackPawn)
        this->setBrush(QBrush(dark_pawn));
    else
        this->setBrush(QBrush(light_pawn));
    setPen(QPen(QBrush(), 0));
}

void Pawn::setDefaultColour()
{
    if (this->pawn_state == tileState::BlackPawn ||this->pawn_state == tileState::BlackQueen)
        setBrush(QBrush(dark_pawn));
    else
        setBrush(QBrush(light_pawn));
}
