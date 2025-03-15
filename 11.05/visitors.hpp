#pragma once

#include "shapes.hpp"
#include "visitor_interface.hpp"
#include <iostream>

class AreaVisitor : public ShapeVisitor {
public:
    void visit(Circle& circle) override {
        double area = 3.14159 * circle.getRadius() * circle.getRadius();
        std::cout << "Circle area: " << area << std::endl;
    }

    void visit(Square& square) override {
        double area = square.getSide() * square.getSide();
        std::cout << "Square area: " << area << std::endl;
    }

    void visit(Triangle& triangle) override {
        double area = 0.5 * triangle.getBase() * triangle.getHeight();
        std::cout << "Triangle area: " << area << std::endl;
    }
};

class PerimeterVisitor : public ShapeVisitor {
public:
    void visit(Circle& circle) override {
        double perimeter = 2 * 3.14159 * circle.getRadius();
        std::cout << "Circle perimeter: " << perimeter << std::endl;
    }

    void visit(Square& square) override {
        double perimeter = 4 * square.getSide();
        std::cout << "Square perimeter: " << perimeter << std::endl;
    }

    void visit(Triangle& triangle) override {
        // Для простоты, предполагаем, что все стороны равны
        double perimeter = 3 * triangle.getBase();
        std::cout << "Triangle perimeter: " << perimeter << std::endl;
    }
};