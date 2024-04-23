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
const int NUM_OF_ROWS = 9;
const auto FONT = GLUT_BITMAP_TIMES_ROMAN_24;
const double R = 0.5;

using namespace std;

vector<vector<int>> movesHorse = {
    {-3, -1, 0},
    { 2, -1, 0},
    { 3,  1,  0},
    {-2,  1,  0},
    {-3, -2, 0},
    { 1, -2, 0},
    {-1,  2,  0},
    { 3,  2,  0},
    {-1, -3, 0},
    {-2, -3, 0},
    { 1,  3,  0},
    { 2,  3,  0}, };

vector<vector<int>> movesKing = {
    { 0,  1,  0},
    { 1,  1,  0},
    {-1,  0,  0},
    { 1,  0,  0},
    { 0, -1, 0},
    {-1, -1, 0},
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

void fill_cell(Point point, double width, double height) {
    glBegin(GL_QUADS);
    glColor3f(3.0, 0.0, 0.0);
    glVertex3f(point.x - width / 2, point.y - height / 2, 0);
    glVertex3f(point.x - width / 2, point.y + height / 2, 0);
    glVertex3f(point.x + width / 2, point.y + height / 2, 0);
    glVertex3f(point.x + width / 2, point.y - height / 2, 0);
    glEnd();
}


void horse(Point tmp, vector<Point>& list, double width, double height) {
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

void king(Point tmp, vector<Point>& list, double width, double height) {

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


int findShortestDistanceHorse(int N, Node s, Node dest, vector<Point>& list, double width, double height)
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
            node.path.push_back({ dest.x, dest.y });
            cout << dest.x << " " << endl;

            vector<Point> list2;
            for (int i = 0; i < node.path.size(); i++) {
                for (int j = 0; j < list.size(); j++) {
                    if (list[j].col == node.path[i].first && list[j].row == node.path[i].second) {
                        list2.push_back(list[j]);
                        fill_cell(list[j], width, height);
                    }
                }
            }
            cout << "Path: (";
            cout << s.x << ", " << s.y << ") ->";
            for (int i = 0; i < node.path.size() - 1; i++) {
                cout << "(" << node.path[i].first << "," << node.path[i].second << ")";
                if (i < node.path.size() - 1) {
                    cout << " -> ";
                }
            }
            cout << '\n';
            cout << "Path: ";
            for (int i = 0; i < list2.size() - 1; i++) {
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


int findShortestDistanceKing(int N, Node s, Node dest, vector<Point>& list, double width, double height)
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
            node.path.push_back({ dest.x, dest.y });
            cout << dest.x << " " << endl;

            vector<Point> list2;
            for (int i = 0; i < node.path.size(); i++) {
                for (int j = 0; j < list.size(); j++) {
                    if (list[j].col == node.path[i].first && list[j].row == node.path[i].second) {
                        list2.push_back(list[j]);
                        fill_cell(list[j], width, height);
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

            for (int i = 0; i < movesKing.size(); i++)
            {
                int x1 = x + movesKing[i][0];
                int y1 = y + movesKing[i][1];

                if (isValid(x1, y1, N + movesKing[i][2])) {
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

void create_table(vector<Point>& list, double width, double height) {

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

        glVertex3f(list[i].x - width / 2, list[i].y - height / 2, 0);
        glVertex3f(list[i].x - width / 2, list[i].y + height / 2, 0);
        glVertex3f(list[i].x + width / 2, list[i].y + height / 2, 0);
        glVertex3f(list[i].x + width / 2, list[i].y - height / 2, 0);
        glEnd();
    }
}

bool compare(Point first, Point second) {
    return (first.index > second.index);
}
void display(void)
{

    glPointSize(6.0);

    int kh, pos;
    cout << "Введите с чем будете работать (1 - Конь, 2 - Король): ";
    cin >> kh;
    int n, tTmp = 1;
    cout << "Введите максимальную возможную длину : ";
    cin >> n;
    cout << "Введите позицию фигуры на пирамидной доске: ";
    cin >> pos;
    vector<Point> list;

    double sizePointH = (1000 - 100) / NUM_OF_ROWS;
    double sizePointW = (1000 - 100) / n / 2;

    double posI = 100 - sizePointW / 2;
    double posJ = 100 + sizePointH / 2;

    int index = n * NUM_OF_ROWS - n + 1;
    int rowInd = n - 1;
    int colInd = NUM_OF_ROWS - 1;

    double begI = 0;
    double begJ = 0;

    int tmp = 1;

    for (int i = NUM_OF_ROWS - 1; i >= 0; i--){
        for (int j = 0; j < n; j++) {
            Point tmp;

            tmp.x = posI + begI;
            begI += sizePointW;

            tmp.y = posJ + begJ;

            tmp.index = index;
            index++;

            tmp.row = i;
            tmp.col = j;
            rowInd++;

            tmp.dist = n;

            list.push_back(tmp);
        }

           
        begI = tmp * sizePointW / 2;
        tmp++;
        index -= 2 * n;
            
        begJ += sizePointH;
    }
    
    sort(list.rbegin(), list.rend(), compare);
    
    pos--;
    if (kh == 1) {
        list[pos].figure = 1;
    }
    else {
        list[pos].figure = 2;
    }

    for (int i = 0; i < list.size(); i++) {
        cout << "Index: " << list[i].index << endl;
        cout << "Row: " << list[i].row << endl;
        cout << "Col: " << list[i].col << endl;
        cout << "Figure: " << list[i].figure << endl;
        cout << "Dist: " << list[i].dist << endl;
        cout << endl;
    }

    create_table(list, sizePointW, sizePointH);

    cout << "\n\n\n";

    if (kh == 1) {
        int horseX = list[pos].col, horseY = list[pos].row;
        vector<Point> tmpList;

        for (auto move1 : movesHorse)
        {
            int nextY = horseY + move1[1];
            int nextX = horseX;

            nextX += move1[0];
            if (isValid(nextX, nextY, list[pos].dist + move1[2])) {
                for (int i = 0; i < list.size(); i++)
                {
                    if (list[i].row == nextY && list[i].col == nextX) {
                        glColor3f(1.0, 1.0, 0.0);
                        fill_cell(list[i], sizePointW, sizePointH);
                        renderText(list[i].x, list[i].y, "OK");
                        tmpList.push_back(list[i]);
                        break;
                    }
                }
            }
        }


        for (int i = 0; i < tmpList.size(); i++) {
            glColor3f(1.0, 1.0, 0.0);
            horse(tmpList[i], list, sizePointW, sizePointH);
        }


        cout << "Введите точку назначения: ";
        int indexN;
        cin >> indexN;
        indexN--;
        glColor3f(0.0, 1.0, 0.0);
        Node src = { horseX,  horseY };
        Node dest = { list[indexN].col, list[indexN].row };
        fill_cell(list[indexN], sizePointW, sizePointH);
        fill_cell(list[pos], sizePointW, sizePointH);
        findShortestDistanceHorse(n, src, dest, list,sizePointW, sizePointH);
    }
    else {
        int kingX = list[pos].col, kingY = list[pos].row;
        vector<Point> tmpList;

        for (auto move1 : movesKing)
        {
            int nextY = kingY + move1[1];
            int nextX = kingX;

            nextX += move1[0];
            if (isValid(nextX, nextY, list[pos].dist + move1[2])) {
                for (int i = 0; i < list.size(); i++)
                {
                    if (list[i].row == nextY && list[i].col == nextX) {
                        glColor3f(1.0, 1.0, 0.0);
                        fill_cell(list[i], sizePointW, sizePointH);
                        renderText(list[i].x, list[i].y, "OK");
                        tmpList.push_back(list[i]);
                        break;
                    }
                }
            }
        }


        for (int i = 0; i < tmpList.size(); i++) {
            glColor3f(1.0, 1.0, 0.0);
            king(tmpList[i], list, sizePointW, sizePointH);
        }


        cout << "Введите точку назначения: ";
        int indexN;
        cin >> indexN;
        indexN--;
        glColor3f(0.0, 1.0, 0.0);
        Node src = { kingX,  kingY };
        Node dest = { list[indexN].col, list[indexN].row };
        fill_cell(list[indexN], sizePointW, sizePointH);
        fill_cell(list[pos], sizePointW, sizePointH);
        findShortestDistanceKing(n, src, dest, list, sizePointW, sizePointH);
    }



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


