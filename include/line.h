#ifndef LINE_H
#define LINE_H

#include "point.h"
#include <utility>
template <typename T>
class Line
{
public:
    Line(Point<T> &p1,Point<T> &p2,int id_):id(id_),p1_(p1),p2_(p2)
      {
          evalKoeffs();
      }
    Line(){}
    double getA() const{
        return A;
    }
    double getB() const{
        return B;
    }
    double getC() const{
        return C;
    }
    int getId() const{return id;}
    Point<T> getP1() const{return p1_;}
    Point<T> getP2() const{return p2_;}

    void setId(int value){id=value;}
    void setPoints(Point<T> &p1,Point<T> &p2)
    {
        p1_=p1,p2_=p2;
        evalKoeffs();
    }

private:
    void evalKoeffs(){
        A=p2_.getY()-p1_.getY();
        B=p1_.getX()-p2_.getX();
        C=-p1_.getX()*(p2_.getY()-p1_.getY())+p1_.getY()*(p2_.getX()-p1_.getX());
    }
    double A,B,C;
    int id;
    Point<T> p1_,p2_;
};


#endif // LINE_H
