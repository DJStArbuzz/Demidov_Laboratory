#include <iostream>
#include <algorithm>

using namespace std;

// Процедура ввода массива в консоль
void cin_for_array(int* array, int n) {
	for (int i = 0; i < n; i++) {
		cin >> array[i];
	}
}

// Процедура вывода массива в консоль
void cout_for_array(int* array, int n) {
	for (int i = 0; i < n; i++) {
		cout << array[i] << " ";
	}
}

// Процедура добавления 0 перед каждой серии массива
void array_with_null(int* array, int n) {
	int* arrayRes; // Итоговый массив (0 перед каждой серий массива)
	arrayRes = new int[2 * n]; 
	int tmp = 1;   // Доп. переменная

	arrayRes[0] = 0;
	arrayRes[tmp] = array[0];

	for (int i = 1; i < n; i++) {
		tmp++;
		if (array[i - 1] != array[i]) {
			arrayRes[tmp] = 0;
			tmp++;
		}

		arrayRes[tmp] = array[i];
	}

	cout_for_array(arrayRes, tmp + 1);
}

int main() {
	setlocale(LC_ALL, "Russian");
	/* Задание 2, вариант 2
	Дан целочисленный массив размера N. 
	Вставить перед каждой его серией элемент с нулевым значением.
	1 2 2 3 -> 0 1 0 2 2 0 3
	*/
	int n;      // Количество элементов
	int* array; // Массив с сериями

	cout << "Введите количество элементов в массиве: ";
	cin >> n;

	cout << "Введите элементы массива: ";
	array = new int[n];
	cin_for_array(array, n);

	cout << "\nИтоговый массив: ";
	array_with_null(array, n);

}
