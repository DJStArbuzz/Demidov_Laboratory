#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <cmath>
#include <algorithm> 

using namespace std;

int main() {
	int n;
	cin >> n;
	
	int* A;
	A = new int[n];

	for (int i = 0; i < n; i++) {
		cin >> A[i];
	}

	int l = 0;
	int r = 4 * n;
	int mid;

	while (r - l) {
		mid = (r + l) / 2;
		int count_tmp = 0;
		int flag = true;

		for (int i = 0; i < n; i++) {
			if (A[i] > mid) {
				flag = false;
			}
			else {
				count_tmp += A[i] - mid;
			}
		}
		if (flag = false) {
			l = mid;
		}
		else {
			if (count_tmp < mid) {
				l = mid;
			}
			else {
				r = mid;
			}
		}


	}


	mid = l;
	int count_tmp = 0;
	int flag = true;

	for (int i = 0; i < n; i++) {
		if (A[i] > mid) {
			flag = false;
		}
		else {
			count_tmp += A[i] - mid;
		}
	}
	if (flag = false) {
		cout << r;
	}
	else {
		if (count_tmp < mid) {
			cout << r;
		}
		else {
			cout << l;
		}
	}


}
