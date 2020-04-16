#ifndef PAWN_H
#define PAWN_H

#include "CONSTANTS_ENUMS.h"
#include <QObject>
#include <QGraphicsEllipseItem>

#include <QBrush>
#include <QGraphicsView>


enum class pawnType
{
    Normal,
    Queen
};

class Pawn : public QObject, public QGraphicsEllipseItem
{
    pawnType type;
    Colour colour;
    bool selected;
    Q_OBJECT
public:
    void set_selected();
    void set_unselected();
    Pawn(Colour pC, pawnType pT, QRect rect, QObject *parent = nullptr);

signals:

};

#endif // PAWN_H
