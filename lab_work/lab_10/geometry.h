#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>

using namespace std;

const double epsilon = 1e-3;
const double PI = acos(-1);

bool equal(double first, double second) {
    return abs(first - second) < epsilon;
}

double deg_to_rad(double angle) {
    return (angle / 180) * PI;
}

double rad_to_deg(double angle) {
    return (angle / PI) * 180;
}

class Line;

// Структура Point — точка на плоскости.
struct Point {
    double x, y;    // Должны быть открыты поля x и y.

    // Начало координат
    Point() : x(0.0), y(0.0) {}

    // Точку можно задать двумя числами типа double.
    Point(double x, double y) : x(x), y(y) {}

    // Средняя точка
    Point(Point first, Point second) {
        x = (first.x + second.x) / 2;
        y = (first.y + second.y) / 2;

    }

    // поворот на угол (в градусах, против часовой стрелки) относительно точки;
    void rotate(const Point& center, double rad) {
        double x_2 = center.x + cos(rad) * (x - center.x) - sin(rad) * (y - center.y);
        double y_2 = center.y + sin(rad) * (x - center.x) + cos(rad) * (y - center.y);
        x = x_2;
        y = y_2;
    }

    // гомотетию с коэффициентом coefficient и центром center.
    /*
        Гомотетией с центром в точке О и коэффициентом k
        называется такое преобразование плоскости, при котором
        любая точка А переходит в точку А' такую, что OA' = kOA   
    */
    void scale(const Point& center, double coefficient) {
        x = (x - center.x) * coefficient + center.x;
        y = (y - center.y) * coefficient + center.y;
    }

    void reflect(const Point& center) {
        scale(center, -1);
    }

    void reflect(const Line&);
};

double operator*(const Point first, const Point second) {
    return first.x * second.x + first.y * second.y;
}

Point operator+(const Point first, const Point second) {
    return { first.x + second.x, first.y + second.y };
}

Point operator-(const Point first, const Point second) {
    return { first.x - second.x, first.y - second.y };
}

// Точки можно сравнивать операторами == и != .
bool operator==(const Point& first, const Point& second) {
    return equal(first.x, second.x) && equal(first.y, second.y);
}

bool operator!=(const Point& first, const Point& second) { return !(first == second); }

double dist(const Point& first, const Point& second) {
    return sqrt(pow((first.x - second.x), 2) + pow((first.y - second.y), 2));
}

double vecMultiply(const Point& first, const Point& second) {
    return first.x * second.y - first.y * second.x;
}

bool between(const Point& first, const Point& second, const Point target) {
    return (min(first.x, second.x) <= target.x) && 
           (max(first.x, second.x) >= target.x) &&
           (min(first.y, second.y) <= target.y) && 
           (max(first.y, second.y) >= target.y);
}

// Класс Line — прямая.
class Line {
public:
    double aLine;
    double bLine;
    double cLine;

private:
    void normalise() {
        if (!equal(bLine, 1.) && !equal(bLine, 0.)) {
            aLine /= bLine;
            cLine /= bLine;
            bLine = 1.;
        }
    }

    Line(double a, double b, double c) : aLine(a), bLine(b), cLine(c) {
        normalise();
    };

public:
    // Прямую можно задать двумя точками
    Line(const Point& first, const Point& second) {
        aLine = first.y - second.y;
        bLine = second.x - first.x;
        cLine = first.x * second.y - second.x * first.y;
        normalise();
    }

    // можно двумя числами(угловой коэффициент и сдвиг)
    Line(double k, double b) {
        aLine = -k;
        bLine = 1;
        cLine = -b;
    }

    // можно точкой и числом (угловой коэффициент)
    Line(const Point& point, double k) : aLine(-k), bLine(1) {
        cLine = point.x * k - point.y;
    }
};

// Линии можно сравнивать операторами == и !=.
bool operator==(const Line& first, const Line& second) {
    return equal(first.aLine, second.aLine) &&
        equal(first.bLine, second.bLine) &&
        equal(first.cLine, second.cLine);
}

bool operator!=(const Line& first, const Line& second) {
    return !(first == second);
}

Line orthogonal(const Line line, const Point axis = { 0, 0 }) {
    Point n_1 = Point(axis.x, axis.y);
    Point n_2 = Point(axis.x + line.aLine, axis.y + line.bLine);
    return { n_1, n_2 };
}

int type(const Line& first, const Line& second) {
    if (equal(first.bLine, 0)) {
        if (equal(second.bLine, 0)) {
            if (equal(first.aLine / first.cLine, second.aLine / second.cLine)) {
                return 0;
            }
            else {
                return -1;
            }
        }
        else {
            return 1;
        }
    }
    else {
        if (equal(second.bLine, 0)) {
            return 1;
        }
        else {
            if (equal(first.aLine / first.bLine, second.aLine / second.bLine)) {
                if (equal(first.cLine / first.bLine, second.cLine / second.bLine)) {
                    return 0;
                }
                else {
                    return -1;
                }
            }
        }
    }
    return 1;
}

Point intersect(const Line& first, const Line& second) {
    assert(!equal(first.aLine * second.bLine - second.aLine * first.bLine, 0));
    double x = (first.bLine * second.cLine - second.bLine * first.cLine) /
        (first.aLine * second.bLine - second.aLine * first.bLine);
    double y = (first.cLine * second.aLine - second.cLine * first.aLine) /
        (first.aLine * second.bLine - second.aLine * first.bLine);
    return { x, y };
}


void Point::reflect(const Line& line) {
    Line ort = orthogonal(line, *this);
    Point inter = intersect(line, ort);
    reflect(inter);
}

// Абстрактный класс Shape — фигура.
class Shape {
public:
    // периметр;
    virtual double perimeter() = 0;

    // площадь;
    virtual double area() const = 0;

    // совпадает ли эта фигура с другой;
    virtual bool operator==(const Shape& another) const = 0;

    // не совпадает ли эта фигура с другой;
    bool operator!=(const Shape& another) const {
        return !(*this == another);
    }

    // равна ли эта фигура другой в геометрическом смысле;
    virtual bool isCongruentTo(const Shape& another) const = 0;

    // подобна ли эта фигура другой;
    virtual bool isSimilarTo(const Shape& another) const = 0;

    // находится ли точка внутри фигуры.
    virtual bool containsPoint(const Point& point) const = 0;

    // поворот на угол (в градусах, против часовой стрелки) относительно точки;
    virtual void rotate(const Point& center, double angle) = 0;

    // симметрию относительно точки;
    virtual void reflect(const Point& center) = 0;

    // симметрию относительно прямой;
    virtual void reflect(const Line& axis) = 0;

    // гомотетию с коэффициентом coefficient и центром center.
    virtual void scale(const Point& center, double coefficient) = 0;

    virtual ~Shape() = default;
};

// Класс Polygon — многоугольник. 
// Многоугольник — частный случай фигуры.
class Polygon : public Shape {
protected:
    vector<Point> vertices;

    Point vert(int pos) const {
        int verCount = verticesCount();
        return vertices[((pos % verCount) + verCount) % verCount];
    }

public:
    void print() const {
        for (int i = 0; i < verticesCount(); ++i) {
            cout << '{' << vert(i).x << ", " << vert(i).y << "}, ";
        }
        cout << '\n';
    }

    // количество вершин
    int verticesCount() const {
        return vertices.size();
    }

    // сами вершины без возможности изменения.
    vector<Point> getVertices() const {
        vector<Point> ver = vertices;
        return ver;
    }

    // выпуклый ли он
    bool isConvex() const {
        bool flag = true;
        for (int i = 0; i < verticesCount(); ++i) {
            Point p_1 = vert(i) - vert(i + 1);
            Point p_2 = vert(i + 2) - vert(i + 1);
            if (vecMultiply(p_1, p_2) < 0) {
                flag = false;
                break;
            }
        }
        if (flag) {
            return true;
        }
        flag = true;
        for (int i = 0; i < verticesCount(); ++i) {
            Point p_1 = vert(i) - vert(i + 1);
            Point p_2 = vert(i + 2) - vert(i + 1);
            if (vecMultiply(p_2, p_1) < 0) {
                flag = false;
            }
        }
        if (flag) {
            return true;
        }
        return false;
    }

    Polygon(const vector<Point>& ver) : vertices(ver) {}

    template<typename... T>
    Polygon(T... points) : vertices({ points... }) {};

    double perimeter() override {
        if (vertices.size() <= 1) {
            return 0;
        }
        double su = 0;
        for (int i = 0; i < verticesCount(); ++i) {
            su += dist(vert(i - 1), vert(i));
        }
        return su;
    }

    double area() const override {
        double su = 0;
        int count = verticesCount();
        for (int i = 0; i < count; ++i) {
            su += vertices[i].x * vertices[(i + 1) % count].y -
                vertices[i].y * vertices[(i + 1) % count].x;
        }
        return fabsl(su / 2);
    }

    bool operator==(const Shape& another) const override {
        auto casted = dynamic_cast<const Polygon*>(&another);
        if (casted == nullptr || casted->verticesCount() != verticesCount()) {
            return false;
        }
        else {
            bool flag;
            int count = verticesCount();
            for (int k = -1; k < 2; k += 2) {
                for (int i = 0; i < count; ++i) {
                    flag = true;
                    for (int j = 0; j < count; ++j) {
                        if (vert(j) != casted->vert((i + j) * k)) {
                            flag = false;
                            break;
                        }
                    }
                    if (flag) {
                        return true;
                    }
                }
            }
            return false;
        }
    }

    bool isCongruentTo(const Shape& another) const override {
        bool f_1 = isSimilarTo(another);
        bool f_2 = equal(another.area(), area());
        bool flag = f_1 && f_2;
        return flag;
    }

    bool isSimilarTo(const Shape& another) const override {
        auto casted = dynamic_cast<const Polygon*>(&another);
        if (casted == nullptr || casted->verticesCount() != verticesCount()) {
            return false;
        }
        bool flag = false;
        int count = verticesCount();
        if (count == 1) {
            return true;
        }
        for (int k = 1; k > -2; k -= 2) {
            for (int i = 0; i < count; ++i) {
                flag = true;
                double coe = dist(casted->vert((i + 1) * k), casted->vert(i * k));
                coe /= dist(vert(1), vert(0));
                for (int j = 0; j < count; ++j) {
                    Point v1 = vert(j) - vert(j + 1);
                    Point v2 = vert(j + 2) - vert(j + 1);
                    double v_cos = (v1 * v2) / sqrt(v1.x * v1.x + v1.y * v1.y) /
                        sqrt(v2.x * v2.x + v2.y * v2.y);
                    Point w1 = casted->vert((i + j) * k) - casted->vert((i + j + 1) * k);
                    Point w2 = casted->vert((i + j + 2) * k) - casted->vert((i + j + 1) * k);
                    double w_cos = (w1 * w2) / sqrt(w1.x * w1.x + w1.y * w1.y) /
                        sqrt(w2.x * w2.x + w2.y * w2.y);
                    if (!(equal(dist(casted->vert((i + j) * k),
                        casted->vert((i + j + 1) * k)),
                        coe * dist(vert(j), vert(j + 1))) &&
                        equal(v_cos, w_cos))) {
                        flag = false;
                        break;
                    }
                }
                if (flag) {
                    return true;
                }
            }
        }
        return false;
    }

    bool containsPoint(const Point& point) const override {
        if (verticesCount() <= 2) {
            return false;
        }
        int count = verticesCount();
        int amount = 0;
        Line line = Line(point, point + Point(1, 1));
        for (int i = 0; i < count; ++i) {
            auto cur = vertices[i];
            auto next = vert(i + 1);
            if (equal(cur.x * line.aLine + cur.y * line.bLine + line.cLine, 0)) {
                if (equal(next.x * line.aLine + next.y * line.bLine + line.cLine, 0)) {
                    if (between(cur, next, point)) {
                        return true;
                    }
                    if (point.x <= cur.x) {
                        ++amount;
                        ++i;
                    }
                    continue;
                }
                auto prev = vert(i - 1);
                if (cur.x < point.x) {
                    continue;
                }
                if (equal(cur.x, point.x)) {
                    return true;
                }
                if ((next.x * line.aLine + next.y * line.bLine + line.cLine > 0 &&
                    prev.x * line.aLine + prev.y * line.bLine + line.cLine < 0) ||
                    (next.x * line.aLine + next.y * line.bLine + line.cLine < 0 &&
                        prev.x * line.aLine + prev.y * line.bLine + line.cLine > 0)) {
                    ++amount;
                }
                else {
                    continue;
                }
            }
            else {
                if (type(line, Line(cur, next)) > 0) {
                    Point cross = intersect(line, Line(cur, next));
                    if (cross.x >= point.x &&
                        between(cur, next, cross) && cross != cur && cross != next) {
                        ++amount;
                    }
                }
            }
        }
        return (amount % 2 == 1);
    }

    void rotate(const Point& center, double angle) override {
        double rad = deg_to_rad(angle);
        for (int i = 0; i < verticesCount(); ++i) {
            vertices[i].rotate(center, rad);
        }
    }

    void reflect(const Point& center) override {
        for (int i = 0; i < verticesCount(); ++i) {
            vertices[i].reflect(center);
        }
    }

    void reflect(const Line& axis) override {
        for (int i = 0; i < verticesCount(); ++i) {
            vertices[i].reflect(axis);
        }
    }

    void scale(const Point& center, double coefficient) override {
        for (int i = 0; i < verticesCount(); ++i) {
            vertices[i].scale(center, coefficient);
        }
    }
};

// Класс Ellipse — эллипс. Эллипс — частный случай фигуры.
class Ellipse : public Shape {
    Point firstF;
    Point secondF;

protected:
    double distance;

    vector<double> abc() const {
        double a = distance / 2;
        double b = sqrt(pow(a, 2) - pow(dist(firstF, secondF) / 2, 2));
        double c = sqrt(pow(a, 2) - pow(b, 2));
        return { a, b, c };
    }

public:
    // фокусы
    pair<Point, Point> focuses() const {
        return make_pair(firstF, secondF);
    }

    // директрисы
    pair<Line, Line> directrices() const {
        auto params = abc();
        Line line = Line(firstF, secondF);
        Point d_1 = firstF;
        d_1.scale(secondF, (params[0] + params[0] * params[0] / params[2]) / (2 * params[0]));
        Point d_2 = secondF;
        d_2.scale(firstF, (params[0] + params[0] * params[0] / params[2]) / (2 * params[0]));
        return { Line(d_1, d_1 + Point(line.aLine, line.bLine)),
                Line(d_2, d_2 + Point(line.aLine, line.bLine)) };
    }

    // эксцентриситет
    double eccentricity() const {
        auto params = abc();
        return params[2] / params[0];
    }

    // Центр
    Point center() const {
        return { (firstF.x + secondF.x) / 2, (firstF.y + secondF.y) / 2 };
    }

    Ellipse(Point first, Point second, double distance) :
        firstF(first), secondF(second), distance(distance) {}

    double perimeter() override {
        auto params = abc();
        return PI * (3 * (params[0] + params[1]) -
            sqrtl((3 * params[0] + params[1]) * (params[0] + 3 * params[1])));
    }

    double area() const override {
        auto params = abc();
        return PI * params[0] * params[1];
    }

    bool operator==(const Shape& another) const override {
        auto casted = dynamic_cast<const Ellipse*>(&another);
        if ((casted != nullptr) &&
            ((casted->firstF == firstF && casted->secondF == secondF) ||
                (casted->firstF == secondF && casted->secondF == firstF)) &&
            equal(casted->distance, distance)) {
            return true;
        }
        return false;
    }

    bool isCongruentTo(const Shape& another) const override {
        auto casted = dynamic_cast<const Ellipse*>(&another);
        if ((casted != nullptr) &&
            equal(dist(casted->firstF, casted->secondF),
                dist(firstF, secondF)) &&
            equal(casted->distance, distance)) {
            return true;
        }
        return false;
    }

    bool isSimilarTo(const Shape& another) const override {
        auto casted = dynamic_cast<const Ellipse*>(&another);
        if ((casted != nullptr) &&
            equal(dist(casted->firstF, casted->secondF),
                dist(firstF, secondF) * casted->distance / distance)) {
            return true;
        }
        return false;
    }

    bool containsPoint(const Point& point) const override {
        if (dist(point, firstF) + dist(point, secondF) <= distance) {
            return true;
        }
        return false;
    }

    void rotate(const Point& center, double angle) override {
        double rad = deg_to_rad(angle);
        firstF.rotate(center, rad);
        secondF.rotate(center, rad);
    }

    void reflect(const Point& center) override {
        firstF.reflect(center);
        secondF.reflect(center);
    }

    void reflect(const Line& axis) override {
        firstF.reflect(axis);
        secondF.reflect(axis);
    }

    void scale(const Point& center, double coefficient) override {
        firstF.scale(center, coefficient);
        secondF.scale(center, coefficient);
        distance *= coefficient;
    }
};

// Класс Circle — круг. Круг — частный случай эллипса.
class Circle : public Ellipse {
public:
    pair<Line, Line> directrices() const = delete;

    double eccentricity() const { return 0; }

    // Радиус
    double radius() const {
        return distance / 2;
    }

    // Круг можно задать точкой и числом (центр и радиус).
    Circle(Point point, double radius) : Ellipse(point, point, radius * 2) {}
};


// Класс Rectangle — прямоугольник. Прямоугольник — частный случай многоугольника.
class Rectangle : public Polygon {
public:
    // центр
    Point center() const {
        vector<Point> ver = getVertices();
        return { (ver[0].x + ver[2].x) / 2, (ver[0].y + ver[2].y) / 2 };
    }

    // пара диагоналей
    pair<Line, Line> diagonals() const {
        vector<Point> ver = getVertices();
        return { Line(ver[0], ver[2]), Line(ver[1], ver[3]) };
    }

    // диагоналей. Прямоугольник можно сконструировать
    //по двум точкам(его противоположным вершинам) и числу(отношению смежных
    //  сторон),
    Rectangle(Point first, Point second, double k) :
        Polygon(first, Point(0, 0), second, Point(0, 0)) {
        double angle = PI - 2 * atan(k);
        Point middle = Point(first, second);
        first.rotate(middle, angle);
        vertices[1] = first;
        second.rotate(middle, angle);
        vertices[3] = second;
    }
};


// Класс Square — квадрат. Квадрат — частный случай прямоугольника.
class Square : public Rectangle {
public:
    // описанная окружность
    Circle circumscribedCircle() const {
        vector<Point> ver = getVertices();
        return { center(), dist(ver[0], ver[1]) / 2 };
    }

    // вписанная окружность
    Circle inscribedCircle() const {
        vector<Point> ver = getVertices();
        return { center(), dist(ver[0], ver[2]) / 2 };
    }

    // Квадрат можно задать двумя точками — противоположными вершинами.
    Square(Point first, Point second) : Rectangle(first, second, 1) {}
};

// Класс Triangle — треугольник. Треугольник — частный случай многоугольника.
class Triangle : public Polygon {
    using Polygon::Polygon;

public:
    // Описанная окружность
    Circle circumscribedCircle() const {
        Line first = orthogonal(Line(vertices[0], vertices[1]),
            Point((vertices[0].x + vertices[1].x) / 2,
                (vertices[0].y + vertices[1].y) / 2));
        Line second = orthogonal(Line(vertices[1], vertices[2]),
            Point((vertices[1].x + vertices[2].x) / 2,
                (vertices[1].y + vertices[2].y) / 2));
        Point center = intersect(first, second);
        return { center, dist(center, vertices[0]) };
    }

    // Вписанная окружность
    Circle inscribedCircle() const {
        double a = dist(vertices[0], vertices[1]);
        double b = dist(vertices[1], vertices[2]);
        double c = dist(vertices[2], vertices[0]);
        Point tmp;
        tmp.x = (vertices[2].x * a + vertices[0].x * b + vertices[1].x * c) / (a + b + c);
        tmp.y = (vertices[2].y * a + vertices[0].y * b + vertices[1].y * c) / (a + b + c);
        return { tmp, 2 * area() / (a + b + c) };
    }

    // Центр масс
    Point centroid() const {
        double x = (vertices[0].x + vertices[1].x + vertices[2].x) / 3;
        double y = (vertices[0].y + vertices[1].y + vertices[2].y) / 3;
        return { x, y };
    }

    // Ортоцентр
    Point orthocenter() const {
        Line first = orthogonal(Line(vertices[0], vertices[1]), vertices[2]);
        Line second = orthogonal(Line(vertices[1], vertices[2]), vertices[0]);
        return intersect(first, second);
    }

    // Прямая Эйлера
    /*
       Прямая, проходящая через центр описанной
       окружности и ортоцентр треугольника
    */
    Line EulerLine() const {
        return { circumscribedCircle().center(), orthocenter() };
    }

    // Окружность Эйлера
    /*
      Окружность девяти точек - это окружность,
      проходящая через середины всех трех сторон треугольника
    */
    Circle ninePointsCircle() const {
        Point first = circumscribedCircle().center();
        Point second = orthocenter();
        Point center = Point((first.x + second.x) / 2, (first.y + second.y) / 2);
        return { center, circumscribedCircle().radius() / 2 };
    }
};

/*
    У любой фигуры можно вычислить:
        — double perimeter() — периметр;
        — double area() — площадь;
        — operator==(const Shape& another) — совпадает ли эта фигура с другой;
        — isCongruentTo(const Shape& another) — равна ли эта фигура
    другой в геометрическом смысле;

        — isSimilarTo(const Shape& another) — подобна ли эта фигура другой;
        — containsPoint(Point point) — находится ли точка внутри фигуры.

    С любой фигурой можно сделать следующие действия:
        — rotate(Point center, double angle) — поворот на угол (в градусах, 
    против часовой стрелки) относительно точки;
        — reflex(Point center) — симметрию относительно точки;
        — reflex(Line axis) — симметрию относительно прямой;
        — scale(Point center, double coefficient) — гомотетию с коэффициентом coefficient
и центром center.
*/
