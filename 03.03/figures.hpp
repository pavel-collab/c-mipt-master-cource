#ifndef FIGURES_H
#define FIGURES_H

#include <cmath>

/*
 * Вообще-то говоря, наследовать квадрат от прямоугольника -- некорректно. Так же, как наследовать прямоугольник от квадрата.
 * Эта проблема известна как Circle-ellipse problem. https://en.wikipedia.org/wiki/Circle%E2%80%93ellipse_problem
 * При наследовании одного класса от другого должны выполняться 2 условияЖ
 * 1) Dirived -- частный случай Base
 * 2) Derived расширяет Base
 * В нашем случае это не выполнено. Если мы наследуем квадрат от прямоугольника, он является его частным случаем, но не расширяет его
 * (у структуры эллипс больше полей). Если наследовать эллипс от квадрата, но это не будет чустным случаем.
 * 
 * Однако в данном случае на проблему можно скрипя сердцем закрыть глаза по следующей причине:
 * принцып подстановки Лисков (принципы SOLID) гласит: типы Base и Derived связаны отношением is-a, если любой интересующий нас
 * предикат относительно Base остается истиным при подстановке в Derived. Таким образом, если не писать, например, функций стретчинга в 
 * этих классах, то ничего страшного не произойдет, относительно ИНТЕРЕСУЮЩЕЙ НАС функциональности -- все нормально.
 */

#define TRIANGLE_SIDES_NUM 3

#define RECTANGLE_SIDES_NUM 4

class Shape
{
public:
    virtual ~Shape() {}

    virtual double GetSquare() const = 0;
    
    virtual double GetPerimetr() const = 0;
};

class Polygon : public Shape
{
    int sides_num_;

public:
    Polygon (int sides_num) : sides_num_(sides_num) {}

    virtual ~Polygon () = default;
};

class Triangle final : public Polygon
{
    double side_a_, side_b_, side_c_;

public:
    Triangle (double a, double b, double c) : Polygon(TRIANGLE_SIDES_NUM), side_a_(a), side_b_(b), side_c_(c) {}

    double GetPerimetr() const override
    {
        return side_a_ + side_b_ + side_c_;
    }

    double GetSquare() const override
    {
        // формула Герона
        double half_perimetr = GetPerimetr() / 2;
        return std::sqrt (half_perimetr * (half_perimetr - side_a_) * (half_perimetr - side_b_) * (half_perimetr - side_c_));
    }
};


class Rectangle : public Polygon
{
    double width_, height_;

public:
    Rectangle (double width, double height) : Polygon (RECTANGLE_SIDES_NUM), width_(width), height_(height) {}

    double GetPerimetr() const override
    {
        return 2 * (width_ + height_);
    }

    double GetSquare() const override
    {
        return width_ * height_;
    }

    virtual ~Rectangle () = default;
};

struct Square final : public Rectangle
{
    Square (double side) : Rectangle (side, side) {}
};

class Ellipse : public Shape
{
    double major_axis_, minor_axis_;

public:
    Ellipse (double major_axis, double minor_axis) : major_axis_(major_axis), minor_axis_(minor_axis) {}

    double GetPerimetr() const override
    {
        return std::numbers::pi * major_axis_ * minor_axis_;
    }

    double GetSquare() const override
    {
        return 4 * (GetPerimetr() + (major_axis_ - minor_axis_) * (major_axis_ - minor_axis_)) / (major_axis_ + minor_axis_);
    }

    virtual ~Ellipse () = default;
};

struct Circle final : public Ellipse
{
    Circle (double radius) : Ellipse (radius, radius) {}
};

#endif // FIGURES_H