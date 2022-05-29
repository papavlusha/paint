#include "rectangle.h"
#include <cmath>

using namespace std;

Rectangle::Rectangle()
{
}
Rectangle::Rectangle(int a, int b, int c, int d,QPen p)
{
    A = a;
    B = b;
    C = c;
    D = d;
    pen = p;
    degree = 0;
}
void Rectangle::draw(QPainter *p)
{
           QPainterPath path;
           p->translate(A,B);
           p->setPen(pen);
           path.addRect(0,0,C,D);
           p->rotate(degree);
           p->drawPath(path);
            p->rotate(-degree);
           p->translate(-A,-B);
}

void Rectangle::resize(double w , double h )
{
    A*=w;
    B*=h;
    C*=w;
    D*=h;
}

void Rectangle::move(int x, int y)
{
    A = x;
    B = y;
}
