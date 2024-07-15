#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "shapes.h"

Shape parse_shape(const std::string& line) {
    std::istringstream iss(line);
    std::string name;
    std::vector<Point> points;
    char ch;

    std::getline(iss, name, ',');
    if (iss >> ch && ch != '[') {
        std::cerr << "Error: Expected '[' after shape name" << std::endl;
        return Shape(name, points);
    }

    int x, y;
    while (iss >> ch) {
        if (ch == '(') {
            if (!(iss >> x >> ch) || ch != ',') {
                std::cerr << "Error: Expected ',' between point coordinates" << std::endl;
                return Shape(name, points);
            }
            if (!(iss >> y >> ch) || ch != ')') {
                std::cerr << "Error: Expected ')' after point coordinates" << std::endl;
                return Shape(name, points);
            }
            points.emplace_back(x, y);
            if (iss >> ch && ch == ',') {
                continue;
            }
            else if (ch == ']') {
                break;
            }
            else {
                std::cerr << "Error: Unexpected character while parsing points" << std::endl;
                return Shape(name, points);
            }
        }
        else {
            std::cerr << "Error: Unexpected character while parsing points" << std::endl;
            return Shape(name, points);
        }
    }

    return Shape(name, points);
}

std::vector<Shape> read_shapes_from_file(const std::string& filename) {
    std::vector<Shape> shapes;
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        Shape shape = parse_shape(line);
        shapes.push_back(shape);
    }
    return shapes;
}

int main() {
    std::vector<Point> points = { {80, 70}, {50, 200}, {190, 240}, {270, 120} };
    Shape test_shape("TEST_SHAPE", points);
    double testArea = test_shape.area();
    std::cout << "Test Shape Area: " << testArea << std::endl;

    std::vector<Shape> shapes = read_shapes_from_file("shapes.txt");

    for (const auto& shape : shapes) {
        double area = shape.area();
        std::cout << shape.name << ": Area = " << area << std::endl;
    }

    std::cout << "\nOverlapping Shapes:" << std::endl;
    for (size_t i = 0; i < shapes.size(); ++i) {
        for (size_t j = i + 1; j < shapes.size(); ++j) {
            if (shapes[i].overlaps_with(shapes[j])) {
                std::cout << shapes[i].name << " overlaps with " << shapes[j].name << std::endl;
            }
        }
    }

    return 0;
}