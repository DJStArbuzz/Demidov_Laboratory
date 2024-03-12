#include <iostream>
#include <vector>
#include <map>
#include <random>
#include <algorithm>
#include <random>
#include "glut.h"

using namespace std;

typedef pair<double, double> pdd;

const double PI = acos(-1.0);

struct Point {
	double x, y; // Координаты точки

	Point(double xTmp, double yTmp);
};
Point::Point(double xTmp, double yTmp) :
	x(xTmp),
	y(yTmp) {}

double func2(double x) {
	return x * sin(2 * x);
}

void init2D(float r, float g, float b)
{
	glClearColor(r, g, b, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 200.0, 0.0, 150.0);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_LINES);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(0, 0);
	glVertex2f(0, 1);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(1.0, 0.0, 0.0);
	for (float x = -1 * PI / 2; x <= 5 * PI /2; x += 0.01) {
		glVertex2f(x, func2(x));
	}
	glEnd();

	glFlush();
}

float compute_integral(int n) {
	float sum = 0;
	double tmp = pow(n, -1);

	for (float x = -1 * PI / 2; x <= 5 * PI / 2; x += tmp) {
		sum += (func2(x) + func2(x + tmp)) * tmp / 2;
	}
	return sum;
}

int main(int argc, char** argv) {
	setlocale(LC_ALL, "Russian");
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Задание 4, вариант 2, пример 2");
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-PI / 2, 5 * PI / 2, -8, 8);

	cout << "2 - ой интеграл:\n";
	cout << "\nПри N = 10     : " << compute_integral(10);
	cout << "\nПри N = 100    : " << compute_integral(100);
	cout << "\nПри N = 1000   : " << compute_integral(1000);
	cout << "\nПри N = 10000  : " << compute_integral(10000);
	cout << "\nПри N = 100000 : " << compute_integral(100000);
	cout << "\nПри N = 1000000: " << compute_integral(1000000);

	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
}
