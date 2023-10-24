#include <iostream>
#include <cmath>
#include <set>
#include <algorithm>


void positive_array(int array[101], int n) {
	for (int i = 0; i < n; i++) {
		if (array[i] >= 0) {
			std::cout << array[i] << " ";
		}
	}
}

void negative_array(int array[101], int n) {
	for (int i = 0; i < n; i++) {
		if (array[i] < 0) {
			std::cout << array[i] << " ";
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
	
	std::cout << "Задание 1\n";
	std::cout << "Введите n, потом элементы статистического массива.\n\n";

	int n;
	std::cin >> n;

	int array[101];
	for (int i = 0; i < n; ++i) {
		std::cin >> array[i];
	}

	std::cout << "\nМассив был изменен.\n";
	std::cout << "Сначала неотрицательные члены, потом отрицательные\n";
	std::cout << "Тот же порядок.\n\n";
	
	positive_array(array, n);
	negative_array(array, n);

	std::cout << std::endl << std::endl;
}

void problem_2() {
	/* Задание 2, вариант 9
	Дано целое число K (> 0) и целочисленный массив размера N. 
	Поменять местами последнюю серию массива и его серию с номером K. 
	Если серий в массиве меньше K, то вывести массив без изменений.
	*/

	std::cout << "Задание 2\n";
	std::cout << "Введите n и k, потом элементы динамического массива.\n\n";

	int n, k;
	std::cin >> n >> k;

	int* array_1 = new int[n];
	int* array_res = new int[n];
	for (int i = 0; i < n; ++i) {
		std::cin >> array_1[i];
	}

	int count = 1;
	for (int i = 0; i < n - 1; ++i) {
		if (array_1[i] != array_1[i + 1]) {
			count++;
		}
	}

	std::cout << "\nСерия массива равна: " << count << std::endl;
	std::cout << "Вывод динамического массива\n\n";

	if (count < k) {
		for (int i = 0; i < n; i++) {
			std::cout << array_1[i] << " ";
		}
	}
	else {
		int tmp = 1;
		int indKSeries = 1; // индекс начала серии К
		int indFSeries = 1; // индекс начала последней серии
		int lenKSeries = (k == 1 ? 1 : 0); // длина серии К

		for (int i = 1; i < n; ++i) {
			if (array_1[i - 1] != array_1[i]) {
				tmp++;
				if (k == tmp)
				{
					indKSeries = i;
				}
				indFSeries = i;
			}
			if (k == tmp)
			{
				lenKSeries++;
			}
		}

		int index = -1;
		for (int i = 0; i < indKSeries; ++i)
		{
			index++;
			array_res[index] = array_1[i];
		}

		for (int i = indFSeries; i < n; ++i)
		{
			index++;
			array_res[index] = array_1[i];
		}

		for (int i = indKSeries + lenKSeries; i < indFSeries; ++i)
		{
			index++;
			array_res[index] = array_1[i];
		}

		for (int i = indKSeries; i < indKSeries + lenKSeries; ++i)
		{
			index++;
			array_res[index] = array_1[i];
		}

		for (int i = 0; i < n; ++i) {
			std::cout << array_res[i] << " ";
		}

		std::cout << "\n\n";

	}

	delete[] array_1, array_res;

	std::cout << std::endl << std::endl;
}

bool perfect_search(int n) {
	/*	Совершенное число - число, которое равно сумме всех своих делителей
		(без самого же себя)
		Пример: 6 = 1 + 2 + 3
		28 = 1 + 2 + 4 + 7 + 14
	*/

	int sum = (-1) * n;
	for (int i = 1; i * i <= n; i++) {
		if (n % i == 0) {
			sum += i;
			if (i * i != n) {
				sum += (n / i);
			}
		}
	}

	return sum == n;
}

int perfect_search_res(int* array3, int n, int begin) {
	bool flag;

	for (int i = begin; i < n; i++) {
		flag = perfect_search(array3[i]);
		if (flag) 
		{
			return i;
		}
	}
	return -1;
}

int max_positive_odd_n_search(int* array3, int n) {
	int res = -1;
	int maximum = -1;
	
	for (int i = 0; i < n; i++) {
		if (array3[i] > 0 && array3[i] % 2 == 1 && array3[i] > maximum) {
			maximum = array3[i];
			res = i;
		}
	}

	return res;
}

int min_positive_n_search(int* array3, int n) {
	int res = -1;
	int minimum = 10000000;

	for (int i = 0; i < n; i++) {
		if (array3[i] > 0 && array3[i] < minimum) {
			minimum = array3[i];
			res = i;
		}
	}

	return res;
}

int delete_elem(int* &array, int index, int size) {
	for (int i = index; i < size - 1; i++) {
		array[i] = array[i + 1];
	}

	return size - 1;
}

void problem_3() {
	/* Задание 3, вариант 8
	В целочисленном массиве Х(N) определить: максимальный элемент среди
	положительных нечетных элементов, минимальный среди положительных 
	четных элементов, первые два совершенных числа. Удалить найденные элементы.
	Процедуру повторить еще раз. В программе написать методы: удаления 
	элемента, определения максимального и минимального элементов согласно заданию,
	проверки условия — число совершенное.*/

	std::cout << "Задание 3\n";
	std::cout << "Введите n, потом элементы динамического массива.\n\n";

	int n;
	std::cin >> n;

	int* array3 = new int[n];
	for (int i = 0; i < n; i++) {
		std::cin >> array3[i];
	}

	int firstPerfectN = -1;   // Первое совершенное число
	int secondPerfectN = -1;  // Второе совершенное число
	int maxPositiveOddN = - 1; // Максимальное среди положительных нечетных элементов
	int minPositiveN = -1;    // Минимальный среди положительных элементов
	
	for (int i = 0; i < 2; i++) {
		firstPerfectN = perfect_search_res(array3, n, 0);
		
		if (firstPerfectN != -1) {
			secondPerfectN = perfect_search_res(array3, n, firstPerfectN + 1);
		}

		maxPositiveOddN = max_positive_odd_n_search(array3, n);

		minPositiveN = min_positive_n_search(array3, n);
	
		std::set<int> deleteElem = { maxPositiveOddN, minPositiveN, firstPerfectN, secondPerfectN };
		deleteElem.erase(-1);

		std::cout << std::endl;

		int k = deleteElem.size();

		for (int i = 0; i < k; i++) {
			std::set<int>::iterator it = deleteElem.begin();
			std::advance(it, i);
			int element = *it;

			n = delete_elem(array3, element - i, n);
		}

		std::cout << "Удаление массивов:\n";

		for (int i = 0; i < n; i++) {
			std::cout << array3[i] << " ";
		}

		std::cout << "\n\n";

	}

	delete[] array3;

	std::cout << std::endl;
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
