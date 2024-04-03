#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <random>
#include <sstream>
#include <queue>
#include <set>
#include "glut.h"

const int WIDTH = 1000;
const int HEIGHT = 1000;
const auto FONT = GLUT_BITMAP_TIMES_ROMAN_24;
const double R = 0.5;

using namespace std;

vector<vector<int>> movesHorse = {
    {-3, -1, -1},
    { 2, -1, -1},
    { 3,  1,  1},
    {-2,  1,  1},
    {-3, -2, -2},
    { 1, -2, -2},
    {-1,  2,  2},
    { 3,  2,  2},
    {-1, -3, -3},
    {-2, -3, -3},
    { 1,  3,  3},
    { 2,  3,  3}, };

vector<vector<int>> movesKing = {
    { 0,  1,  1},
    { 1,  1,  1},
    {-1,  0,  0},
    { 1,  0,  0},
    { 0, -1, -1},
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


void renderText(float x, float y, string text) {
    glRasterPos2f(x, y);

    for (int i = 0; i < text.size(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text[i]);
    }
}
bool isValid(int x, int y, int dist) {
    return x >= 0 && x < dist && y >= 0 && y < dist;
}

void fill_cell(Point point, double mi) {
    glBegin(GL_QUADS);
    glColor3f(3.0, 0.0, 0.0);
    glVertex3f(point.x - mi / 2, point.y - mi / 2, 0);
    glVertex3f(point.x - mi / 2, point.y + mi / 2, 0);
    glVertex3f(point.x + mi / 2, point.y + mi / 2, 0);
    glVertex3f(point.x + mi / 2, point.y - mi / 2, 0);
    glEnd();
}


void horse(Point tmp, vector<Point>& list, double mi) {
    int horseX = tmp.col, horseY = tmp.row;
    for (auto move : movesHorse) {
        int nextY = horseY + move[1];
        int nextX = horseX;
        nextX += move[0];

        if (isValid(nextX, nextY, tmp.dist + move[2])) {
            for (int i = 0; i < list.size(); i++)
            {
                if (list[i].row == nextY && list[i].col == nextX) {
                    renderText(list[i].x, list[i].y, "OK");
                    break;
                }
            }
        }
    }
}

void king(Point tmp, vector<Point>& list) {

    int kingX = tmp.col, kingY = tmp.row;
    for (auto move1 : movesKing)
    {
        int nextY = kingY + move1[1];
        int nextX = kingX;

        nextX += move1[0];
        if (isValid(nextX, nextY, tmp.dist + move1[2])) {
            for (int i = 0; i < list.size(); i++)
            {
                if (list[i].row == nextY && list[i].col == nextX) {
                    renderText(list[i].x, list[i].y, "OK");
                    break;
                }
            }
        }
    }
}


struct Node
{
    int x, y, dist;
    vector<pair<int, int>> path;

    Node(int x, int y, int dist = 0) : x(x), y(y), dist(dist) {}
    bool operator<(const Node& o) const {
        return x < o.x || (x == o.x && y < o.y);
    }
};


int findShortestDistance(int N, Node s, Node dest, vector<Point>& list, double mi)
{
    Node src = s;
    s.path.push_back({ src.x, src.y });
    set<Node> visited;

    queue<Node> q;
    q.push(src);

    while (!q.empty())
    {
        Node node = q.front();
        q.pop();

        int x = node.x;
        int y = node.y;
        int dist = node.dist;

        if (x == dest.x && y == dest.y) {
            cout << "\n\n\n\n\n";
            cout << "Length path: " << dist << endl;

            vector<Point> list2;
            for (int i = 0; i < node.path.size(); i++) {
                for (int j = 0; j < list.size(); j++) {
                    if (list[j].col == node.path[i].first && list[j].row == node.path[i].second) {
                        list2.push_back(list[j]);
                        fill_cell(list[j], mi);
                    }
                }
            }
            cout << "Path: (";
            cout << s.x << ", " << s.y << ") ->";
            for (int i = 0; i < node.path.size(); i++) {
                cout << "(" << node.path[i].first << "," << node.path[i].second << ")";
                if (i < node.path.size() - 1) {
                    cout << " -> ";
                }
            }
            cout << '\n';
            cout << "Path: ";
            for (int i = 0; i < list2.size(); i++) {
                cout << list2[i].index << " ";
            }
            return dist;
        }

        if (!visited.count(node))
        {
            visited.insert(node);

            for (int i = 0; i < movesHorse.size(); i++)
            {
                int x1 = x + movesHorse[i][0];
                int y1 = y + movesHorse[i][1];

                if (isValid(x1, y1, N + movesHorse[i][2])) {
                    Node nextNode = { x1, y1, dist + 1 };
                    nextNode.path = node.path;
                    nextNode.path.push_back({ x1, y1 });
                    q.push(nextNode);
                }
            }
        }
    }

    return INT_MAX;
}

void create_table(vector<Point>& list, double mi) {

    glClear(GL_COLOR_BUFFER_BIT);
    for (int i = 0; i < list.size(); i++) {
        glColor3f(3.0, 0.0, 0.0);

        string tmp = "--";
        if (list[i].figure == 0) {
            tmp = to_string(list[i].index);
        }
        else {
            tmp = (list[i].figure == 1) ? '-K' : '-H';
        }

        renderText(list[i].x, list[i].y, tmp);

        glBegin(GL_LINE_LOOP);
        glColor3f(1.0, 1.0, 0.0);

        glVertex3f(list[i].x - mi / 2, list[i].y - mi / 2, 0);
        glVertex3f(list[i].x - mi / 2, list[i].y + mi / 2, 0);
        glVertex3f(list[i].x + mi / 2, list[i].y + mi / 2, 0);
        glVertex3f(list[i].x + mi / 2, list[i].y - mi / 2, 0);
        glEnd();
    }
}

void display(void)
{

    glPointSize(6.0);

    int nKing, nHorse, n, tTmp = 1;
    cout << "Введите максимальную возможную длину : ";
    cin >> n;
    cout << "Введите позицию короля на пирамидной доске: ";
    cin >> nKing;
    cout << "Введите позицию коня на пирамидной доске:   ";
    cin >> nHorse;

    int up = 2;
    int nextBeg = 2;
    int dist = 1;

    vector<Point> list;
    Point first;
    first.index = 1;
    first.x = WIDTH / 2;
    first.y = HEIGHT - 50;
    list.push_back(first);

    double distB = (HEIGHT - 100) / n;
    double mi = distB, beg = first.x - distB;
    int cntW = 0, cntH = 0;

    if (n > 10) {
        mi -= 10 * (n - 10);
        distB -= 10 * (n - 10);
        list[0].x -= 10 * (n - 10);
    }

    int in = 2, rIn = 0, cIn = 0;
    while (tTmp <= n) {
        if (in == nextBeg) {
            dist++;
            nextBeg += up;
            up++;
            cntW = 1;
            cntH++;
            distB += mi;
            beg -= mi / 2;
            tTmp++;

            cIn = 0;
            rIn++;
            if (tTmp > n) {
                break;
            }
        }

        Point tmpP;
        tmpP.x = beg + (distB / dist) * cntW;
        cntW++;
        tmpP.y = HEIGHT - 50 - mi * cntH;
        tmpP.index = in;
        tmpP.figure = 0;
        tmpP.row = rIn;
        tmpP.col = cIn;
        tmpP.dist = tTmp;
        cIn++;
        list.push_back(tmpP);
        in++;
    }

    nHorse--, nKing--;
    list[nKing].figure = 1;
    list[nHorse].figure = 2;

    for (int i = 0; i < list.size(); i++) {
        cout << "Index: " << list[i].index << endl;
        cout << "Row: " << list[i].row << endl;
        cout << "Col: " << list[i].col << endl;
        cout << "Figure: " << list[i].figure << endl;
        cout << "Dist: " << list[i].dist << endl;
        cout << endl;
    }

    create_table(list, mi);

    cout << "\n\n\n";

    int horseX = list[nHorse].col, horseY = list[nHorse].row;

    int need;
    cout << "Введите до какой клетки хотите добраться: ";
    cin >> need;
    need--;
    Node src = { horseX,  horseY };
    Node dest = { list[need].row, list[need].col };
    fill_cell(list[need], mi);
    create_table(list, mi);
    if (src.x != dest.y && src.y != dest.y) { findShortestDistance(n, src, dest, list, mi); }


    glColor3f(0.0, 0.0, 1.0);
    fill_cell(list[nHorse], mi);
    glutSwapBuffers();
    glFlush();

}

int main(int argc, char* argv[]) {
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
