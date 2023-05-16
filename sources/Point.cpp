#include "Point.hpp"

Point::Point() {
    this->x_val = 0;
    this->y_val = 0;
}

Point::Point(double x, double y) {
    this->x_val = x;
    this->y_val = y;
}


double Point::distance(const Point &other) const {
    return sqrt(pow(this->x_val - other.x_val, 2) + pow(this->y_val - other.y_val, 2));
}

void Point::print() {
    std::cout << "(" << this->x_val << "," << this->y_val << ")";
}

Point Point::moveTowards(const Point &_p1, const Point &_p2, double dist) {
    if(dist < 0)
        throw std::invalid_argument("Cannot move negative distance");
    double distance = _p1.distance(_p2);
    if (distance <= dist) {
        return _p2;
    }
    double distx = _p2.x_val - _p1.x_val;
    double disty = _p2.y_val - _p1.y_val;
    double factor = dist / distance;
    double new_X = _p1.x_val + distx * factor;
    double new_Y = _p1.y_val + disty * factor;

    return Point(new_X, new_Y);
}

double Point::getX() {
    return this->x_val;
}
double Point::getY() {
    return this->y_val;
}