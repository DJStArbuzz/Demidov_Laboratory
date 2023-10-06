#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <set>
#include <iomanip>

using namespace std;

void read_info(int *A, int n) 
{
	for (int i = 0; i < n; i++) {
		cin >> A[i];
	}
		 
}

void swap_A(int& a, int& b) {
	if (a > b) {
		int tmp = a;
		a = b;
		b = a;
	}
}

void buble_sort(int *A, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 1; j < n; j++) {
			swap_A(A[j - 1], A[j]);
		}
	}
}

void write_info(int* A, int n) {
	for (int i = 0; i < n; i++) {
		cout << A[i] << " ";
	}
}

void solve()
{
	int n;
	cin >> n;

	int* A;
	A = new int[n];
	read_info(A, n);
	buble_sort(A, n);
	write_info(A, n);
}

int main() {
	solve();
}
