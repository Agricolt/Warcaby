#ifndef LIST_H
#define LIST_H

#include <iostream>

class list
{
    struct el
    {
        int x1, x2, y1, y2;
        el* pNext;
        el(int x1, int x2, int y1, int y2);
    };
    el* pHead;
public:
    list() : pHead(nullptr) {};
    ~list();
    void add(int x1, int x2, int y1, int y2);
    bool find();
    void print();

};

#endif // LIST_H
