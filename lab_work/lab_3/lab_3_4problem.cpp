#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

const int order = 3;

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

void menu_for_7() {
	cout << "1. возведение матрицы в -1 степень" << endl;
	cout << "2. перемножение матрицы на саму же себя" << endl;
	cout << "3. сложение с единичной матрицей" << endl;
	cout << "4. умножение на некоторое число k" << endl;
	cout << "5. транспонирование матрицы" << endl;
	cout << "6. вернуться в меню" << endl;
	cout << endl;
}

// 2. вывод матрицы на экран
// 8. печать матрицы после преобразования на экран
void cout_to_console_matrix(double**& matrix) {
	for (int i = 0; i < order; i++) {
		for (int j = 0; j < order; j++) {
			cout << fixed << setprecision(3) << matrix[i][j] << " ";
		}
		cout << endl;
	}

	cout << endl;
}


// 7. преобразование матрицы

// Поиск определителя матрицы 
double search_determinant_of_matrix(double**& matrix) {
	double** arrayB;
	arrayB = new double* [order];
	for (int i = 0; i < order; i++) {
		arrayB[i] = new double[order];
	}

	for (int i = 0; i < order; i++) {
		for (int j = 0; j < order; j++) {
			arrayB[i][j] = 1.0 * matrix[i][j];
		}
	}

	double determinant = -1;

	if (order == 1) {
		return matrix[0][0];
	}
	else if (order == 2) {
		determinant = matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1];
	}
	else if (order > 2) {
		determinant = 1.0;
		for (int i = 0; i < order; i++) {
			int tmp = i;
			for (int j = i + 1; j < order; j++) {
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
			for (int j = i + 1; j < order; j++) {
				double factor = arrayB[j][i] / arrayB[i][i];
				for (int k = i + 1; k < order; k++) {
					arrayB[j][k] -= factor * arrayB[i][k];
				}
			}
		}

		return determinant;

	}

	return determinant;
}

// 7.1. возведение матрицы в -1 степень
double** reverse_matrix(double** &matrix) {
	double** secondMatrix;
	secondMatrix = new double* [order];
	for (int i = 0; i < order; i++) {
		secondMatrix[i] = new double[order];
	}

	float det = search_determinant_of_matrix(matrix);
	for (int i = 0; i < order; i++) {
		for (int j = 0; j < order; j++) {
			secondMatrix[i][j] = (matrix[(j + 1) % 3][(i + 1) % 3] * matrix[(j + 2) % 3][(i + 2) % 3]
				- (matrix[(j + 1) % 3][(i + 2) % 3] *
					matrix[(j + 2) % 3][(i + 1) % 3])) / det;
		}
	}

	return secondMatrix;
}

// 7.2. перемножение матрицы на саму же себя
double** multiplicationMatrix(double**& matrix) {
	double** secondMatrix;
	double** resMatrix;

	secondMatrix = new double* [order];
	resMatrix = new double* [order];

	for (int i = 0; i < order; i++) {
		secondMatrix[i] = new double[order];
		resMatrix[i] = new double[order];
	}

	secondMatrix = matrix;

	for (int i = 0; i < order; i++) {
		for (int j = 0; j < order; j++) {
			int sum = 0;
			for (int k = 0; k < order; k++) {
				sum += matrix[i][k] * secondMatrix[k][j];
			}
			resMatrix[i][j] = sum;
		}
	}

	return resMatrix;
}

// 7.3. сложение с единичной матрицей

void sum_matrix(double**& matrix, double**& unitMatrix) {
	for (int i = 0; i < order; i++) {
		for (int j = 0; j < order; j++) {
			matrix[i][j] += unitMatrix[i][j];
		}
	}
}

// 7.4. умножение на некоторое число k

void additional_matrix_multiplication(double**& matrix) {
	cout << "Введите некоторое число k: ";
	
	int k;
	cin >> k;


	for (int i = 0; i < order; i++) {
		for (int j = 0; j < order; j++) {
			matrix[i][j] *= k;
		}
	}
}

// 7.5. транспонирование матрицы
double** transpose_matrix(double**& matrix) {
	double** resMatrix;
	resMatrix = new double* [order];
	for (int i = 0; i < order; i++) {
		resMatrix[i] = new double[order];
	}

	for (int i = 0; i < order; i++) {
		for (int j = 0; j < order; j++) {
			resMatrix[j][i] = matrix[i][j];
		}
	}

	return resMatrix;
}

// Разарботка единичной матрицы
void create_unit_matrix(double**& unitMatrix) {
	for (int i = 0; i < order; i++) {
		for (int j = 0; j < order; j++) {
			unitMatrix[i][j] = (i == j) ? 1 : 0;
		}
	}
}


// выбор операции
void operation_with_matrix(double** &matrix) {
	menu_for_7();

	int choise; // номер выбранной операции
	cin >> choise;

	switch(choise) {
		case(1):
			matrix = reverse_matrix(matrix);
			cout << endl;
			break;

		case(2):
			matrix = multiplicationMatrix(matrix);
			cout << endl;
			break;

		case(3):
			// Единичная матрица порядка 3
			double** unitMatrix;
			unitMatrix = new double* [order];
			for (int i = 0; i < order; i++) {
				unitMatrix[i] = new double[order];
			}
			create_unit_matrix(unitMatrix);

			sum_matrix(matrix, unitMatrix);
			cout << endl;
			break;

		case(4):
			additional_matrix_multiplication(matrix);
			cout << endl;
			break;

		case(5):
			matrix = transpose_matrix(matrix);
			cout << endl;
			break;

		case(6):
			cout << endl;
			break;
	}
}

// проверка на некорректный ввод данных и подправление
bool correct_name_for_cin_file(string& name, string &operation) {
	return (name == "input.txt" && operation == "cin") ||
		(name == "output.txt" && operation == "cout");
}


// 3. вывод матрицы в файл
// 9. печать матрицы после преобразования в файл
void cout_to_file(double**& matrix) {
	cout << "Введите имя файла: ";
	string operation = "cout";
	string name_of_file;
	cin >> name_of_file;

	bool flag = correct_name_for_cin_file(name_of_file, operation);
	while (flag != true) {
		cout << "Попробуйте еще раз: ";
		cin >> name_of_file;
		flag = correct_name_for_cin_file(name_of_file, operation);
	}

	ofstream output(name_of_file);
	
	double tmp{ 0.0 };
	for (int i = 0; i < order; i++) {
		for (int j = 0; j < order; j++) {
			tmp = matrix[i][j];
			output << tmp << " ";
			}
		output << endl;
		}
	
	output.close();
	cout << "Матрица была введена.\n" << endl;
}

// 5. ввод матрицы из файла
void cin_to_file(double** &matrix) {
	cout << "Введите имя файла: ";

	string operation = "cin";
	string name_of_file;
	cin >> name_of_file;

	bool flag = correct_name_for_cin_file(name_of_file, operation);
	while (flag != true) {
		cout << "Попробуйте еще раз: ";
		cin >> name_of_file;
		flag = correct_name_for_cin_file(name_of_file, operation);
	}

	ifstream input(name_of_file);

	for (int i = 0; i < order; i++) {
		for (int j = 0; j < order; j++) {
			input >> matrix[i][j];
		}
	}
	
	input.close();
	cout << "Матрица была записана.\n" << endl;
}


// 6. вычисление характеристики
/* Наибольший элемент матрицы расположен ниже побочной диагонали.

	1 2 3
	4 5 6
	7 8 9

	Главная диагональ: 1 - 5 - 9
	Побочная диагональ: 7 - 5 - 3

	Наибольший элемент матрицы, 9, расположен ниже побочной диагонали
 */

// Поиск максимального элемента в матрице (его координат)
pair<int, int> max_elem(double**& matrix) {
	pair<int, int> result = { 0, 0 };
	double max_elem = 0.0;

	for (int i = 0; i < order; i++) {
		for (int j = 0; j < order; j++) {
			if (max_elem <= matrix[i][j]) {
				max_elem = matrix[i][j];
				result = { i, j };
			}
		}
	}
	
	cout << "Максимальный элемент матрицы: " << max_elem << endl;
	cout << "Позиция в матрице [" << result.first << "][" << result.second << "]." << endl;
	return result;
}

// Проверка находится ли макс. элемент под побочной диагональю
void max_elem_inder_diagonal(double**& matrix) {
	pair<int, int>coordinates = max_elem(matrix);

	if (coordinates.first + coordinates.second > order - 1) {
		cout << "Максимальный элемент под побочной диагональю." << endl;
	}
	else {
		cout << "Максимальный элемент не под побочной диагональю." << endl;
	}
}


// 4. ввод матрицы на экран,
void cin_to_console_matrix(double**& matrix) {
	cout << "Введите элементы матрицы." << endl;
	for (int i = 0; i < order; i++) {
		for (int j = 0; j < order; j++) {
			cin >> matrix[i][j];
		}
	}
	cout << endl;
}

// 1. генерация случайной матрицы
void random_matrix(double**& matrix) {
	int start = 0;           // Начало диапазона
	int end = 100;           // Конец диапазона


	for (int i = 0; i < order; i++) {
		for (int j = 0; j < order; j++) {
			matrix[i][j] = rand() % 100 * 1.0;
		}
	}

	cout << "Разработка матрицы, заполненной случайными значениями." << endl;
	cout << "Порядок матрицы: " << order << endl;
	cout << "'Случайная' матрица:" << endl;
	cout_to_console_matrix(matrix);
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

	double** matrix;
	matrix = new double* [order];
	for (int i = 0; i < order; i++) {
		matrix[i] = new double[order];
	}
	create_unit_matrix(matrix);

	bool flag = true;
	int problem;

	start();

	while (flag) {
		std::cin >> problem;
		switch (problem)
		{
		case(0):
			start();
			break;

		case(1):
			random_matrix(matrix);
			break;

		case(2):
			cout_to_console_matrix(matrix);
			break;

		case(3):
			cout_to_file(matrix);
			break;

		case(4):
			cin_to_console_matrix(matrix);
			break;

		case(5):
			cin_to_file(matrix);
			break;
		case(6):
			max_elem_inder_diagonal(matrix);
			break;

		case(7):
			operation_with_matrix(matrix);
			break;

		case(8):
			cout_to_console_matrix(matrix);
			break;

		case(9):
			cout_to_file(matrix);
			break;

		case(10):
			for (int i = 0; i < order; i++) {
				delete[] matrix[i];
			}
			delete[] matrix;
			return 0;
		default:
			start();
			break;
		}
	}

}
