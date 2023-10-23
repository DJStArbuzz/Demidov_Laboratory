#include <iostream>
#include <stdio.h>


using namespace std;

void positive_array(int array[101], int n) {
	for (int i = 0; i < n; i++) {
		if (array[i] >= 0) {
			cout << array[i] << " ";
		}
	}
}

void negative_array(int array[101], int n) {
	for (int i = 0; i < n; i++) {
		if (array[i] < 0) {
			cout << array[i] << " ";
		}
	}
}

void problem_1() {
	/* Задание 1, вариант 14
	Решить задачу на обработку одномерного статического массива.
	Требуется ввести с клавиатуры размерность массива n (n ≤ 100), 
	далее в цикле ввести элементы массива. 
	Полученный ответ вывести на экран.
	*/
	
	cout << "Задание 1\n";
	cout << "Введите n, потом элементы статистического массива.\n\n";

	int n, tmp;
	cin >> n;

	int array[101];
	for (int i = 0; i < n; i++) {
		cin >> array[i];
	}

	cout << "\nМассив был изменен.\n";
	cout << "Сначала неотрицательные члены, потом отрицательные\n";
	cout << "Тот же порядок.\n\n";
	
	positive_array(array, n);
	negative_array(array, n);

	cout << endl << endl;
}

void problem_2() {
	/* Задание 2, вариант 9
	Дано целое число K (> 0) и целочисленный массив размера N. 
	Поменять местами последнюю серию массива и его серию с номером K. 
	Если серий в массиве меньше K, то вывести массив без изменений.
	*/

	cout << "Задание 2\n";
	cout << "Введите n и k, потом элементы динамического массива.\n";

	int n, k;
	cin >> n >> k;

	int* array_1 = new int[n];
	int* array_2 = new int[n];
	for (int i = 0; i < n; i++) {
		cin >> array_1[i];
	}

	int count = 1;
	for (int i = 0; i < n - 1; i++) {
		if (array_1[i] != array_1[i + 1]) {
			count++;
		}
	}

	cout << "Серия массива равна: " << count << endl;
	cout << "Вывод динамического массива\n";

	if (count < k) {
		for (int i = 0; i < n; i++) {
			cout << array_1[i] << " ";
		}
	}
	else {
		int nk = 1;
		int beginKSeries = 1;
		int lenKSeries = (k == 1 ? 1 : 0);
		int beginEndSeries;

		for (int i = 1; i < n; ++i) {
			if (array_1[i - 1] != array_1[i]) {
				nk++;
				if (nk == k) beginKSeries = i;
				beginEndSeries = i;
			}
			if (nk == k) lenKSeries++;
		}

		int index = -1;
		for (int i = 0; i < beginKSeries; ++i)
		{
			index++;
			array_2[index] = array_1[i];
		}

		for (int i = beginEndSeries; i < n; ++i)
		{
			index++;
			array_2[index] = array_1[i];
		}

		for (int i = beginKSeries + lenKSeries; i < beginEndSeries; ++i)
		{
			index++;
			array_2[index] = array_1[i];
		}

		for (int i = beginKSeries; i < beginKSeries + lenKSeries; ++i)
		{
			index++;
			array_2[index] = array_1[i];
		}

		for (int i = 0; i < n; ++i)
		{
			array_1[i] = array_2[i];
		}

		for (int i = 0; i < n; ++i) {
			cout << array_1[i] << " ";
		}

	}

	delete[] array_1, array_2;

	cout << endl << endl;
}

void problem_3() {
	/* Задание 3, вариант 8
	В целочисленном массиве Х(N) определить: максимальный элемент среди
	положительных нечетных элементов, минимальный среди положительных 
	четных элементов, первые два совершенных числа. Удалить найденные элементы.
	Процедуру повторить еще раз. В программе написать методы: удаления 
	элемента, определения максимального и минимального элементов согласно заданию,
	проверки условия — число совершенное.*/

	int n;
	cin >> n;

	int* array_1 = new int[n];
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
		default:
			problem_1();
			break;
		}
	}
}
