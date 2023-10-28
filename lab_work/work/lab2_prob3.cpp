#include <iostream>
#include <iomanip>

using namespace std;

// Процедура проверки числа на простоту
bool prime_elem(int elem) {
	/*
		 Простое число
		 Это число имеющее только 2 делителя (1 и само число).
		 у него нет обратного значения среди Целых чисел (т.е не отрицательное).
	*/
	if (elem == 1) {
		return true;
	}

	if (elem < 0) {
		return false;
	}

	for (int i = 2; i * i <= elem; i++) {
		if (elem % i == 0) {
			return false;
		}
	}
	return true;
}

// Процедура поиска среднего арифметического простых чисел из массива X
float find_arithmetic_mean_sum_X(int*& arrayX, int N) {
	double sum = 0.0;   // сумма простых элементов 
	double count = 0.0; // кол-во простых элементов

	for (int i = 0; i < N; i++) {
		if (prime_elem(arrayX[i])) {
			sum += arrayX[i];
			count++;
		}
	}

	// Если мы не нашли простые числа, то происходит деление на 0
	count = (count != 0) ? count : 1;
	return sum / count;
}

// Процедура поиска среднего арифметического простых чисел из массива Y
float find_arithmetic_mean_sum_Y(int*& arrayY, int N) {
	double sum = 0;   // сумма простых элементов 
	double count = 0; // кол-во простых элементов


	for (int i = 0; i < N; i++) {
		if (prime_elem(arrayY[i])) {
			sum += arrayY[i];
			count++;
		}
	}

	// Если мы не нашли простые числа, то происходит деление на 0
	count = (count != 0) ? count : 1;
	return sum / count;
}

// Процедура добавления положительных нечетных элементов из массива X в Y
int add_odd_n(int* &arrayX, int N, int* &arrayY, int* &arrayIndex) {
	int count = 0; //  Кол-во переданных элементов

	for (int i = 0; i < N; i++){
		if (arrayX[i] % 2 == 1 && arrayX[i] > 0) {
			arrayY[count] = arrayX[i]; // перенос элемента
			arrayIndex[count] = i;     // сохранение индекса переданного элемента
			count++;                   // счетчик + 1
		}
	}
	
	return count;
}

// Процедура по удалению положительных элементов из массива X
int delete_elem(int* arrayX, int index, int size) {
	for (int i = index; i < size - 1; i++) {
		arrayX[i] = arrayX[i + 1];
	}

	return size - 1;
}

int main() {
	setlocale(LC_ALL, "Russian");

	cout << "Введите n, потом элементы массива X размером n" << endl;


	int N;                        // Кол-во элементов в массиве
	cin >> N;
	int* arrayX = new int[N];     // Массив X размером N
	int* arrayY = new int[N];     // Массив Y
	int* arrayIndex = new int[N]; // Массив индексов убранных элементов из X

	for (int i = 0; i < N; i++) {
		cin >> arrayX[i];
	}

	int count = add_odd_n(arrayX, N, arrayY, arrayIndex);

	for (int i = 0; i < count; i++){
		N = delete_elem(arrayX, arrayIndex[i] - i, N);
	}
		
	cout << "Итоговый массив X:" << endl;
	for (int i = 0; i < N; i++){
		cout << arrayX[i] << " ";
	}

	cout << "\nМассив Y с нечетными положительными элементами (из массива X)" << endl;
	for (int i = 0; i < count; i++) {
		cout << arrayY[i] << " ";
	}

	float arithmeticMeanX = find_arithmetic_mean_sum_X(arrayX, N);
	float arithmeticMeanY = find_arithmetic_mean_sum_Y(arrayY, count);

	cout << "\nСреднее арифметическое простых элементов из массива X: " << fixed << setprecision(3) << arithmeticMeanX << endl;
	cout << "Среднее арифметическое простых элементов из массива Y: " << fixed << setprecision(3) << arithmeticMeanY << endl;


	delete arrayX, arrayY, arrayIndex;

}
