#include <iostream>
#include <string>

#include "glut.h"
#include "geometry.h"

using namespace std;

/*
    Сначала указываем на массив с фигурами
    Потом Указываем на номер в массиве

    0 - Point, точка на плоскости
    1 - Line, прямая
    2 - Shape, фигура
    3 - Polygon, многоугольник
    4 - Ellipse, эллипс
    5 - Circle, круг
    6 - Rectangle, прямоугольник
    7 - Square, квадрат
    8 - Triangle, треугольник
*/
int main() {
    vector<pair<int, int>> list = { {0, 0}, {1, 1}, {3,  0} };

    vector<Point> pointList = { Point(1.0, 1.0), Point(2.9, 2.1) };
    vector<Line> lineList = { Line(Point(1.0, 1.0), Point(2.0, 2.0)), Line(5, 5) };
    vector<Shape> shapeList;
    vector<Shape> polygonList = {Polygon({1.0, 2.0, 3.0})};
    vector<Shape> ellipseList = {Ellipse( Point(1.0, 2.0), Point(2.0, 5.0), 5) };
    vector<Shape> circleList = { Circle(Point(1.0, 6.0), 5) };
    vector<Shape> rectangleList;
    vector<Shape> squareList;
    vector<Shape> triangleList;

    int id;
    cin >> id;

    id--;



    return 0;
}
