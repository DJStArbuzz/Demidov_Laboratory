#include <iostream>
#include <vector>
#include <map>
#include <random>
#include <algorithm>
#include <random>
#include <sstream>
#include "glut.h"

const int WIDTH = 1000;
const int HEIGHT = 1000;
const auto FONT = GLUT_BITMAP_TIMES_ROMAN_24;
const double R = 0.5;

using namespace std;

vector<vector<int>> movesHorse =
{    {-3, -1, -1},
    {2, -1, -1},
    {3, 1, 1},
    {-2, 1, 1},
    { - 2, -2, -2},
    {0, -2, -2},
    {0, 2, 2},
    {2, 2, 2},
};

vector<vector<int>> movesKing =
{ {0, 1, 1},
    {1, 1, 1},
    {-1, 0, 0},
    {1, 0, 0},
    {0, -1, -1},
    {-1, -1, -1},
};

struct Point {
    double x = 0.0;
    double y = 0.0;
    int figure = 0;
    int index = 0;
    int row = 0;
    int col = 0;
    int dist = 1;

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

void renderText(float x, float y, string text) {
    glRasterPos2f(x, y);

    for (int i = 0; i < text.size(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text[i]);
    }
}
bool isValid(int x, int y, int dist) {
    return x >= 0 && x < dist && y >= 0 && y < dist;
}

void horse(Point tmp, vector<Point> &list) {

    int knightX = tmp.col, knightY = tmp.row; // координаты коня
    for (auto move1 : movesHorse)
    {
        int nextY = knightY + move1[1];
        int nextX = knightX;
        if (((nextX == tmp.dist + move1[2] - 1) || nextX == 0) && (abs(move1[2]) == 2)) {
            continue;
        }



        nextX += move1[0];
        if (isValid(nextX, nextY, tmp.dist + move1[2])) {
            cout << "(" << nextX << "," << nextY << ")" << endl;
            for (int i = 0; i < list.size(); i++)
            {
                if (list[i].row == nextY && list[i].col == nextX) {
                    renderText(list[i].x, list[i].y, "XYI");
                    cout << list[i].index << " " << nextY << " " << nextX << endl;
                    break;
                }
            }
        }
    }
}

void king(Point tmp, vector<Point>& list) {

    int knightX = tmp.col, knightY = tmp.row; // координаты коня
    for (auto move1 : movesKing)
    {
        int nextY = knightY + move1[1];
        int nextX = knightX;
        if (((nextX == tmp.dist + move1[2] - 1) || nextX == 0) && (abs(move1[2]) == 2)) {
            continue;
        }



        nextX += move1[0];
        if (isValid(nextX, nextY, tmp.dist + move1[2])) {
            cout << "(" << nextX << "," << nextY << ")" << endl;
            for (int i = 0; i < list.size(); i++)
            {
                if (list[i].row == nextY && list[i].col == nextX) {
                    renderText(list[i].x, list[i].y, "XYI");
                    cout << list[i].index << " " << nextY << " " << nextX << endl;
                    break;
                }
            }
        }
    }
}
void display(void)
{

    glClear(GL_COLOR_BUFFER_BIT);

    glPointSize(6.0);

    int n = 10, n2 = 1;

    int up = 2;
    int nextBeg = 2;
    int dist = 1;

    vector<Point> list;
    Point first;
    first.index = 1;
    first.x = 500;
    first.y = 850;
    list.push_back(first);

    double distB = 100;
    int cntW = 0, cntH = 0;
    double beg = 400;
    double mi = 100;

    int in = 2;
    int rIn = 0, cIn = 0;
    cout << 1;
    while (n2 <= n) {
        if (in == nextBeg) {
            cout << '\n';
            dist++;
            nextBeg += up;
            up++;
            cntW = 1;
            cntH++;
            distB += mi;
            beg -= 50;
            n2++;

            cIn = 0;
            rIn++;
            if (n2 > n) {
                break;
            }
        }

        Point tmpP;
        tmpP.x = beg + (distB / dist) * cntW;
        cntW++;
        tmpP.y = 850 - mi * cntH;
        tmpP.index = in;
        tmpP.figure = 0;
        tmpP.row = rIn;
        tmpP.col = cIn;
        tmpP.dist = n2;
        cIn++;
        list.push_back(tmpP);
        cout << in << ' ';

        in++;
    }

    list[5].figure = 1;
    list[24].figure = 2;

    for (int i = 0; i < list.size(); i++) {
        cout << "index: " << list[i].index << endl;
        cout << "row: " << list[i].row << endl;
        cout << "col: " << list[i].col << endl;
        cout << "figure: " << list[i].figure << endl;
        cout << "dist: " << list[i].dist << endl;
        cout << endl;
    }

    for (int i = 0; i < list.size(); i++) {
        cout << list[i].index;
        glColor3f(3.0, 0.0, 0.0);

        string tmp = "--";
        if (list[i].figure == 0) {
            tmp = to_string(list[i].index);
        }
        else {
            tmp = (list[i].figure == 1) ? '-K' : '-H';
        }
        cout << tmp << endl;
        renderText(list[i].x, list[i].y, tmp);
        glBegin(GL_LINE_LOOP);
        glColor3f(1.0, 1.0, 0.0);
        glVertex3f(list[i].x - mi / 2, list[i].y - mi / 2, 0);
        glVertex3f(list[i].x - mi / 2, list[i].y + mi / 2, 0);
        glVertex3f(list[i].x + mi / 2, list[i].y + mi / 2, 0);
        glVertex3f(list[i].x + mi / 2, list[i].y - mi / 2, 0);
        glEnd();
    }

    vector<Point> tmpList;
    int knightX = list[24].col, knightY = list[24].row; // координаты коня
    for (auto move1 : movesKing)
    {
        int nextY = knightY + move1[1];
        int nextX = knightX;
        if (((nextX == list[24].dist + move1[2] - 1) || nextX == 0) && (abs(move1[2]) == 2)) {
            continue;
        }

        nextX += move1[0];
        if (isValid(nextX, nextY, list[24].dist + move1[2])) {
            cout << "(" << nextX << "," << nextY << ")" << endl;
            for (int i = 0; i < list.size(); i++)
            {
                if (list[i].row == nextY && list[i].col== nextX) {
                    renderText(list[i].x, list[i].y, "XYI");
                    tmpList.push_back(list[i]);
                    cout << list[i].index << " " << nextY << " " << nextX << endl;
                    break;
                }
            }
        }
    }
    glColor3f(0.0, 0.0, 1.0);

    for (int i = 0; i < tmpList.size(); i++) {
        king(tmpList[i], list);
    }

    cout << "\n\n\n";
    cout << dist << "\n\n\n";

    glutSwapBuffers();
    glFlush();

}

int main(int argc, char* argv[]){
    setlocale(LC_ALL, "Russian");
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(50, 100);
    glutCreateWindow("Задание 5, вариант 4");
    init2D(0.0, 0.0, 0.0);
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
