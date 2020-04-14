#ifndef PAWN_H
#define PAWN_H

#include <QObject>
#include <QGraphicsEllipseItem>

enum class pawnType
{
    Normal,
    Queen
};

enum class pawnColour
{
    White,
    Black
};

class Pawn : public QObject, public QGraphicsEllipseItem
{
    pawnType type;
    pawnColour colour;
    Q_OBJECT
public:
    explicit Pawn(QObject *parent = nullptr);

signals:

};

#endif // PAWN_H
