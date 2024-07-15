#include "shapes.h"

Shape::Shape(std::string name, std::vector<Point> points) : name(name), points(points) {
    // Constructor implementation
}

void Shape::print() const {
    std::cout << name << ": ";
    for (const auto& point : points) {
        std::cout << "(" << point.x << "," << point.y << ") ";
    }
    std::cout << std::endl;
}

double Shape::area() const {
    int n = points.size();
    if (n < 3) {
        std::cerr << "Error: A polygon must have at least 3 points to have an area.\n";
        return 0;
    }

    double area = 0;
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        double term = points[i].x * points[j].y - points[j].x * points[i].y;
        area += term;
    }
    area = std::abs(area) / 2.0;
    return area;
}

bool Shape::is_point_inside(const Point& p) const {
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

bool Shape::overlaps_with(const Shape& other) const {
    for (const auto& point : other.points) {
        if (is_point_inside(point)) {
            return true;
        }
    }
    return false;
}