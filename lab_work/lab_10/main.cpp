#include <iostream>
#include <string>

#include "geometry.h"
#include "glut.h"

using namespace std;

const int N = 30;
const int RAZ = 15;


void listFigure() {
    cout << "--------------------------\n";
    cout << "1 - Point, точка на плоскости;\n";
    cout << "2 - Line, прямая;\n";
    cout << "3 - Polygon, многоугольник;\n";
    cout << "4 - Ellipse, эллипс;\n";
    cout << "5 - Circle, круг;\n";
    cout << "6 - Rectangle, прямоугольник;\n";
    cout << "7 - Square, квадрат;\n";
    cout << "8 - Triangle, треугольник;\n";
    cout << "--------------------------\n";
}

void listOper() {
    cout << "_1 - Периметр;\n";
    cout << "_2 - Площадь;\n";
    cout << "_3 - Совпадение;\n";
    cout << "_4 - Равенство;\n";
    cout << "_5 - Равенство в геометрическом смысле;\n";
    cout << "_6 - Подобие;\n";
    cout << "_7 - Нахождение в точке;\n";
    cout << "_8 - Поворот на угол;\n";
    cout << "_9 - Симметрия относительно точки;\n";
    cout << "10 - Симметрия относительно прямой;\n";
    cout << "11 - Гомотетия;\n";
    cout << "--------------------------\n";
}

void Instruction() {
    cout << "Нажмите на одну из предложенных кнопок:\n";
    cout << "Create - создать фигуру;\n";
    cout << "Delete - удалить фигуру;\n";
    cout << "Edit - изменение фигуры;\n";
    cout << "Next - переключиться на следующую фигуру;\n";
    cout << "Preview - переключиться на предыдущую фигуру;\n";
    cout << "Next - просмотр инструкции;\n\n";

    cout << "При выборе Next или Preview программа укажет на ";
    cout << "текущую (подсвеченную) фигуру.\n\n";

    cout << "При выборе Edit или Delete программа запросит номер ";
    cout << "фигуры, которую Вы хотите удалить.\n";
    cout << "С фигурой можно:\n";
    listOper();

    cout << "При выборе Create пользователю предлагается список возможных ";
    cout << "элементов / фигур, которые он захочет создать:\n";

    listFigure();
}

class Button {
private:
    double x;
    double y;
    double width;
    double height;
    const char* text;
public:
    Button() : x(0), y(0), width(0), height(0), text(nullptr) {};
    Button(double x, double y, double width, double height, const char* text)
        : x(x), y(y), width(width), height(height), text(text) {};

    vector <double> colors;
    void setColor(double first, double second, double third) {
        colors.push_back(first);
        colors.push_back(second);
        colors.push_back(third);
    }

    void drawButton() {
        //Отрисовка кнопки
        glBegin(GL_POLYGON);
        glColor3f(colors[0], colors[1], colors[2]); // Серый цвет
        glVertex2f(x, y);
        glVertex2f(x + width, y);
        glVertex2f(x + width, y + height);
        glVertex2f(x, y + height);
        glEnd();

        glColor3f(0.0f, 0.0f, 0.0f); // Серый цвет
        int textLength = strlen(text);
        float textX = x + 1;
        float textY = y + 1;

        glRasterPos2f(textX, textY);
        for (int i = 0; i < textLength; i++) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, text[i]);
        }
    }

    bool isButtonHovered(Point& najatie) {
        return najatie.x >= this->x && najatie.x <= this->x + this->width &&
            najatie.y >= this->y && najatie.y <= this->y + this->height;
    }

};

// Массив из всех элементов
vector<pair<int, int>> list = { {0, 0}, {1, 1}, {2,  0} };

// Массив элементов определенного вида фигуры
vector<Point> pointList = { Point(1.0, 1.0), Point(2.9, 2.1) };
vector<Line> lineList = { Line(Point(1.0, 1.0), Point(2.0, 2.0)), Line(5, 5) };
vector<Polygon> polygonList = { Polygon({Point(1.0, 2.0), Point(3.0, 3.0), Point(1.0, 3.0)})};
vector<Ellipse> ellipseList = { Ellipse(Point(1.0, 2.0), Point(2.0, 5.0), 5) };
vector<Circle> circleList = { Circle(Point(1.0, 6.0), 5) };
vector<Rectangle> rectangleList;
vector<Square> squareList;
vector<Triangle> triangleList;

int cur = -1;

void init() {
    glClearColor(0.0, 0.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-N, N + RAZ, -N, N, -1.0, 1.0);
}

//Кнопки изначального меню
Button bCreate(31, 25, 12, 4, "Create");
Button bDelete(31, 20, 12, 4, "Delete");
Button bEdit(31, 15, 12, 4, "Edit");
Button bNext(31, 10, 12, 4, "Next");
Button bPreview(31, 5, 12, 4, "Preview");
Button bInstruction(31, 0, 12, 4, "Instruction");

//Кнопки меню выбора точек
Button bPoint    (31,  25, 12, 4, "Point");
Button bLine     (31,  20, 12, 4, "Line");
Button bPolygon  (31,  15, 12, 4, "Polygon");
Button bEllipse  (31,  10, 12, 4, "Ellipse");
Button bCircle   (31,   5, 12, 4, "Circle");
Button bRectangle(31,   0, 12, 4, "Rectangle");
Button bSquare   (31,  -5, 12, 4, "Square");
Button bTriangle (31, -10, 12, 4, "Triangle");

//Кнопки меню выбора операции
Button bPerimeter    (31,  25, 12, 4, "Perimeter");
Button bArea         (31,  20, 12, 4, "Area");
Button bEqual        (31,  15, 12, 4, "Equal (==)");
Button bIsCongruentTo(31,  10, 12, 4, "Is Congruent To");
Button bIsSimilarTo  (31,   5, 12, 4, "Is Similar To");
Button bContainsP    (31,   0, 12, 4, "ContainsPoint");
Button bRotate       (31,  -5, 12, 4, "Rotate");
Button bReflexP      (31, -10, 12, 4, "Reflex with Point");
Button bReflexL      (31, -15, 12, 4, "Reflex with Line");
Button bScale        (31, -20, 12, 4, "Scale");

// Отрисовка стартового меню
void drawMenu() {
    bCreate.setColor(0.9, 0.0, 0.5);
    bDelete.setColor(0.9, 0.0, 0.5);
    bEdit.setColor(0.9, 0.0, 0.5);
    bNext.setColor(0.9, 0.0, 0.5);
    bPreview.setColor(0.9, 0.0, 0.5);
    bInstruction.setColor(0.9, 0.0, 0.5);

    bCreate.drawButton();
    bDelete.drawButton();
    bEdit.drawButton();
    bNext.drawButton();
    bPreview.drawButton();
    bInstruction.drawButton();
}

// Отрисовка меню выбора фигур
void drawMenuFigure() {
    bPoint.setColor(0.9, 0.0, 0.5);
    bLine.setColor(0.9, 0.0, 0.5);
    bPolygon.setColor(0.9, 0.0, 0.5);
    bEllipse.setColor(0.9, 0.0, 0.5);
    bCircle.setColor(0.9, 0.0, 0.5);
    bRectangle.setColor(0.9, 0.0, 0.5);
    bSquare.setColor(0.9, 0.0, 0.5);
    bTriangle.setColor(0.9, 0.0, 0.5);

    bPoint.drawButton();
    bLine.drawButton();
    bPolygon.drawButton();
    bEllipse.drawButton();
    bCircle.drawButton();
    bRectangle.drawButton();
    bSquare.drawButton();
    bTriangle.drawButton();
}

// Отрисовка меню выбора операции
void drawMenuOperation() {
    bPerimeter.setColor(0.9, 0.0, 0.5);
    bArea.setColor(0.9, 0.0, 0.5);
    bEqual.setColor(0.9, 0.0, 0.5);
    bIsCongruentTo.setColor(0.9, 0.0, 0.5);
    bIsSimilarTo.setColor(0.9, 0.0, 0.5);
    bContainsP.setColor(0.9, 0.0, 0.5);
    bRotate.setColor(0.9, 0.0, 0.5);
    bReflexP.setColor(0.9, 0.0, 0.5);
    bReflexL.setColor(0.9, 0.0, 0.5);
    bScale.setColor(0.9, 0.0, 0.5);

    bPerimeter.drawButton();
    bArea.drawButton();
    bEqual.drawButton();
    bIsCongruentTo.drawButton();
    bIsSimilarTo.drawButton();
    bContainsP.drawButton();
    bRotate.drawButton();
    bReflexP.drawButton();
    bReflexL.drawButton();
    bScale.drawButton();
}

// Отрисовка координатной плоскости
void drawGrid() {
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(1.0);
    glBegin(GL_LINES);
    for (int i = -N; i <= N; i++) {
        glVertex2f(i, -N);
        glVertex2f(i, N);
        glVertex2f(-N, i);
        glVertex2f(N, i);
    }
    glEnd();
}

void drawAxes() {
    glBegin(GL_QUADS);
    glVertex2f(-N, -N);
    glVertex2f(-N, N);
    glVertex2f(N, N);
    glVertex2f(N, -N);
    glEnd();

    glColor3f(1.0, 0.0, 0.0);
    glLineWidth(4.0);
    glBegin(GL_LINES);
    glVertex2f(-N, 0);
    glVertex2f(N, 0);
    glVertex2f(0, -N);
    glVertex2f(0, N);
    glEnd();
}

// Отображение изначального экрана
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawAxes();
    drawGrid();
    drawMenu();
    glColor3f(1.0, 1.0, 1.0);
    glFlush();
    glutSwapBuffers();
}

// Отображение экрана с выбором фигур
void display2() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0, 0.0, 1.0, 1.0);
    drawMenuFigure();
    glutPostRedisplay();
    glFlush();
    glutSwapBuffers();
}

// Отображение экрана с выбором операций
void display3() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0, 0.0, 1.0, 1.0);
    drawMenuOperation();
    glutPostRedisplay();
    glFlush();
    glutSwapBuffers();
}

void Create() {
    listFigure();
    glutInitWindowSize(1000, 1000);
    glutCreateWindow("Create");
    init();
    glutDisplayFunc(display2);
    glutMainLoop();

}

void Delete() {
    cout << "Delete\n";
    cout << "Выберете номер фигуры, которую вы хотите удалить: ";
    
    int ind = 0;
    cin >> ind;

    if (ind < 0 || ind >= list.size()) {
        cout << "Неправильно указан номер";
        return;
    }
    
    list.erase(list.begin() + ind);

    cout << "Фигура была удалена\n";
    cout << "-------------------\n";
}

void Edit() {
    listOper();
    glutInitWindowSize(1000, 1000);
    glutCreateWindow("Edit");
    init();
    glutDisplayFunc(display3);
    glutMainLoop();

}



void mouseClick(int button, int state, int x, int y) {
    setlocale(LC_ALL, "rus");
    double worldX, worldY, worldZ;
    GLint viewport[4];
    GLdouble modelview[16], projection[16];

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        glGetIntegerv(GL_VIEWPORT, viewport);
        glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
        glGetDoublev(GL_PROJECTION_MATRIX, projection);

        gluUnProject(x, viewport[3] - y, 0, modelview, projection, viewport, &worldX, &worldY, &worldZ);

        // cout << "Нажатие на координате X: " << worldX << ", Y: " << worldY << '\n';

        Point menuChoice(worldX, worldY);

        if (bCreate.isButtonHovered(menuChoice)) {
            cout << "Create\n";
            Create();

            cout << '\n';
        }
        else if (bDelete.isButtonHovered(menuChoice)) {
            Delete();
        }
        else if (bEdit.isButtonHovered(menuChoice)) {
            cout << "Edit\n\n";
            Edit();

            cout << '\n';
        }
        else if (bNext.isButtonHovered(menuChoice)) {
            cout << "Next\n\n";

            cout << '\n';
        }
        else if (bPreview.isButtonHovered(menuChoice)) {
            cout << "Preview\n\n";


            cout << '\n';
        }
        else if (bInstruction.isButtonHovered(menuChoice)) {
            cout << "Instruction\n";
            Instruction();


            cout << '\n';
        }
    }
}

int main(int argc, char** argv) {
    setlocale(LC_ALL, "RUS");
    Instruction();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1000, 1000);
    glutCreateWindow("Лабораторная работа №10, вариант №1");

    init();

    glutDisplayFunc(display);
    glutMouseFunc(mouseClick);

    glutMainLoop();

    return 0;
}