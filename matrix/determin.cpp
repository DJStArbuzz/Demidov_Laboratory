#include <iostream>
#include <vector>

using namespace std;

void gen_p(vector<int> &P, int pos) {
	if (pos == P.size()) {
		/*
		for (int i = 0; i < P.size(); i++) {
			cout << P[i] << " ";
		}
		cout << endl;*/
		long long buf = 0;
		for (int i = 0; i < P.size(); i++) {
			buf *= matrix[P[i]][i];
		}
		int count = 0;
		count_inv(P, count);
		if (count % 2 == 0) {
			det += buf;
		}
		else {
			det -= buf;
		}
	}
	else {
		for (int i = 0; i < P.size(); i++) {
			P[pos] = i;
			bool flag = true;
			
			for (int j = 0; j < pos; j++) {
				if (P[pos] == P[j]) {
					flag = false;
				}
			}

			if (flag) {
				gen_p(P, pos + 1);
			}
		}
	}
}

void count_inv(vector<int>& P, int& count) {
	for (int i = 0; i < P.size(); i++) {
		for (int j = 0; j < i; j++) {
			if (P[j] > P[i]) {
				count++;
			}
		}
	}
}

vector<vector<int>> matrix(10, vector<int>(10));
long long det = 0;


int main(){
	vector<int> P(7);
	int pos = 0;
	gen_p(P, pos);
}
