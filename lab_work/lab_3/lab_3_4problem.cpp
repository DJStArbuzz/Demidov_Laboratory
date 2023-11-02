#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <fstream>

using namespace std;

// Процедура для вывода команд
void start() {
	cout << "Меню:" << endl;
	cout << "1. генерация случайной матрицы" << endl;
	cout << "2. вывод матрицы на экран" << endl;
	cout << "3. вывод матрицы в файл" << endl;
	cout << "4. ввод матрицы с клавиатуры" << endl;
	cout << "5. ввод матрицы из файла" << endl;
	cout << "6. вычисление характеристики" << endl;
	cout << "7. преобразование матрицы" << endl;
	cout << "8. печать матрицы после преобразования на экран" << endl;
	cout << "9. печать матрицы после преобразования в файл" << endl;
	cout << "10. выход из программы" << endl;
	cout << endl;
}

// 2. вывод матрицы на экран,
void cout_to_console_matrix(double**& matrix, int order) {
	for (int i = 0; i < order; i++) {
		for (int j = 0; j < order; j++) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}

// 1. генерация случайной матрицы
int random_matrix(int**& matirx) {
	int order = rand() % 10; // Порядок матрицы
	int start = 0;           // Начало диапазона
	int end = 100;           // Конец диапазона

	if (order == 0) {
		order = 1;
	}

	double** matrix;         //  'Случайная' матрица
	matrix = new double* [order];

	for (int i = 0; i < order; i++) {
		matrix[i] = new double[order];
	}

	for (int i = 0; i < order; i++) {
		for (int j = 0; j < order; j++) {
			matrix[i][j] = rand() % 100 * 1.0;
		}
	}

	cout << "Разработка матрицы, заполненной случайными значениями." << endl;
	cout << "Порядок матрицы: " << order << endl;
	cout << "'Случайная' матрица:" << endl;
	cout_to_console_matrix(matrix, order);

	cout << endl;

	return order;
}

int main()
{
	/*
	Задание 4, вариант 7
	Интерфейс программы должен быть выполнен в виде меню. Каждый пункт меню
	— это отдельная функция. Меню состоит из следующих пунктов:

	1. генерация случайной матрицы,
	2. вывод матрицы на экран,
	3. вывод матрицы в файл,
	4. ввод матрицы с клавиатуры,
	5. ввод матрицы из файла,
	6. вычисление характеристики,
	7. преобразование матрицы,
	8. печать матрицы после преобразования на экран,
	9. печать матрицы после преобразования в файл,
	10. выход из программы.

	Вариант характеристики:
	Наибольший элемент матрицы расположен ниже побочной диагонали.


	*/
	setlocale(LC_ALL, "Russian");

	start();

	int** matrix;

	int order = 2;
	bool flag = true;
	int problem;

	while (flag) {
		std::cin >> problem;
		switch (problem)
		{
		case(0):
			start();
			break;
		case(1):
			order = random_matrix(matrix);
			break;
			/*
			case(2):
				problem_2();
				break;
			case(3):
				problem_3();
				break;
			case(4):
				problem_4();
				break;
			case(5):
				problem_5();
				break;
			case(6):
				problem_6();
				break;
			case(7):
				problem_7();
				break;
			case(8):
				problem_8();
				break;
			case(9):
				problem_8();
				break;
			*/

		case(-1):
			return 0;
		default:
			start();
			break;
		}
	}

}
