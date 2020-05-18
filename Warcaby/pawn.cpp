#include "pawn.h"

void Pawn::set_selected()
{
    this->setBrush(QBrush(selected_pawn));
}

void Pawn::setPosition(QPoint point)
{
    this->position = point;
}

void Pawn::transformToQueen()
{
    if (this->pawn_state == tileState::WhitePawn)
    {
        this->pawn_state = tileState::WhiteQueen;
        this->setBrush(QBrush(light_queen));
    }
    else if (this->pawn_state == tileState::BlackPawn)
    {
        this->pawn_state = tileState::BlackQueen;
        this->setBrush(QBrush(dark_queen));
    }
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
    {
        this->setBrush(QBrush(dark_pawn));
    }
    else if (ps == tileState::WhitePawn)
    {
        this->setBrush(QBrush(light_pawn));
    }
    else if (ps == tileState::WhiteQueen)
    {
        this->setBrush(QBrush(light_queen));
    }
    else if (ps == tileState::BlackPawn)
    {
        this->setBrush(QBrush(dark_queen));
    }
    setPen(QPen(QBrush(), 0));
}

void Pawn::setDefaultColour()
{
    if (this->pawn_state == tileState::BlackPawn)
        setBrush(QBrush(dark_pawn));
    else if (this->pawn_state == tileState::WhitePawn)
        setBrush(QBrush(light_pawn));
    else if (this->pawn_state == tileState::BlackQueen)
        setBrush(QBrush(dark_queen));
    else if (this->pawn_state == tileState::WhiteQueen)
        setBrush(QBrush(light_queen));
}
