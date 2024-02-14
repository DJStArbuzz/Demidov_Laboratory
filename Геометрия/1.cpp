#include <iostream>         
#include <vector>
#include <string>
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

// sqrt(dist(A)) = |A|
double dist(Point A) {
	return A.x * A.x + A.y * A.y;
}

double dist2(Point A) {
	return sqrt(A.x * A.x + A.y * A.y);
}

// (a, b) = a.x * b.x + a.y * b.y = a * b - скалярное произведение
double dot(Point A, Point B) {
	return A.x * B.x + A.y * B.y;
}

// [a b] = a.x * b.y - a.y * b.x - векторное произведение
double cross(Point A, Point B) {
	return A.x * B.y - A.y * B.x;
}

int main()
{

}
