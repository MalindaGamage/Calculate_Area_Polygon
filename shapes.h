#ifndef SHAPE_H
#define SHAPE_H

#include <iostream>
#include <vector>
#include <cmath>
#include <string> // Ensure this is included

struct Point {
    int x, y;
    Point(int x, int y) : x(x), y(y) {}
};

class Shape {
public:
    std::string name;
    std::vector<Point> points;

    Shape(std::string name, std::vector<Point> points);
    void print() const;
    double area() const;
    bool is_point_inside(const Point& p) const;
    bool overlaps_with(const Shape& other) const;
};

#endif // SHAPE_H