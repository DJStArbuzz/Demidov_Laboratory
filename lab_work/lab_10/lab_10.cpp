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
        cout << "Drawing a shape" << '\n';
    }

    // Периметр
    virtual double perimeter() const = 0;
    
    // Площадь
    virtual double area() const = 0;
    
    // Совпадает ли эта фигура с другой
    virtual bool operator==(const Shape& other) const = 0;
    
    // Равна ли эта фигура другой в геометрическом смысле
    virtual bool isCongruentTo(const Shape& other) const = 0;
    
    // Подобна ли эта фигура другой
    virtual bool isSimilarTo(const Shape& other) const = 0;
    
    // Находится ли эта точка внутри фигуры
    virtual bool containsPoint(Point point) const = 0;

    // Поворот на угол (в градусах, против часовой стрелки)
    virtual void rotate(Point center, double angle) = 0;

    // Симметрично относительно точки
    virtual void reflex(Point center) = 0;

    // Симметрично относительно прямой
    virtual void reflex(Line axis) = 0;

    // Гомотетию с коэффициентом и центром
    virtual void scale(Point center, double coefficient) = 0;
};

// Класс Polygon — многоугольник. Многоугольник — частный случай фигуры.
class Polygon : public Shape {
private:
    vector<Point> vertices;

public:
    // Можно сконструировать многоугольник из вектора точек - вершин в порядке обхода.
    Polygon(const vector<Point>& points) : vertices(points) {}

    // Можно сконструировать многоугольник из точек, передаваемых в качестве параметров через запятую
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
        return true;
    }

    double perimeter() const override {
    }

    double area() const override {
    }

    bool operator==(const Shape& other) const override {
    }

    bool isCongruentTo(const Shape& other) const override {
    }

    bool isSimilarTo(const Shape& other) const override {
    }

    bool containsPoint(Point point) const override {
    }

    void rotate(Point center, double angle) override {
    }

    void reflex(Point center) override {
    }

    void reflex(Line axis) override {
    }

    void scale(Point center, double coefficient) override {
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
    void draw() override {
       cout << "Drawing a circle" << '\n';
    }
};

// Класс Rectangle — прямоугольник. Прямоугольник — частный случай многоугольника.
class Rectangle : public Polygon {
public:
    /*
    Прямоугольник можно сконструировать
по двум точкам (его противоположным вершинам) и числу (отношению смежных
сторон), причем из двух таких прямоугольников выбирается тот, у которого более
короткая сторона расположена по левую сторону от диагонали, если смотреть от
первой заданной точки в направлении второй.
    */

    // Центр прямоугольника
    Point center() {
        // calculate and return the center of the rectangle
    }

    // Пара его диагоналей
    pair<Line, Line> diagonals() {
        // calculate and return the diagonals of the rectangle
    }
};

// Класс Square — квадрат. Квадрат — частный случай прямоугольника.
class Square : public Rectangle {
public:
    // Квадрат можно задать двумя точками — противоположными вершинами.

    Circle circumscribedCircle() {
        // calculate and return the circumscribed circle of the square
    }

    Circle inscribedCircle() {
        // calculate and return the inscribed circle of the square
    }

    void draw() override {
        cout << "Drawing a square" << '\n';
    }
};

// Класс Triangle — треугольник. Треугольник — частный случай многоугольника.
class Triangle : public Polygon {
public:
    // Центр масс
    Circle circumscribedCircle() {
        // calculate and return the circumscribed circle of the triangle
    }

    // Центр масс
    Circle inscribedCircle() {
        // calculate and return the inscribed circle of the triangle
    }

    // Центр масс
    Point centroid() {
        // calculate and return the centroid of the triangle
    }

    // Ортоцентр
    Point orthocenter() {
        // calculate and return the orthocenter of the triangle
    }

    // Прямая Эйлера
    Line EulerLine() {
        // calculate and return the Euler line of the triangle
    }

    // Окружность Эйлера
    Circle ninePointsCircle() {
        // calculate and return the nine points circle of the triangle
    }
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
