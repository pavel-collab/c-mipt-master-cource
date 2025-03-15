#include "visitors.hpp"

#include <vector>

int main() {
    // Создаем фигуры
    std::vector<std::shared_ptr<Shape>> shapes;
    shapes.push_back(std::make_shared<Circle>(5.0));
    shapes.push_back(std::make_shared<Square>(4.0));
    shapes.push_back(std::make_shared<Triangle>(3.0, 4.0));

    // Создаем посетителей
    AreaVisitor areaVisitor;
    PerimeterVisitor perimeterVisitor;

    // Вычисляем площади и периметры
    for (auto& shape : shapes) {
        shape->accept(areaVisitor);
        shape->accept(perimeterVisitor);
    }

    return 0;
}