#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std;

// Процедура вывода массива в консоль
void cout_for_array(int* &array, int n) { 
	for (int i = 0; i < n; i++) {
		cout << array[i] << " ";
	}
}

// Процедура поиска среднего арифметического
int search_arithmetic_mean(int*& array, int n) {
	int arith_mean = 0; // Переменная для будущего ариф. среднего

	for (int i = 0; i < n; i++) {
		arith_mean += array[i];
	}

	return arith_mean / n;
}

// Процедура составления массива, в котором элементы больше ср значения из Х
int array_more_arith_mean(int*& arrayOrig, int*& arrayRes, int n, int am) {
	int tmp = 0; // Дополнительная переменная
	for (int i = 0; i < n; i++) {
		if (arrayOrig[i] >= am) {
			// am - среднее арифметическое
			arrayRes[tmp] = arrayOrig[i];
			tmp++;
		}
	}

	return tmp;
}

// Процедура поиска совершенного числа
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

// Процедура составления массива, в котором элементы - совершенные числа
int perfect_array(int*& arrayOrig, int*& arrayRes, int n) {
	int tmp = 0; // Дополнительная переменная
	for (int i = 0; i < n; i++) {
		if (perfect_search(arrayOrig[i]))
		{
			arrayRes[tmp] = arrayOrig[i];
			tmp++;
		}
	}

	return tmp;
}

bool prime_search(int n) {
	for (int i = 2; i <= sqrt(n); i++) {
		if (n % i == 0) {
			return false;
		}
	}
	return true;
}

// Процедура удаления не простых элементов
int delete_elem(int*& arrayOrig, int*& arrayRes, int n) {
	int tmp = 0; // Дополнительная переменная
	for (int i = 0; i < n; i++) {
		if (prime_search(arrayOrig[i]))
		{
			arrayRes[tmp] = arrayOrig[i];
			tmp++;
		}
	}

	return tmp;

}

// Процедура вывода массива в файл
void cout_to_file(int*& array, int n) {
	ofstream output("output.txt");
	int tmp{ 0 };

	output << "Массив: ";
	for (int i = 0; i < n; i++) {
		tmp = array[i];
		output << tmp << " ";
	}
	output << endl;
	output.close();
}

int main() {
	setlocale(LC_ALL, "Russian");
	/* Задание 3, вариант 2
	Из целочисленного массива Х(N) записать в массив Y(K) все элементы, 
	превышающие среднее арифметическое значение всех элементов массива Х. 
	Записать в массив Z(M) все элементы массива Х, являющиеся совершенными 
	числами. Удалить в массивах все элементы, не являющиеся простыми числами. 
	В программе написать методы: проверки числа на совершенность (совершенным
	называется число, равное сумме всех своих делителей, меньших его самого),
	формирования массивов Y и Z, определения среднего арифметического 
	элементов, удаления элемента.
	*/

	int n;       // Размер массива X
	int k;       // Размер массива Y
	int m;       // Размер массива Z

	int* arrayX; // Изначальный массив X
	int* arrayY; // Массив Y, в котором элементы превышают ср. значение массива Х
	int* arrayZ; // Массив Z, в котором - совершенные числа 

	cout << "Введите количество элементов: ";
	cin >> n;
	
	cout << "Введите элементы массива Х: ";
	arrayX = new int[n];
	for (int i = 0; i < n; i++) {
		cin >> arrayX[i];
	}

	int arithmetic_mean = search_arithmetic_mean(arrayX, n);


	cout << "\nЭлементы массива Y: ";
	arrayY = new int[n];
	k = array_more_arith_mean(arrayX, arrayY, n, arithmetic_mean);
	cout_for_array(arrayY, k);

	cout << "\nЭлементы массива Z: ";
	arrayZ = new int[n];
	m = perfect_array(arrayX, arrayZ, n);
	cout_for_array(arrayZ, m);

	int* arrayXnew = new int[n]; // Массив X только с простыми числами
	int* arrayYnew = new int[k]; // Массив Y только с простыми числами
	int* arrayZnew = new int[m]; // Массив Z только с простыми числами

	int newX = delete_elem(arrayX, arrayXnew, n);
	int newY = delete_elem(arrayY, arrayYnew, k);
	int newZ = delete_elem(arrayZ, arrayZnew, m);

	cout << "\nЭлементы нового массива X: ";
	cout_for_array(arrayXnew, newX);

	cout << "\nЭлементы нового массива Y: ";
	cout_for_array(arrayYnew, newY);

	cout << "\nЭлементы нового массива Z: ";
	cout_for_array(arrayZnew, newZ);

	cout << endl;

	cout << "Вывод в файл осуществлен" << endl;
	cout_to_file(arrayXnew, newX);


}
