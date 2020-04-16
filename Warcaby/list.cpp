#include "list.h"

void list::add(int x1, int x2, int y1, int y2)
{
    list::el *el = new list::el(x1, x2, y1, y2);
    if (pHead == nullptr)
    {
        pHead =el;
        el->pNext = nullptr;
    }
    else
    { 
        list::el* pIter = this->pHead;
        while (pIter->pNext != nullptr)
        {
            pIter = pIter->pNext;
        }
        pIter->pNext = el;
        el->pNext = nullptr;

    }
}

void list::print()
{
    list::el *iter = pHead;
    while (iter != nullptr)
    {
        std::cout << iter->x1 << ";" << iter->x2 << ", " << iter->y1 << ";" << iter->y2 << std::endl;
    }
}

list::el::el(int x1, int x2, int y1, int y2)
{
    this->x1 = x1;
    this->x2 = x2;
    this->y1 = y1;
    this->y2 = y2;
    this->pNext = nullptr;
}
