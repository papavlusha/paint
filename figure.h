#ifndef FIGURE_H
#define FIGURE_H
#include<QPoint>
#include<QPainter>
#include<QPainterPath>


class Figure
{
public:
    Figure();
    virtual void draw(QPainter* ) = 0;
    virtual void resize(double,double) = 0;
    virtual void move(int , int) = 0;
    virtual void setSize(int , int) = 0;
    void setPenW(int a)
    {
        pen.setWidth( a);
    }
    QPen pen;
    int degree;
};

#endif // FIGURE_H


