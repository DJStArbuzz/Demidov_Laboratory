#include <iostream>
#include <vector>
#include <map>
#include <random>
#include <algorithm>
#include <random>
#include "glut.h"


const int width = 500;
const int height = 500;

const int N = 4;
const int M = 13;
const int K = 1000000;
const double R = 0.5;

using namespace std;

typedef pair<double, double> pdd;

struct Point {
	double x, y; // Координаты точки

	Point(double xTmp, double yTmp);
};
Point::Point(double xTmp, double yTmp) :
	x(xTmp),
	y(yTmp) {}


void init2D(float r, float g, float b)
{
	glClearColor(r, g, b, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 200.0, 0.0, 150.0);
}

map <int, vector<int>> createTravelPos() {
	map<int, vector<int>> res = {
		{1, {}}, {2, {}}, {3, {}}, {4, {}}
	};

	vector<int> list(M);
	for (int i = 0; i < M; i++) {
		list[i] = i;
	}

	random_device rd;
	mt19937 g(rd());
	shuffle(list.begin(), list.end(), g);

	int index = 0;
	for (int i = 0; i < M; ++i) {
		res[(i % N) + 1].push_back(list[i] + 1);
	}

	for (int i = 1; i <= N; i++) {
		cout << "\nТочка " << i << ": ";
		for (int j = 0; j < res[i].size(); j++) {
			cout << res[i][j] << " ";
		}
	}
	cout << '\n';
	return res;
}

double distance(Point first, Point second) {
	return sqrt(pow(second.x - first.x, 2) + pow(second.y - first.y, 2));
}

int negaFlag(double first, double second) {
	if (first < second) {
		return 1;
	}
	else if (first > second) {
		return -1;
	}
	else {
		return 0;
	}
}

void display(void)
{

	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(3.0, 0.0, 0.0);

	vector<Point> list = {
		Point(25.0, 25.0),
		Point(60.0, 25.0),
		Point(150.0, 100.0),
		Point(50.0, 150.0)
	};

	glPointSize(6.0);
	glBegin(GL_POINTS);
	for (int j = 0; j < list.size(); j++) {
		glVertex2i(list[j].x, list[j].y);
	}
	glEnd();

	map<int, vector<int>> arrays = createTravelPos();

	for (int i = 1; i < M; i++)
	{
		cout << i << " этап:\n";
		int posFirst = 0, posSecond = 0;

		for (int j = 1; j <= N; j++) {
			if (count(arrays[j].begin(), arrays[j].end(), i) == 1)
			{
				posFirst = j - 1;
				break;
			}
		}
		for (int j = 1; j <= N; j++) {
			if (count(arrays[j].begin(), arrays[j].end(), i + 1) == 1) {
				posSecond = j - 1;
				break;
			}
		}


		if (posFirst == posSecond) {
			continue;
		}

		Point first = list[posFirst], second = list[posSecond];
		double dist = distance(first, second);

		glBegin(GL_LINES);
		glVertex2i(first.x, first.y);
		glVertex2i(second.x, second.y);
		glEnd();

		cout << "a: " << first.x << " " << first.y << " " << posFirst << endl;
		cout << "b: " << second.x << " " << second.y << " " << posSecond << endl;
		cout << dist << " расстояние" << endl;

		int negaFlagX = negaFlag(first.x, second.x);
		int negaFlagY = negaFlag(first.y, second.y);

		glColor3f(0.0, 1.0, 0.0);

		Point tmpFirst(first.x, first.y);

		while (dist >= 0.005) {
			double dx = abs(second.x - tmpFirst.x) / (pow(R, -1)) * negaFlagX;
			double dy = abs(second.y - tmpFirst.y) / (pow(R, -1)) * negaFlagY;

			glBegin(GL_POINTS);
			glPointSize(6.0);
			for (int j = 1; j <= int(pow(R, -1)) - 1; j++)
			{
				glVertex2i(tmpFirst.x + dx * j, tmpFirst.y + dy * j);
				cout << tmpFirst.x + dx * j << " " << tmpFirst.y + dy * j << endl;

			}

			glEnd();

			tmpFirst.x += dx * (int(pow(R, -1)) - 1);
			tmpFirst.y += dy * (int(pow(R, -1)) - 1);
			dist = distance(tmpFirst, second);
		}
		glFlush();

		cout << "конец этапа\n\n";
	}
}

int main(int argc, char* argv[])
{
	/*
	Построить "ломанную" по точкам. Точек = N, Операций = M - 1.
	Коэффициент подобия = 0.5
	*/
	setlocale(LC_ALL, "Russian");
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Задание 2, вариант 30");
	init2D(0.0, 0.0, 0.0);
	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
}
