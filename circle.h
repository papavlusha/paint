#ifndef CIRCLE_H
#define CIRCLE_H
#include"figure.h"

class Circle:public Figure
{
public:
    Circle();
    Circle(int , int  , int ,int,QPen);
    void draw(QPainter* );
    void resize(double,double);
    void move(int , int);
    void setSize(int x, int y)
    {
        radius1 = x/2;
        radius2 = y/2;
        radius1 = y;
        radius2 = y;
    }

private:
    double X,Y;
    double radius1,radius2;

};

#endif // CIRCLE_H


