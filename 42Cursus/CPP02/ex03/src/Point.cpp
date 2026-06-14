#include "Point.hpp"

Point::Point(void) : _x(0), _y(0) {
}

Point::Point(const float& a, const float& b) : _x(a), _y(b) {
}

Point::Point(const Point& other) : _x(other._x), _y(other._y) {
}

Point& Point::operator=(const Point& other) {
    if (this != &other)
        return *this;
    return *this;
}

Point::~Point() {
}

Fixed Point::getX(void) const {
    return _x;
}

Fixed Point::getY(void) const {
    return _y;
}

Fixed posPointLine (Point const a, Point const b, Point const p) {
    return (b.getX() - a.getX()) * (p.getY() - a.getY()) - (b.getY() - a.getY()) * (p.getX() - a.getX()); 
}

bool bsp(Point const a, Point const b, Point const c, Point const point) {
    Fixed pointToAB = posPointLine(a, b, point);
    Fixed pointToBC = posPointLine(b, c, point);
    Fixed pointToCA = posPointLine(c, a, point);

    if (pointToAB > 0 && pointToBC > 0 && pointToCA > 0)
        return true;
    if (pointToAB < 0 && pointToBC < 0 && pointToCA < 0)
        return true;
    return false;
}