#include "line.h"
#include <cmath>
#include<QDebug>

using namespace std;

Line::Line()
{

}

Line::Line(int x1,int y1,int x2,int y2,QPen p)
{
    X1 = x1;
    X2 = x2;
    Y1 = y1;
    Y2 = y2;
    pen=p;
    degree = 0;
}

void Line::draw(QPainter* p)
{
            QPainterPath path;
            p->translate(X1,Y1);
            path.moveTo(0,0);
            path.lineTo(X2-X1,Y2-Y1);
            p->rotate(degree);
            p->setPen(pen);
            p->drawPath(path);

            p->rotate(-degree);
            p->translate(-X1,-Y1);

}

void Line::resize(double w, double h)
{
    X1*=w;
    X2*=w;
    Y1*=h;
    Y2*=h;
}

void Line::move(int x, int y)
{
    double dx, dy;
    dx = X1 - x;
    dy = Y1 - y;
    X1 = x;
    Y1 = y;
    X2 -=dx;
    Y2 -=dy;
}
