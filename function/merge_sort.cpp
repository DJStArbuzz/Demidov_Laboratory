#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <set>
#include <iomanip>

using namespace std;

int Buf[1000000];

void merge(int* A, int l, int mid, int r) {
	for (int i = l; i < r; i++) {
		Buf[i] = A[i];
	}
	int u1 = l, u2 = mid, u3 = l;

	while (u1 < mid && u2 < r) {
		if (Buf[u1] < Buf[u2]) {
			A[u3] = Buf[u1];
			u1++;
			u3++;
		} 
		else {
			A[u3] = Buf[u2];
			u2++;
			u3++;
		}
	}
	while (u1 < mid) {
		A[u3] = Buf[u1];
		u1++;
		u3++;
	}
	while (u2 < r) {
		A[u2] = Buf[u2];
		u2++;
		u3++;
	}
}

void merge_sort(int* A, int l, int r) {
	int mid = (r - l) / 2 + l;
	if (r - l > 1) {
		merge_sort(A, l, mid);
		merge_sort(A, mid, r);
		merge(A, l, mid, r);
	}
}

void read_info(int* A, int n) 
{
	for (int i = 0; i < n; i++) {
		cin >> A[i];
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
	merge_sort(A, 0, n);
	write_info(A, n);
}

int main() {
	solve();
}
