#include "lista.h"

lista::lista()
    : pHead(nullptr)
{}

void lista::add(QPoint from, QPoint where)
{
    lista::el *el = new lista::el(from, where);
    if (pHead == nullptr)
    {
        pHead =el;
        el->pNext = nullptr;
    }
    else
    { 
        lista::el* pIter = this->pHead;
        while (pIter->pNext != nullptr)
        {
            pIter = pIter->pNext;
        }
        pIter->pNext = el;
        el->pNext = nullptr;

    }
}

bool lista::find(QPoint from, QPoint where)
{
    lista::el *iter = pHead;
    while (iter !=nullptr)
    {
        if (iter->from == from && iter->where == where)
            return true;
        iter = iter->pNext;
    }
    return false;
}

bool lista::isEmpty()
{
    if (this->pHead == nullptr)
        return true;
    return false;
}

void lista::print()
{
    lista::el *iter = pHead;
    while (iter != nullptr)
    {
        std::cout << iter->from.x() << ";" << iter->from.y() << ", " << iter->where.x() << ";" << iter->where.y() << std::endl;
        iter = iter->pNext;
    }
}

lista::el::el(QPoint from, QPoint where)
{
    this->from = from;
    this->where = where;
    this->pNext = nullptr;
}
