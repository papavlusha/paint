#ifndef RECTANGLE_H
#define RECTANGLE_H
#include"figure.h"

class Rectangle:public Figure
{
public:
    Rectangle();

    Rectangle(int a,int b ,int c, int d,QPen);
    void draw(QPainter* );
    void resize(double,double);
    void move(int , int);
    void setSize(int x, int y)
    {
        C = x;
        D = y;
    }

private:
    double A,B,C,D;
};

#endif // RECTANGLE_H
