#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <iomanip>

using namespace std;

// 3 задание

// Поиск определителя матрицы 
double search_determinant_of_matrix(double(&arrayA)[3][3], int n) {
	double arrayB[100][100];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			arrayB[i][j] = 1.0 * arrayA[i][j];
		}
	}

	double determinant = -1;

	if (n == 1) {
		return arrayA[0][0];
	}
	else if (n == 2) {
		determinant = arrayA[0][0] * arrayA[1][1] - arrayA[1][0] * arrayA[0][1];
	}
	else if (n > 2) {
		determinant = 1.0;
		for (int i = 0; i < n; i++) {
			int tmp = i;
			for (int j = i + 1; j < n; j++) {
				if (abs(arrayB[j][i]) > abs(arrayB[tmp][i])) {
					tmp = j;
				}
			}

			if (tmp != i) {
				swap(arrayB[i], arrayB[tmp]);
				determinant *= -1;
			}

			if (arrayB[i][i] == 0.0) {
				return 0;
			}

			determinant *= arrayB[i][i];
			for (int j = i + 1; j < n; j++) {
				double factor = arrayB[j][i] / arrayB[i][i];
				for (int k = i + 1; k < n; k++) {
					arrayB[j][k] -= factor * arrayB[i][k];
				}
			}
		}

		return determinant;

	}

	return determinant;
}

// Разарботка единичной матрицы
void create_unit_matrix(double(&unitMatrix)[3][3], int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			unitMatrix[i][j] = (i == j) ? 1 : 0;
		}
	}
}

// Умножение матрицы на число k
void additional_matrix_multiplication(double(&matrix)[3][3], int n, int k) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			matrix[i][j] *= k;
		}
	}
}

// Перемножение матриц
void multiplicationMatrix(double(&arrayFirst)[3][3], double(&arraySecond)[3][3], int n) {
	int arrayRes[3][3];

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int sum = 0;
			for (int k = 0; k < n; k++) {
				sum += arrayFirst[i][k] * arraySecond[k][j];
			}
			arrayRes[i][j] = sum;
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			arrayFirst[i][j] = arrayRes[i][j];
		}
	}
}

// Обратная матрица

void reverse_matrix(double(&A)[3][3], int n) {
	double B[3][3];

	float det = search_determinant_of_matrix(A, n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			B[i][j] = (A[(j + 1) % 3][(i + 1) % 3] * A[(j + 2) % 3][(i + 2) % 3]
				- (A[(j + 1) % 3][(i + 2) % 3] *
					A[(j + 2) % 3][(i + 1) % 3]) ) / det;
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			A[i][j] = B[i][j];
		}
	}

}

// Сложение матриц
void sum_matrix(double(&matrixRes)[3][3], double(&matrixA)[3][3], int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			matrixRes[i][j] += matrixA[i][j];
		}
	}
}

// Вывод матрицы
void cout_res(double(&matrixRes)[3][3], int n)
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << matrixRes[i][j] << " ";
		}
		cout << endl;
	}
}



int main()
{
	setlocale(LC_ALL, "Russian");

	/* Задание 3, вариант 10
	Напишите программу, решающую заданное матричное уравнение или систему
	матричных уравнений. Выполните проверку, выводя промежуточные результаты
	вычислений. Данные считывать с файла, ответ и промежуточные результаты вывести
	в файл. Пользоваться классом vector запрещено.

		  |-14   1   4|   |  1 -2  3|
	5X + X|-12  -4   6| = |  3 -2  1|
		  | 11  -1 -10|   |  1  0  1|

	5X + XA = B
	X(5 + A) = B
	X = B / (5 + A), где A + 5 = A + 5E, где E — единичная матрица.

	X = B * (A + 5E) ^ (-1)
	*/

	int n = 3;
	double arrayA[3][3] = {
		{-14,  1,   4},
		{-12, -4,   6},
		{11,  -1, -10} };

	cout << "\nМатрица A:" << endl;
	cout_res(arrayA, 3);

	double arrayB[3][3] = {
		{1,  -2,   3},
		{3,  -2,   1},
		{1,   0,   1} };

	cout << "\nМатрица B:" << endl;
	cout_res(arrayB, 3);

	double arrayE[3][3];

	create_unit_matrix(arrayE, n);
	additional_matrix_multiplication(arrayE, 3, 5);

	cout << "\nМатрица E (доп):" << endl;
	cout_res(arrayE, 3);

	// 5X + XA  = B
	// X(5 + A) = B
	// X(5E + A) = B

	sum_matrix(arrayA, arrayE, 3);

	// X = B / (5E + A)
	// X = B * (5E + A) ^ (-1)


	reverse_matrix(arrayA, 3);

	/*
	1 1 2
	6 1 6
	1 2 3
	*/

	cout << "\nМатрица А в степени -1" << endl;
	cout_res(arrayA, 3);

	multiplicationMatrix(arrayB, arrayA, 3);

	cout << "\nИскомая матрица X:" << endl;
	cout_res(arrayB, 3);
}
