#ifndef BOARDTILE_H
#define BOARDTILE_H

#include <QObject>
#include <QGraphicsRectItem>

class boardTile : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
     boardTile(QObject *parent = nullptr);

signals:

};

#endif // BOARDTILE_H
