#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>
#include <algorithm>

using namespace std;

struct Point {
	double x, y;

	// Перегрузка оператора сложения
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

double dist(Point A) {
	return A.x * A.x + A.y * A.y;
}

double dist2(Point A) {
	return sqrt(A.x * A.x + A.y * A.y);
}

double dot(Point A, Point B) {
	return A.x * B.x + A.y * B.y;
}

double cross(Point A, Point B) {
	return A.x * B.y - A.y * B.x;
}

int main() {
	int n;
	cin >> n;

	vector<Point> list(n);
	for (int i = 0; i < n; i++) {
		cin >> list[i].x >> list[i].y;
	}
	
	double res = 0.0;
	int ind = 0, tmpI = 1;

	while (tmpI != n) {
		res += (list[ind].x + list[tmpI].x) * (list[tmpI].y - list[ind].y);
		tmpI++;
		ind++;
	}

	tmpI = n - 1;
	ind = 0;
	res += (list[ind].x + list[tmpI].x) * (list[ind].y - list[tmpI].y);

	cout << fixed << setprecision(5) << abs(res) / 2;

	return 0;
}
