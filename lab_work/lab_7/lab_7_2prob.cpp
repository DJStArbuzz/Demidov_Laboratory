#include <iostream>
#include <vector>
#include <map>
#include <random>
#include <algorithm>
#include <random>
#include "glut.h"

const int width = 500;
const int height = 500;

const int N = 3;
const int M = 13;
const int K = 1000000;
const double R = 0.5;

using namespace std;

struct Point {
    double x = 0.0, y = 0.0;

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
	gluOrtho2D(0, 500.0, 0, 500.0);
}


int draw() {
    int result = rand() % M;
    return result % N;
}

void Generate_points(vector<Point>& A, int n) {
    glPointSize(5.0);
    glColor3f(1, 0, 0);
    glBegin(GL_POINTS);
    for (int i = 0; i < n; i++) {
        A[i].x = abs((rand() % width) - width / 2);
        A[i].y = abs((rand() % height) - height / 2);
        glVertex2d(A[i].x, A[i].y);
    }
    glEnd();
}

void display(void)
{

	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(3.0, 0.0, 0.0);

    vector<Point> list(N);
    Generate_points(list, N);

	glPointSize(6.0);
	glBegin(GL_POINTS);
	
    Point Start;
    Start.x = (rand() % width) - width / 2;
    Start.y = (rand() % height) - height / 2;

    for (int i = 1; i < K; i++) {
        int it = draw();
        
        Point B = Start + list[it];
        B = B * 0.5;

        glPointSize(2.0);
        glColor3f(0, 1, 0);
        glBegin(GL_POINTS);
        glVertex2d(B.x, B.y);
        glEnd();
        Start = B;

    }
    glutSwapBuffers();
    glFlush();
	
}

int main(int argc, char* argv[])
{
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



/*
using namespace std;

int main() {
    int n = 20;

    int up = 2;
    int nextBeg = 2;
    int dist = 1;

    cout << 1 << '\n';
    for (int i = 2; i <= n; i++) {
        if (i == nextBeg) {
            cout << '\n';
            dist++;
            nextBeg += up;
            up++;
        }
        cout << i << ' ';
    }

    cout << "\n\n\n";
    cout << dist;
}
*/
