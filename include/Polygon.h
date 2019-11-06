#ifndef Polygon_H
#define Polygon_H
#include "line.h"
#include <vector>
template <typename T>
class Polygon
{
public:
    Polygon(int & id, std::vector<Point<T>> &points):id_(id),PolygonPoints_(std::move(points)){}
    Polygon(){}
    std::vector<Point<T>> PolygonPoints() const { return PolygonPoints_;}
    int id() const{     return id_; }
    void setPolygonPoints(const std::vector<Point<T>> & polygonPoints) { PolygonPoints_=polygonPoints;}
    void setId(int id){ id_=id;}

private:
    int id_;
    std::vector<Point<T>> PolygonPoints_;

};

#endif
