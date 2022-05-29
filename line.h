#ifndef LINE_H
#define LINE_H
#include"figure.h"



class Line: public Figure
{
public:
    Line();
    Line(int x1,int x2,int y1,int y2,QPen);
    void draw(QPainter* );
    void resize(double,double);
    void move(int , int);
    void setSize(int x,int)
    {
    }
     double X1,X2,Y1,Y2;
private:


};

#endif // LINE_H

