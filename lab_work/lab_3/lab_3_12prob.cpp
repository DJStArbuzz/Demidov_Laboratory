#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <iomanip>

using namespace std;

// Ввод матрицы из консоли
void cin_for_matrix(int(&arrayA)[100][100], int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> arrayA[i][j];
		}
	}
}

// Вывод матрицы в консоль
void cout_res(int(&matrixRes)[100][100], int n)
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << matrixRes[i][j] << " ";
		}
		cout << endl;
	}
}

// Разарботка единичной матрицы
void create_unit_matrix(int(&unitMatrix)[100][100], int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			unitMatrix[i][j] = (i == j) ? 1 : 0;
		}
	}
}

// Умножение матрицы на число k
void additional_matrix_multiplication(int(&matrix)[100][100], int n, int k) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			matrix[i][j] *= k;
		}
	}
}

// Перемножение матриц
void multiplicationMatrix(int(&arrayFirst)[100][100], int(&arraySecond)[100][100], int n) {
	int arrayRes[100][100];

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

// Сложение матриц
void sum_matrix(int(&matrixRes)[100][100], int(&matrixA)[100][100], int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			matrixRes[i][j] += matrixA[i][j];
		}
	}
}

// Поиск определителя матрицы 
double search_determinant_of_matrix(int(&arrayA)[100][100], int n) {
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


// Вычисление значения выражения для 1-го задания
void find_function_for_problem1(int(&arrayA)[100][100], int(&unitMatrix)[100][100], int n) {
	// f(x) = x^(3) − 4x^(2) + 2x − 5
	int result[100][100];

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			result[i][j] = 0;
		}
	}

	int first[100][100];
	int second[100][100];
	int third[100][100];
	int fourth[100][100];

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			first[i][j] = arrayA[i][j];
			second[i][j] = arrayA[i][j];
			third[i][j] = arrayA[i][j];
			fourth[i][j] = unitMatrix[i][j];
		}
	}

	multiplicationMatrix(second, second, n);
	multiplicationMatrix(first, second, n);

	additional_matrix_multiplication(second, n, -4);
	additional_matrix_multiplication(third, n, 2);
	additional_matrix_multiplication(fourth, n, -5);

	cout << "\n1-ый член многочлена:" << endl;
	cout_res(first, n);

	cout << "\n2-ый член многочлена:" << endl;
	cout_res(second, n);

	cout << "\n3-ий член многочлена:" << endl;
	cout_res(third, n);

	cout << "\n4-ый член многочлена:" << endl;
	cout_res(fourth, n);


	sum_matrix(result, first, n);
	sum_matrix(result, second, n);
	sum_matrix(result, third, n);
	sum_matrix(result, fourth, n);

	cout << "\nИтоговый результат:" << endl;
	cout_res(result, n);
}

void problem_1() {
	/* Задание 1, вариант 1
	На вход программы из файла поступает квадратная матрица .
	Элементы матрицы — вещественные числа. Дан многочлен f(x) или многочлены f(x) и g(x).
	Выражение A − k следует понимать как A − kE, где E — единичная матрица.
	Необходимо вычислить значение выражения в и вывести промежуточные результаты
	вычислений в файл. Необходимо использовать статический массив.
	Пользоваться классом vector запрещено.

	1. f(x) = x^(3) − 4x^(2) + 2x − 5. Найдите f(A).*/

	cout << "Введити число n - порядок матрицы A: ";

	// n - порядок матрицы А
	int n;
	cin >> n;

	cout << "Введите элементы матрицы А размера n * n" << endl;

	// Матрица А размером n * n
	int arrayA[100][100];
	cin_for_matrix(arrayA, n);

	int unitMatrix[100][100];
	create_unit_matrix(unitMatrix, n);

	find_function_for_problem1(arrayA, unitMatrix, n);

	cout << endl;
}

void create_matrix_for_problem2(int(&array)[100][100], int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			array[j][i] = (abs((i + 1) - (j + 1)));
		}
	}
}

void problem_2() {
	/* Задание 2, вариант 17
	Вычислите определитель порядка n, элементы которого заданы условием 
	aij = |i − j|. Нумерация строк и столбцов начинается с единицы.
	*/


	cout << "Введити число n - порядок матрицы A: ";

	// n - порядок матрицы А
	int n;
	cin >> n;

	// Матрица А размером n * n
	// Aij = |i - j|
	int arrayIEqualJ[100][100];
	create_matrix_for_problem2(arrayIEqualJ, n);

	cout << "\nМатрица вида Aij = |i - j|: " << endl;
	cout_res(arrayIEqualJ, n);

	cout << "\nОпределитель матрицы: ";
	double result = search_determinant_of_matrix(arrayIEqualJ, n);
	cout << result << endl;
	
}


int main()
{
	setlocale(LC_ALL, "Russian");

	bool flag = true;
	int problem;
	while (flag) {
		std::cin >> problem;
		switch (problem)
		{
		case(1):
			problem_1();
			break;
		case(2):
			problem_2();
			break;
		default:
			problem_1();
			break;
		}
	}
}
