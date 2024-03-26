#include <iostream>
#include <vector>
#include <map>
#include <random>
#include <algorithm>
#include <random>
#include "glut.h"

const int WIDTH = 1000;
const int HEIGHT = 1000;
const auto FONT = GLUT_BITMAP_TIMES_ROMAN_24;
const double R = 0.5;

using namespace std;

struct Point {
    double x = 0.0;
    double y = 0.0;
    int figure = 0;
    int index  = 0;
    /*
        x, y   - координаты позиции точки;
        figure - указатель на фигуру: 0 - пусто, 1 - король, 2 - конь
        index  - номер точки
    */

    Point operator+(Point B) {
        Point res;
        res.x = x + B.x;
        res.y = y + B.y;
        return res;
    }

    Point operator-(Point B) {
        Point res;
        res.x = x - B.x;
        res.y = y - B.y;
        return res;
    }

    Point operator*(double k) {
        Point res;
        res.x = x * k;
        res.y = y * k;
        return res;
    }

    Point operator/(double k) {
        Point res;
        res.x = x / k;
        res.y = y / k;
        return res;
    }
};

void init2D(float r, float g, float b)
{
    glClearColor(r, g, b, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, WIDTH, 0, HEIGHT);
}

void Generate_points(vector<Point>& A, int n) {
    glPointSize(5.0);
    glColor3f(1, 0, 0);
    glBegin(GL_POINTS);
    for (int i = 0; i < n; i++) {
        A[i].x = abs((rand() % WIDTH) - WIDTH / 2);
        A[i].y = abs((rand() % HEIGHT) - HEIGHT / 2);
        glVertex2d(A[i].x, A[i].y);
    }
    glEnd();
}

void renderBitmapString(float x, float y, const char* string)
{
    glRasterPos3f(x, y, 0);
    glutBitmapCharacter(FONT, string[0]);
    glutBitmapCharacter(FONT, string[1]);
}

void display(void)
{

    glClear(GL_COLOR_BUFFER_BIT);

    glPointSize(6.0);

    int n = 36;

    int up = 2;
    int nextBeg = 2;
    int dist = 1;

    vector<Point> list(n);
    list[0].index = 1;
    list[0].x = 500;
    list[0].y = 850;

    cout << 1;
    double distB = 100;
    int cntW = 0, cntH = 0;
    double beg = 400;
    double mi = 100;

    for (int i = 2; i <= n; i++) {
        if (i == nextBeg) {
            cout << '\n';
            dist++;
            nextBeg += up;
            up++;
            cntW = 1;
            cntH++;
            distB += mi;
            beg -= 50;
        }
        list[i - 1].x = beg + (distB / dist) * cntW;
        cntW++;
        list[i - 1].y = 850 - mi * cntH;
        list[i - 1].index = i;
        list[i - 1].figure = 0;
        cout << i << ' ';
    }
 
    for (int i = 0; i < n; i++) {
        cout << list[i].index;
        glColor3f(3.0, 0.0, 0.0);

        string tmp = "--";
        if (list[i].figure == 0) {
            tmp[0] = char(list[i].index % 10);
            tmp[1] = char(list[i].index - int(tmp[0] * 10)) ;
        }
        else {
            tmp[0] = '-';
            tmp[1] = (list[i].figure == 1) ? 'K' : 'H';
        }

        renderBitmapString(list[i].x, list[i].y, tmp);

        glBegin(GL_LINE_LOOP);
        glColor3f(1.0, 1.0, 0.0);
        glVertex3f(list[i].x - mi / 2, list[i].y - mi / 2, 0);
        glVertex3f(list[i].x - mi / 2, list[i].y + mi / 2, 0);
        glVertex3f(list[i].x + mi / 2, list[i].y + mi / 2, 0);
        glVertex3f(list[i].x + mi / 2, list[i].y - mi / 2, 0);
        glEnd();
    }

    cout << "\n\n\n";
    cout << dist << "\n\n\n";

    glutSwapBuffers();
    glFlush();

}

int main(int argc, char* argv[])
{   
    setlocale(LC_ALL, "Russian");
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Задание 5, вариант 4");
    init2D(0.0, 0.0, 0.0);
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
