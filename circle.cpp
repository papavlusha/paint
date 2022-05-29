#include "circle.h"

Circle::Circle()
{

}

Circle::Circle(int x, int y , int r1,int r2,QPen p)
{
    X = x;
    Y = y;
    radius1 = r1;
    radius2 = r2;
    pen = p;
    degree = 0;
}

void Circle::draw(QPainter * p)
{
    QPainterPath path;
    p->translate(X,Y);
    p->rotate(degree);
    path.addEllipse(X-radius1,Y-radius2,radius1*2,radius2*2);
    p->setPen(pen);
    p->rotate(-degree);
    p->translate(-X,-Y);
    p->drawPath(path);
}

void Circle::resize(double w, double h)
{
    X*=w;
    Y*=h;
    radius1*=w;
    radius2*=h;
}

void Circle::move(int x, int y)
{
    X = x;
    Y = y;
}
