#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <QPoint>

class lista
{
public:
    struct el
    {
        QPoint from, where;
        el* pNext;
        el(QPoint from, QPoint where);
    };
private:
    el* pHead;
public:
    lista();
    ~lista();
    void add(QPoint from, QPoint where);
    void add(lista::el*);
    bool find(QPoint from, QPoint where);
    bool isEmpty();
    void print();
};

#endif // LIST_H
