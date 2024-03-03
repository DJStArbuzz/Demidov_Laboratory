#include <iostream>
#include <vector>
#include "glut.h"

const int width = 500;
const int height = 500;

using namespace std;

typedef pair<double, double> pdd;

struct Line {
	pdd fP;  // Позиции 1-ой точки линии
	pdd sP; // Позиции 2-ой точки линии

	Line();
	Line(pair<pdd, pdd>);
	~Line();
};
Line::Line() :
	fP(0, 0),
	sP(100, 100) {}
Line::Line(pair<pdd, pdd> tmp) :
	fP(tmp.first),
	sP(tmp.second) {}
Line::~Line() {}


bool checkIntersection(Line l1, Line l2) {
	double a1 = l1.sP.second - l1.fP.second;
	double b1 = l1.fP.first - l1.sP.first;
	double c1 = a1 * l1.fP.first + b1 * l1.fP.second;

	double a2 = l2.sP.second - l2.fP.second;
	double b2 = l2.fP.first - l2.sP.first;
	double c2 = a2 * l2.fP.first + b2 * l2.fP.second;

	double det = a1 * b2 - a2 * b1;
	if (det == 0) {
		return false; 
	}

	double x = (b2 * c1 - b1 * c2) / det;
	double y = (a1 * c2 - a2 * c1) / det;

	if (x >= min(l1.fP.first, l1.sP.first) && x <= max(l1.fP.first, l1.sP.first) &&
		x >= min(l2.fP.first, l2.sP.first) && x <= max(l2.fP.first, l2.sP.first) &&
		y >= min(l1.fP.second, l1.sP.second) && y <= max(l1.fP.second, l1.sP.second) &&
		y >= min(l2.fP.second, l2.sP.second) && y <= max(l2.fP.second, l2.sP.second)) {
		return true; 
	}

	return false;
}

void init2D(float r, float g, float b)
{
	glClearColor(r, g, b, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 200.0, 0.0, 150.0);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	
	vector<Line> list = {
		Line({ {10, 10}, {100, 100} }),
		Line({ {70, 35}, {-100, -50} }),  
		Line({ {45, 10}, {78, 100} }),
		Line({ {20, 250}, {20, 250} }), 
		Line({ {10, 2}, {300, 50} }),
		Line({ {40, 0}, {50, 100} }),
	};

	vector<int> intersections(list.size(), 0);
	int maxNeedPos = 0, maxRes = -1;
	for (int i = 0; i < list.size(); i++) {
		for (int j = 0; j < list.size(); j++) {
			if (checkIntersection(list[i], list[j])) {
				intersections[i]++;
				intersections[j]++;
			}
		}
	}
	for (int i = 0; i < list.size(); i++) {
		if (maxRes < intersections[i]) {
			maxRes = intersections[i];
			maxNeedPos = i;
		}
	}

	for (int i = 0; i < list.size(); i++) {
		glBegin(GL_LINES);
		glVertex2i(list[i].fP.first, list[i].fP.second);
		glVertex2i(list[i].sP.first, list[i].sP.second);
		glEnd();
	}

	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINES);
	glVertex2i(list[maxNeedPos].fP.first, list[maxNeedPos].fP.second);
	glVertex2i(list[maxNeedPos].sP.first, list[maxNeedPos].sP.second);
	glEnd();

	glFlush();
}

int main(int argc, char* argv[])
{
	/*
	На плоскости задано множество попарно различных прямых (коэффициентами
	своих уравнений). Указать среди них ту прямую, которая имеет максимальное
	число пересечений с остальными прямыми.
	*/

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Задание 1, вариант 5");
	init2D(0.0, 0.0, 0.0);
	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
}
