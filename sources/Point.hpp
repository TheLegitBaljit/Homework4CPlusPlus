#ifndef COWBOY_VS_NINJA_A_MAIN_POINT_H
#define COWBOY_VS_NINJA_A_MAIN_POINT_H

#include "iostream"
#include "cmath"
namespace ariel{}

class Point {
public:

    double x_val;
    double y_val;

    //Constructors
    Point();
    Point(double x_val, double y_val);

    double distance(const Point &other) const;
    void print();
    double getX();
    double getY();
    static Point moveTowards(const Point& source, const Point& destination, double distance);
};




#endif //COWBOY_VS_NINJA_A_MAIN_POINT_H
