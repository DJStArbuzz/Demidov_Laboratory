#include <iostream>
#include <vector>
#include <map>
#include <random>
#include <algorithm>
#include <cmath>
#include <random>
#include "glut.h"

using namespace std;


bool check(double x, double y) {
    return (pow(x, 7) + 2 * pow(y, 3) < 1) && (x + y > -1)
        && (-2 < x < 2) && (-2 < y < 2);
}

void information_problem3(int k, int N, int S0) {
    cout << "Дана фигура, заданная системой уравнений.\n";
    cout << "/ x^7 + 2 * y^3 < 1\n";
    cout << "| x + y > -1\n";
    cout << "| -2 < x < 2\n";
    cout << "\ -2 < y < 2\n";
    cout << "Площадь методом Монте-Карло: K * S | N \n";
    cout << "k  = " << k << "\n";
    cout << "N  = " << N << "\n";
    cout << "S0 = " << S0 << "\n";
    cout << "S  = " << 1.0 * k * S0 / N << "\n";
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    
    int k = 0, N = 0, S = 16;
    for (float x = -2; x <= 2; x += 0.005) {
        for (float y = -2; y <= 2; y += 0.005) {
            if (check(x, y)) {
                glVertex2f(x / 2, y / 2);
                k++;
            }
            N++;
        }
    }

    information_problem3(k, N, S);
    glEnd();
    glFlush();
}

int main(int argc, char** argv) {
    setlocale(LC_ALL, "Russian");
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("Задание 3, вариант 19");
    glutDisplayFunc(display);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    glutMainLoop();
    return 0;
}
