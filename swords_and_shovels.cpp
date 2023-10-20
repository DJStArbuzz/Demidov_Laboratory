#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <cmath>
#include <algorithm> 

using namespace std;

int main() {
	int a, b;
	cin >> a >> b;

	int l = 0;
	int r = a + b;
	int mid;
	while (r - l > 1) {
		mid = (r + l) / 2;
		if (mid > a || mid > b || a + b < 3 * mid) {
			r = mid;
		}
		else {
			l = mid;
		}
	}
	cout << l;
}
