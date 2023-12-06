#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <vector>
#include <set>

using namespace std;

int main() {
	int n;
	cin >> n;
	
	vector<long long> list(n);
	for (int i = 0; i < n; i++) {
		cin >> list[i];
	}

	/*
		int count_el = 0;
		int res = 0;
		for (int i = 0; i < n; i++)
		{
		count_el = 0;
		for (int j = 0; j < n; j++){
		if (A[j] - A[i] >= && A[j] - A[i] <= 5){
		count_el++;}
		
		
		}
		res = max(res, count_el);
		}
		cout << count_el
	*/

	sort(list.begin(), list.end());
	int l = 0, res = 0;
	
	for (int r = 0; r < n; r++) {
		while (list[r] - list[l] > 5) {
			l++;
		}

		res = max(res, r - l + 1);
	}
	
	cout << res;
  // O(n * logn)
}
