#ifndef VECTORLIB_H
#define VECTORLIB_H

#include "line.h"
#include <map>
#include <vector>

#include "Polygon.h"

template<typename T>
auto vector_mult(Point<T> &a, Point<T> &b)
{
    return a.getX()*b.getY()+a.getY()*b.getX();
}

template<typename T>
bool areCrossing(Point<T> &p1, Point<T> &p2, Point<T> &p3, Point<T> &p4)
{
    auto v1 = vector_mult(p4-p3, p1-p3);
    auto v2 = vector_mult(p4-p3, p3- p2);
    auto v3 = vector_mult(p2-p1, p3-p1);
    auto v4 = vector_mult(p2- p1, p4-p1);
    if ( (v1*v2)<0 && (v3*v4)<0 )
        return true;
    return false;
}

template<typename T>

Point<T> CrossingPoint(Line<T> &l1,Line<T> &l2)
{
    auto d=(l1.getA()*l2.getB()-l1.getB()*l2.getA());
    auto dx=(-l1.getC()*l2.getB()+l1.getB()*l2.getC());
    auto dy=(-l1.getA()*l2.getC()+l1.getC()*l2.getA());
    auto X=(dx/d);
    auto Y=(dy/d);
    return Point<T>(X,Y);
}

template<typename T>
int IsPointInsidePolygon (std::vector<Point<T>> &p, int Number, int x, int y)
{
    int i1, i2, n, N, S, S1, S2, S3, flag;
    N = Number;
    for (n=0; n<N; n++)
    {
        flag = 0;
        i1 = n < N-1 ? n + 1 : 0;
        while (flag == 0)
        {
            i2 = i1 + 1;
            if (i2 >= N)
                i2 = 0;
            if (i2 == (n < N-1 ? n + 1 : 0))
                break;
            S = abs (p[i1].getX() * (p[i2].getY() - p[n ].getY()) +
                     p[i2].getX() * (p[n ].getY() - p[i1].getY()) +
                     p[n].getX()  * (p[i1].getY() - p[i2].getY()));
            S1 = abs (p[i1].getX() * (p[i2].getY() - y) +
                      p[i2].getX() * (y       - p[i1].getY()) +
                      x       * (p[i1].getY() - p[i2].getY()));
            S2 = abs (p[n ].getX() * (p[i2].getY() - y) +
                      p[i2].getX() * (y       - p[n ].getY()) +
                      x       * (p[n ].getY() - p[i2].getY()));
            S3 = abs (p[i1].getX() * (p[n ].getY() - y) +
                      p[n ].getX() * (y       - p[i1].getY()) +
                      x       * (p[i1].getY() - p[n ].getY()));
            if (S == S1 + S2 + S3)
            {
                flag = 1;
                break;
            }
            i1 = i1 + 1;
            if (i1 >= N)
                i1 = 0;
        }
        if (flag == 0)
            break;
    }
    return flag;

}

#endif // VECTORLIB_H
