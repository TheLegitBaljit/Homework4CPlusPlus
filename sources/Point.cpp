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

Point moveTowards(const Point &src ,const Point &destination, double distance) {
    if (distance < 0) {
        throw std::invalid_argument("Distance cannot be negative");
    }
    double dist = src.distance(destination);
    if (dist <= distance)
        return destination;
    double src_between = distance;
    double between_destination = dist - distance;
    double x_new = (between_destination * src.x_val + src_between * destination.x_val)/dist;
    double y_new = (between_destination * src.y_val + src_between * destination.y_val)/dist;
    return Point(x_new,y_new);
}


bool Point::operator==(const Point& other) const {
    double tolerance = 0.00001;
    return std::abs(x_val - other.x_val) < tolerance && std::abs(y_val - other.y_val) < tolerance;
}
double Point::getX() {
    return this->x_val;
}
double Point::getY() {
    return this->y_val;
}