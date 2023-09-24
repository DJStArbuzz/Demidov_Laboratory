#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

using namespace std;
int main()
{
	setlocale(LC_ALL, "Russian");
	/* Задание 1, вариант 9
		Необходимо вычислить два выражения A и B, зависящих
		от переменных, который вводить пользователь.
		Цель - вывести оба выражения и их разность с точностью 
		в 0,000001.
	*/
	cout << "Задание №1" << endl;

	double pi = 3.1415926535;
	// Число pi = 3.14159...
	
	cout << "Введите градус: ";
	double alpha;
	cin >> alpha;

	bool flag = alpha != 90 ? true : false;
	alpha = alpha * pi / 180;
	// Вводимое пользователем переменная
	
	double b = pow(2, 0.5) * sin(alpha / 2) / sin(pi / 4 - alpha / 2);
	cout << "Выражение B = " << fixed << setprecision(6) << b << endl;
	
	if (flag) {
		double a = tan(alpha) + pow(cos(alpha), -1) - 1;
		cout << "Выражение A = " << fixed << setprecision(6) << a << endl;
		cout << "Разность выражений A и B = " << fixed << setprecision(6) << a - b << "\n\n";
	}
	else {
		cout << "Тангенс 90 градусов не определен." << endl;
		cout << "Поиск разности невозможен\n\n";
	}

	/* Задание 2, вариант 9
		Необходимо решить уравнение, аккуратно рассмотреть все возможные принципиально 
		разные варианты значений коэффициентов. Коэффициенты: a; b; c; d; e;
		f; r вводятся с клавиатуры и являются действительными числами. Вывести ответ
		необходимо в виде чисел с фиксированной точкой (точность 0,000001).
	*/

	cout << "Задание №2" << endl;

	cout << "Введите a и b: ";
	double a_2, b_2;
	cin >> a_2 >> b_2;
	
	if ((a_2 == 0 && b_2 != 1) || b_2 <= 0) {
		cout << "Нет решений." << endl;
	}
	else if (a_2 == 0 && b_2 == 1){
		cout << "Бесконечное количество решений.";
	}
	else {
		double x1 = pow(b_2, -1.0 / a_2);
		double x2 = -1.0 * pow(b_2, -1.0 / a_2);
		cout << "Решения: " << x1 << " и " << x2 << ".\n\n";
	}
}	
