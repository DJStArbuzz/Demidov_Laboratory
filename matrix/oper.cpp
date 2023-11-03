#include <iostream>
#include <vector>

using namespace std;

// C = A + B
void sum_matrix(vector<vector<int>> &A, vector<vector<int>>& B, vector<vector<int>>& C) {
	for (int i = 0; i < A.size(); i++) {
		for (int j = 0; j < A[i].size(); j++) {
			C[i][j] = A[i][j] + B[i][j];
		}
	}
}

// C = A - B
void dif_matrix(vector<vector<int>>& A, vector<vector<int>>& B, vector<vector<int>>& C) {
	for (int i = 0; i < A.size(); i++) {
		for (int j = 0; j < A[i].size(); j++) {
			C[i][j] = A[i][j] - B[i][j];
		}
	}
}

// C = A 
void assig_matrix(vector<vector<int>>& A, vector<vector<int>>& C) {
	for (int i = 0; i < A.size(); i++) {
		for (int j = 0; j < A[i].size(); j++) {
			C[i][j] = A[i][j];
		}
	}
}

// C = k * A 
void mult_const_matrix(vector<vector<int>>& A, vector<vector<int>>& C, int k) {
	for (int i = 0; i < A.size(); i++) {
		for (int j = 0; j < A[i].size(); j++) {
			C[i][j] = k * A[i][j];
		}
	}
}

// C = A * B
void mult_matrix(vector<vector<int>>& A, vector<vector<int>>& B, vector<vector<int>>& C) {
	for (int i = 0; i < A.size(); i++) {
		for (int j = 0; j < A[i].size(); j++) {
			C[i][j] = 0;
			for (int k = 0; k < A.size(); k++) {
				C[i][j] += A[i][k] * B[k][j];
			}
		}
	}
}



// 4*X*X + 5*X - 6
int main() {
	int n;
	cin >> n;

	vector<vector<int>> X(n, vector<int>(n));
	vector<vector<int>> TMP(n, vector<int>(n));
	vector<vector<int>> A2(n, vector<int>(n));
	vector<vector<int>> A1(n, vector<int>(n));
	vector<vector<int>> A0(n, vector<int>(n));
	vector<vector<int>> Res(n, vector<int>(n));

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> X[i][j];
		}
	}
	
	mult_matrix(X, X, TMP);
	assig_matrix(TMP, A2);

	mult_const_matrix(A2, TMP, 4);
	assig_matrix(TMP, A2);

	mult_const_matrix(X, TMP, 5);
	assig_matrix(TMP, A1);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			TMP[i][j] = 0;
		}
		TMP[i][i] = 1;
	}
	mult_const_matrix(TMP, A0, -6);

	sum_matrix(A2, A1, TMP);
	sum_matrix(TMP, A0, Res);





}
