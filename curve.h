#ifndef CURVE_H
#define CURVE_H
#include"figure.h"
#include"line.h"


class Curve:public Figure

{
public:
    Curve(int , int, QPen);
    void draw(QPainter* );
    void resize(double,double);
    void addline(int , int);
    void move(int , int);
    void setSize(int ,int)
    {

    }
private:
    std::vector<double>::iterator itx,ity;
    std::vector <double> X;
    std::vector <double> Y;





};

#endif // CURVE_H

