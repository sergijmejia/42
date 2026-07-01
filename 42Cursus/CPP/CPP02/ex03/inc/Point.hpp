#ifndef POINT_HPP
# define POINT_HPP

# include "Fixed.hpp"

class Point {
    private:
        const Fixed _x;
        const Fixed _y;
    
    public:
        Point();
        Point(const float& a, const float& b);
        Point(const Point& other);
        Point& operator=(const Point& other);
        ~Point();

        Fixed getX(void) const;
        Fixed getY(void) const;
};

Fixed posPointLine (Point const a, Point const b, Point const p);
bool bsp(Point const a, Point const b, Point const c, Point const point);

#endif