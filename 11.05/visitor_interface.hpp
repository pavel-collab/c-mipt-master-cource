#pragma once

class Circle;
class Square;
class Triangle;

class ShapeVisitor {
public:
    virtual void visit(Circle& circle) = 0;
    virtual void visit(Square& square) = 0;
    virtual void visit(Triangle& triangle) = 0;
};