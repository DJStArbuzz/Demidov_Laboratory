#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <queue>
#include <set>
#include <cmath>

using namespace std;

// Структура Point — точка на плоскости.
struct Point {
    // Точку можно задать двумя числами типа double.
    // Должны быть открыты поля x и y.
    double x, y; 

    // Точки можно сравнивать операторами == и != .
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
    bool operator!=(const Point& other) const {
        return !(*this == other);
    }
};

// Класс Line — прямая.
class Line {
private:
    double a, b, c;

public:
    // Прямую можно задать двумя точками
    Line(Point p1, Point p2) {
        a = p2.y - p1.y;
        b = p1.x - p2.x;
        c = p2.x * p1.y - p1.x * p2.y;
    }

    // можно двумя числами(угловой коэффициент и сдвиг)
    Line(double slope, double shift) {
        a = -slope;
        b = 1;
        c = -shift;
    }

    // можно точкой и числом (угловой коэффициент).
    Line(Point p, double slope) {
        a = -slope;
        b = 1;
        c = -slope * p.x + p.y;
    }

    // Линии можно сравнивать операторами == и !=.
    bool operator==(const Line& other) const {
        return a == other.a && b == other.b && c == other.c;
    }
    bool operator!=(const Line& other) const {
        return !(*this == other);
    }
};

// Абстрактный класс Shape — фигура.
class Shape {
public:
    virtual void draw() {
        std::cout << "Drawing a shape" << '\n';
    }

    virtual double perimeter() const = 0;
    virtual double area() const = 0;
    virtual bool operator==(const Shape& other) const = 0;
    virtual bool isCongruentTo(const Shape& other) const = 0;
    virtual bool isSimilarTo(const Shape& other) const = 0;
    virtual bool containsPoint(Point point) const = 0;

    virtual void rotate(Point center, double angle) = 0;
    virtual void reflex(Point center) = 0;
    virtual void reflex(Line axis) = 0;
    virtual void scale(Point center, double coefficient) = 0;
};

// Класс Polygon — многоугольник. Многоугольник — частный случай фигуры.
class Polygon : public Shape {
private:
    vector<Point> vertices;

public:
    Polygon(const vector<Point>& points) : vertices(points) {}

    Polygon(Point p1, Point p2, Point p3) {
        vertices.push_back(p1);
        vertices.push_back(p2);
        vertices.push_back(p3);
    }

    // У многоугольника можно спросить verticesCount() — количество вершин
    int verticesCount() const {
        return vertices.size();
    }

    // У многоугольника можно спросить сами вершины без возможности изменения.
    const vector<Point>& getVertices() const {
        return vertices;
    }

    // Можно спросить isConvex() — выпуклый ли.
    bool isConvex() const {
        // Check for convexity
    }

    double perimeter() const override {
        // Calculate perimeter
    }

    double area() const override {
        // Calculate area
    }

    bool operator==(const Shape& other) const override {
        // Implement comparison
    }

    bool isCongruentTo(const Shape& other) const override {
        // Implement congruence check
    }

    bool isSimilarTo(const Shape& other) const override {
        // Implement similarity check
    }

    bool containsPoint(Point point) const override {
        // Implement point containment check
    }

    void rotate(Point center, double angle) override {
        // Implement rotation
    }

    void reflex(Point center) override {
        // Implement reflection
    }

    void reflex(Line axis) override {
        // Implement reflection
    }

    void scale(Point center, double coefficient) override {
        // Implement scaling
    }
};

// Класс Ellipse — эллипс. Эллипс — частный случай фигуры.
class Ellipse : public Shape {
private:
    Point focus1, focus2;
    // Other parameters

public:
    Ellipse(Point f1, Point f2, double sumDistances) : focus1(f1), focus2(f2) {
        // Construct ellipse
    }

    std::pair<Point, Point> focuses() const {
        return { focus1, focus2 };
    }

    std::pair<Line, Line> directrices() const {
        // Calculate directrices
    }

    double eccentricity() const {
        // Calculate eccentricity
    }

    Point center() const {
        // Calculate center
    }

    double perimeter() const override {
        // Calculate perimeter
    }

    double area() const override {
        // Calculate area
    }

    bool operator==(const Shape& other) const override {
        // Implement comparison
    }

    bool isCongruentTo(const Shape& other) const override {
        // Implement congruence check
    }

    bool isSimilarTo(const Shape& other) const override {
        // Implement similarity check
    }

    bool containsPoint(Point point) const override {
        // Implement point containment check
    }

    void rotate(Point center, double angle) override {
        // Implement rotation
    }

    void reflex(Point center) override {
        // Implement reflection
    }

    void reflex(Line axis) override {
        // Implement reflection
    }

    void scale(Point center, double coefficient) override {
        // Implement scaling
    }
};

// Класс Circle — круг. Круг — частный случай эллипса.
class Circle : public Ellipse {
public:
    // Implementation of Circle class
};

// Класс Rectangle — прямоугольник. Прямоугольник — частный случай многоугольника.
class Rectangle : public Polygon {
public:
    // Implementation of Rectangle class
};

// Класс Square — квадрат. Квадрат — частный случай прямоугольника.
class Square : public Rectangle {
public:
    // Implementation of Square class
};

// Класс Triangle — треугольник. Треугольник — частный случай многоугольника.
class Triangle : public Polygon {
public:
    /*
    У треугольника можно спросить Circle circumscribedCircle(), Circle inscribedCircle(),

Point centroid() — его центр масс, Point orthocenter() — его ортоцентр, Line EulerLine()
— его прямую Эйлера, Circle ninePointsCircle() — его окружность Эйлера.
    
    */
};

int main() {
	
    Point a, b;
    a.x = 1.50;
    a.y = 1.0;

    b.x = 1.5;
    b.y = 1.0;
    cout << (a == b);
	return 0;
}
