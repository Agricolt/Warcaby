#ifndef BOARDTILE_H
#define BOARDTILE_H

#include "CONSTANTS_ENUMS.h"
#include <QBrush>
#include <QGraphicsView>
#include <QObject>
#include <QGraphicsRectItem>

class boardTile : public QObject, public QGraphicsRectItem
{
    Colour tile_colour;
    QPoint position;
    bool selected;
    Q_OBJECT
public:
     boardTile(QObject *parent = nullptr);
     void setSelected();
     void setUnselected();
     void setPosition(QPoint pos);
     void setTileColour(Colour colour);

signals:

};

#endif // BOARDTILE_H
