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

// Процедура редактирования массива
void editing_array(int* arrayA, int* arrayB, int n) {
	for (int i = 0; i < n; i++) {
		// если ai > 0, то bi увеличить в 10 раз,
		// иначе bi заменить нулем.
		if (arrayA[i] > 0) {
			arrayB[i] *= 10;
		}
		else {
			arrayB[i] = 0;
		}
	}
}

int main() {
	setlocale(LC_ALL, "Russian");
	/* Задание 1, вариант 17
	Даны натуральное n, целые числа a1, . . . , an и b1, . . . , bn.
	Преобразовать последовательность bn по правилу:
	если ai > 0, то bi увеличить в 10 раз,
	иначе bi заменить нулем.
	
	A:  1 2 -2 -3 2
	B:  10 2 3 2 1
	B:  100 20 0 0 10
	*/

	int n;           // Количество элементов
	int arrayA[100]; // Массив А, по которому будут преобразовывать массив B
	int arrayB[100]; // Массив B, редактируемый по массиву А

	cout << "Введите количество элементов в массивах А и Б: ";
	cin >> n;

	cout << "Введите элементы массива А: ";
	cin_for_array(arrayA, n);

	cout << "Введите элементы массива B: ";
	cin_for_array(arrayB, n);

	cout << "\nМассив B до редактирования:\n";
	cout_for_array(arrayB, n);

	cout << "\nМассив B после редактирования:\n";
	editing_array(arrayA, arrayB, n);
	cout_for_array(arrayB, n);


}
