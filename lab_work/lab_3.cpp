#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

void cin_for_matrix(int (& arrayA)[100][100], int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> arrayA[i][j];
		}
	}
}

void create_unit_matrix(int(&unitMatrix)[100][100], int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			unitMatrix[i][j] = (i == j) ? 1 : 0;
		}
	}
}

void multiplicationMatrix(int(&arrayFirst)[100][100], int(&arraySecond)[100][100], int n) {
	int arrayRes[100][100];

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; i++) {
			int sum = 0;
			for (int k = 0; k < n; k++) {
				sum += arrayFirst[i][k] * arraySecond[k][j];
			}
			cout << i << endl;
		}
	}



	

}

void cout_res(int(&matrixRes)[100][100], int n)
{
	cout << "Результат выражения:" << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << matrixRes[i][j] << " ";
		}
		cout << endl;
	}
}


void find_function(int(&arrayA)[100][100], int(&unitMatrix)[100][100], int n) {
	// f(x) = x^(3) − 4x^(2) + 2x − 5
	int result[100][100];

	int first[100][100];
	int second[100][100];
	int third[100][100];
	int fourth[100][100];

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			first[i][j] = arrayA[i][j];
			second[i][j] = arrayA[i][j];
			third[i][j] = arrayA[i][j] * 2;
			fourth[i][j] = unitMatrix[i][j] * 5;
		}
	}

	multiplicationMatrix(second, second, n);


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

	find_function(arrayA, unitMatrix, n);

	cout << endl;
}

void problem_2() {
	/* Задание 2, вариант 9
	Дано целое число K (> 0) и целочисленный массив размера N.
	Поменять местами последнюю серию массива и его серию с номером K.
	Если серий в массиве меньше K, то вывести массив без изменений.
	*/

	
}


void problem_3() {
	/* Задание 3, вариант 8
	В целочисленном массиве Х(N) определить: максимальный элемент среди
	положительных нечетных элементов, минимальный среди положительных
	четных элементов, первые два совершенных числа. Удалить найденные элементы.
	Процедуру повторить еще раз. В программе написать методы: удаления
	элемента, определения максимального и минимального элементов согласно заданию,
	проверки условия — число совершенное.*/

	
}

void problem_4()
{
	
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
		case(3):
			problem_3();
			break;
		case(4):
			problem_4();
			break;
		default:
			problem_1();
			break;
		}
	}
}
