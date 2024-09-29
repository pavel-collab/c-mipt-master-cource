#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

class Point {
    float m_x;
    float m_y;
public:
    Point(float x, float y) : m_x(x), m_y(y) {};

    float X() {return m_x;};
    float Y() {return m_y;};
}; 

class Rectangle {
    Point m_left_bottom_corn;
    float m_width;
    float m_hight;
public:
    Rectangle(float x, 
              float y,
              float width,
              float hight) : m_left_bottom_corn(x, y), m_width(width), m_hight(hight) {}; 

    float X() {return m_left_bottom_corn.X();};
    float Y() {return m_left_bottom_corn.Y();};

    std::unordered_map<std::string, Point> GetLocation() {
        float x = X();
        float y = Y();
        
        std::unordered_map<std::string, Point> location;
        location.insert({"left bottom", m_left_bottom_corn});
        location.insert({"right top", Point(x + m_width, y + m_hight)});
        return location;
    }

    float GetSpace() {
        return m_width * m_hight;
    }
};

Rectangle Get2RecIntersection(Rectangle first, Rectangle second) {
    std::unordered_map<std::string, Point> first_cordinates = first.GetLocation();
    std::unordered_map<std::string, Point> second_cordinates = second.GetLocation();

    float x1 = first_cordinates["left bottom"].X();
    float y1 = first_cordinates["left bottom"].Y();
    float x2 = first_cordinates["right top"].X();
    float y2 = first_cordinates["right top"].Y();
    float x3 = second_cordinates["left bottom"].X();
    float y3 = second_cordinates["left bottom"].Y();
    float x4 = second_cordinates["right top"].X();
    float y4 = second_cordinates["right top"].Y();

    float left = std::max(x1, x3);
    float right = std::min(x2, x4);
    float top = std::min(y2, y4);
    float bottom = std::max(y1, y3);

    return Rectangle(left, bottom, right-left, top-bottom);
}

float GetRectanglesIntersection(std::vector<Rectangle> rectangles) {
    while (rectangles.size() > 1) {
        Rectangle first = rectangles[0];
        Rectangle second = rectangles[1];

        rectangles.erase(rectangles.begin());
        rectangles.erase(rectangles.begin());

        rectangles.push_back(Get2RecIntersection(first, second));
    }

    return rectangles[0].GetSpace();
}

int main() {

}