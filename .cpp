#ifndef SHAPE_H
#define SHAPE_H

#include <iostream>
#include <vector>
#include <cmath>
#include "shape.h"

struct Point {
    int x, y;
    Point(int x, int y) : x(x), y(y) {}
};

class Shape {
public:
    std::string name;
    std::vector<Point> points;

    Shape(std::string name, std::vector<Point> points) : name(name), points(points) {}

    void print() const {
        std::cout << name << ": ";
        for (const auto& point : points) {
            std::cout << "(" << point.x << "," << point.y << ") ";
        }
        std::cout << std::endl;
    }

    double area() const {
        double area = 0;
        int n = points.size();
        for (int i = 0; i < n; ++i) {
            int j = (i + 1) % n;
            area += points[i].x * points[j].y;
            area -= points[j].x * points[i].y;
        }
        return std::abs(area) / 2.0;
    }

    bool isPointInside(const Point& p) const {
        int n = points.size();
        bool inside = false;
        for (int i = 0, j = n - 1; i < n; j = i++) {
            if (((points[i].y > p.y) != (points[j].y > p.y)) &&
                (p.x < (points[j].x - points[i].x) * (p.y - points[i].y) / (points[j].y - points[i].y) + points[i].x)) {
                inside = !inside;
            }
        }
        return inside;
    }

    bool overlapsWith(const Shape& other) const {
        for (const auto& point : other.points) {
            if (isPointInside(point)) {
                return true;
            }
        }
        return false;
    }
};

#endif // SHAPE_H
