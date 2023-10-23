#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <set>
#include <iomanip>

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
	/* Задание 1
	Решить задачу на обработку одномерного статического массива.
Требуется ввести с клавиатуры размерность массива n (n ≤ 100), далее в цикле вве-
сти элементы массива. Полученный ответ вывести на экран.
	*/
	
	cout << "Задание 1\n";
	cout << "Введите n, потом элементы массива.\n";

	int n, tmp;
	cin >> n;

	int array[101];
	for (int i = 0; i < n; i++) {
		cin >> array[i];
	}

	cout << "Массив был изменен.\n";
	cout << "Сначала неотрицательные члены, потом отрицательные\n";
	cout << "Тот же порядок.\n";
	
	positive_array(array, n);
	negative_array(array, n);

	cout << endl << endl;
}

void problem_2() {

}

void problem_3() {
	
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
