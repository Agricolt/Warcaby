#include "boardtile.h"

boardTile::boardTile(QObject *parent) : QObject(parent)
{
    this->setRect(0, 0, 50, 50);
}
