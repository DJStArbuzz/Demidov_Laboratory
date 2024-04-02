#include <iostream>
#include <vector>

using namespace std;

bool isValid(int x, int y) {
    return x >= 0 && x < 8 && y >= 0 && y < 8;
}

int main() {
    int knightX = 3, knightY = 6; // координаты коня
    vector<pair<int, int>> moves = { {-2, -1}, {-2, 1}, {2, -1}, {2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2} };

    for (auto move1 : moves) {
        int nextX = knightX + move1.first;
        int nextY = knightY + move1.second;
        if (isValid(nextX, nextY)) {
            cout << "(" << nextX << "," << nextY << ")" << endl;
            /*for (auto move2 : moves) {
                int nextX2 = nextX + move2.first;
                int nextY2 = nextY + move2.second;
                if (isValid(nextX2, nextY2)) {
                    cout << "(" << nextX2 << "," << nextY2 << ")" << endl;
                }
            }
            */
        }
    }

    return 0;
}
