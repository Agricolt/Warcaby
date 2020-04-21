#ifndef BOARDTILE_H
#define BOARDTILE_H

#include "CONSTANTS_ENUMS.h"
#include <QBrush>
#include <QGraphicsView>
#include <QObject>
#include <QGraphicsRectItem>

class boardTile : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
    Colour tile_colour;
    QPoint position;
    bool selected;
public:
     boardTile(QObject *parent = nullptr);
     void setSelected();
     void setUnselected();
     void setPosition(QPoint pos);
     QPoint getPosition();
     void setTileColour(Colour colour);
public slots:
     void setDefaultColour();
};

#endif // BOARDTILE_H
