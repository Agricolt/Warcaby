#ifndef PAWN_H
#define PAWN_H

#include "CONSTANTS_ENUMS.h"
#include <QObject>
#include <QGraphicsEllipseItem>

#include <QBrush>
#include <QGraphicsView>


class Pawn : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
    bool selected;
    QPoint position;
public:
    tileState pawn_state;
    void set_selected();
    void setPosition(QPoint point);
    QPoint getPosition();
    Pawn(tileState ps, QObject *parent = nullptr);
public slots:
    void setDefaultColour();
};

#endif // PAWN_H
