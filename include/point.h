#ifndef POINT_H
#define POINT_H

template <typename T>
class Point
{
public:
    Point(T x_, T y_):x(x_),y(y_)
    {

    }
    Point(){}
    T getX() const
    {
     return x;
    }
    T getY() const
    {
        return y;
    }
    Point operator -(Point&p)
    {
        Point tmp(*this);
        tmp.x=x-p.getX();
        tmp.y=y-p.getY();
        return tmp;
    }

    Point operator +(Point&p)
    {
        Point tmp(*this);
        tmp.x=x+p.getX();
        tmp.y=y+p.getY();
        return tmp;
    }

    void setX(T value)
    {
        x = value;
    }

    void setY(T value)
    {
        y = value;
    }


private:
    T x;
    T y;
};


#endif // POINT_H
