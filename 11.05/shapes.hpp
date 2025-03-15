#pragma once

#include "visitor_interface.hpp"

class Shape {
public:
    virtual void accept(ShapeVisitor& visitor) = 0;
    virtual ~Shape() {}
};

class Circle : public Shape {
private:
    double radius;
public:
    Circle(double r) : radius(r) {}

    double getRadius() const { return radius; }

    void accept(ShapeVisitor& visitor) override {
        visitor.visit(*this);
    }
};

class Square : public Shape {
private:
    double side;
public:
    Square(double s) : side(s) {}

    double getSide() const { return side; }

    void accept(ShapeVisitor& visitor) override {
        visitor.visit(*this);
    }
};

class Triangle : public Shape {
private:
    double base;
    double height;
public:
    Triangle(double b, double h) : base(b), height(h) {}

    double getBase() const { return base; }
    double getHeight() const { return height; }

    void accept(ShapeVisitor& visitor) override {
        visitor.visit(*this);
    }
};