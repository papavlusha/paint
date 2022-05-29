#include "curve.h"

Curve::Curve(int x, int y , QPen p)
{
    degree = 0;
    pen = p;
    X.push_back(x);
    Y.push_back(y);
}

void Curve::draw(QPainter *p)
{

    QPainterPath path;
    p->translate(X[0],Y[0]);
    path.moveTo(0,0);
    p->rotate(degree);
    p->setPen(pen);

    itx = X.begin();
    ity = Y.begin();
    while(itx!=X.end())
    {
        path.lineTo((*itx++)-X[0],(*ity++)-Y[0]);
        p->drawPath(path);
    }
    p->rotate(-degree);
    p->translate(-X[0],-Y[0]);
}

void Curve::resize(double A, double b)
{

    itx = X.begin();
    ity = Y.begin();
    while(itx!=X.end())
    {
        *itx++*=A;
        *ity++*=b;
    }

}

void Curve::addline(int x, int y)
{

    X.push_back(x);
    Y.push_back(y);
}

void Curve::move(int x, int y)
{
    double dx, dy;
    dx = X[0] - x;
    dy = Y[0] - y;
    itx = X.begin();
    ity = Y.begin();
    while(itx!=X.end())
    {
        *itx++-=dx;
        *ity++-=dy;
    }
}
