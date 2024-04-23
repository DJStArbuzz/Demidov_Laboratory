#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include "glut.h"

using namespace std;

class Point {
public:
	double x, y;

	Point() : x(), y() {}
	Point(double x, double y) : x(x), y(y) {}

	double dist(Point other)
	{
		return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2));
	}
};

double distance(Point first, Point second) {
	return sqrt(pow(first.x - second.x, 2) + pow(first.y - second.y, 2));
}

double perimeter(Point p1, Point p2, Point p3)
{
	return p1.dist(p2) + p2.dist(p3) + p3.dist(p1);
}

bool checkCircle(Point center, Point tmp, double R) {
	return abs((pow(center.x - tmp.x, 2) + pow(center.y - tmp.y, 2)) <= R * R);
}

void drawCircle(float cx, float cy, float r, int num_segments)
{
	float theta = 3.1415926 * 2 / float(num_segments);
	float tangetial_factor = tanf(theta);//calculate the tangential factor 

	float radial_factor = cosf(theta);

	float x = r;

	float y = 0;
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);
	for (int ii = 0; ii < num_segments; ii++)
	{
		glVertex2f(x + cx, y + cy);

		float tx = -y;
		float ty = x;

		x += tx * tangetial_factor;
		y += ty * tangetial_factor;

		x *= radial_factor;
		y *= radial_factor;
	}
	glEnd();
}

pair<Point, Point>  checkRadius(vector<Point>& list) {
	int checkPointsRes = 0, checkPointsTmp = 0;

	pair<Point, Point> result = { list[0], list[1] };
	for (int i = 0; i < list.size(); i++) {      // Центр
		for (int j = i + 1; j < list.size(); j++) {  // Для радиуса
			double distTmp = distance(list[i], list[j]);

			for (int k = 0; k < list.size(); k++) {
				if (checkCircle(list[i], list[k], distTmp)) {
					checkPointsTmp++;
				}
			}

			if (checkPointsTmp > checkPointsRes) {
				checkPointsRes = checkPointsTmp;
				result.first = list[i];
				result.second = list[j];
			}

			checkPointsTmp = 0;
		}
	}

	cout << "Центр окружности: " << result.first.x << ' ' << result.first.y << '\n';
	cout << "Радиус окружности: " << distance(result.first, result.second) << '\n';
	cout << "Вошло точек: " << checkPointsRes<< '\n';
	cout << result.second.x << ' ' << result.second.y << " ";
	return result;
}

void display()
{

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);

	vector<Point> list;

	ifstream fin("71.txt");
	double x, y;
	while (fin >> x >> y)
	{
		list.push_back(Point(x, y));
	}
	fin.close();


	pair< Point, Point> circle = checkRadius(list);
	
	glPointSize(6.0);
	glBegin(GL_POINTS);
	for (int i = 0; i < list.size(); i++){
		glVertex2d(list[i].x, list[i].y);
	}
	glEnd();

	glColor3f(0.0, 0.0, 1.0);
	double dist = distance(circle.first, circle.second);
	drawCircle(circle.first.x, circle.first.y, dist, 360);

	glBegin(GL_LINES);
	glVertex2d(circle.first.x, circle.first.y);
	glVertex2d(circle.second.x, circle.second.y);
	glEnd();
	glFlush();
}

void init2D(float r, float g, float b)
{
	glClearColor(r, g, b, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 200.0, 0.0, 150.0);
}

int main(int argc, char** argv)
{
	setlocale(LC_ALL, "Russian");
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1000, 1000);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Лабораторная 7, задание 1, вариант 18");
	init2D(0.0, 0.0, 0.0);
	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
}
