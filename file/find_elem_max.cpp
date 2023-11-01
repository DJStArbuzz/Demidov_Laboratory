#include <iostream>
#include <vector>
#include <set>
#include <iomanip>
#include <algorithm>
#include <cmath>

#include <fstream>
// file stream

using namespace std;

void read_info(vector<int> &A, int &n) {
	freopen("input.txt", "rt", stdin);
	cin >> n;

	int elem;
	for (int i = 0; i < n; i++) {
		cin >> elem;
		A.push_back(elem);
	}
}

void write_info(int max1, int max2, int max3, int max4, int max5) {
	freopen("outout.txt", "wt", stdout);
	cout << max1 << " ";
	cout << max2 << " ";
	cout << max3 << " ";
	cout << max4 << " ";
	cout << max5 << " ";

}

void solve(vector<int> &A) {
	sort(A.begin(), A.end());

}

int main() {
	int n;
	vector<int> A(n);
	read_info(A, n);
	solve(A);
	write_info(A[A.size() - 1], A[A.size() - 2], A[A.size() - 3], A[A.size() - 4], A[A.size() - 5]);


}
