#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <set>
#include <iomanip>

const double PI = acos(-1.0);

using namespace std;

void problem_1() {
	/* Задание 1, вариант 9
		Необходимо вычислить два выражения A и B, зависящих
		от переменных, который вводить пользователь.
		Цель - вывести оба выражения и их разность с точностью
		в 0,000001.
	*/
	cout << "Задание №1" << endl;

	// Число pi = 3.14159...

	cout << "Введите градус: ";
	double alpha;
	cin >> alpha;

	bool flag = alpha != 90 ? true : false;
	bool flag2 = sin(PI / 4 - alpha / 2) != 0 ? true : false;

	double a, b;

	alpha = alpha * PI / 180;
	// Вводимое пользователем переменная

	if (flag) {
		a = tan(alpha) + pow(cos(alpha), -1) - 1;
		cout << "Выражение A = " << fixed << setprecision(6) << a << endl;
	}
	else {
		cout << "Тангенс 90 градусов не определен." << endl;
	}

	if (flag2) {
		b = pow(2, 0.5) * sin(alpha / 2) / sin(PI / 4 - alpha / 2);
		cout << "Выражение B = " << fixed << setprecision(6) << b << endl;
	}
	else {
		cout << "Деление на 0\n";
	}

	if (flag && flag2) {
		a = tan(alpha) + pow(cos(alpha), -1) - 1;
		b = pow(2, 0.5) * sin(alpha / 2) / sin(PI / 4 - alpha / 2);
		cout << "Разность выражений A и B = " << fixed << setprecision(6) << a - b << "\n";
	}
	else {
		cout << "Поиск разности невозможен\n";
	}
	cout << endl;
}

void problem_2() {

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
	else if (a_2 == 0 && b_2 == 1) {
		cout << "Бесконечное количество решений.";
	}
	else {
		double x1 = pow(b_2, -1.0 / a_2);
		double x2 = -1.0 * pow(b_2, -1.0 / a_2);
		cout << "Решения: " << x1 << " и " << x2 << ".\n";
	}
	cout << endl;
}

void problem_3() {
	/*
		Задание 3, вариант 8.
		Числовой ребус USA + USSR = PEACE.
		P и U не могут быть равны 0.
		P = 1.
	*/

	int P = 10000;

	cout << "Возможные варианты решения ребуса:\n";

	for (int U = 9; U > 1; U--) {
		for (int S = 0; S < 10; S++) {
			for (int R = 0; R < 10; R++) {
				for (int A = 0; A < 10; A++) {
					for (int C = 0; C < 10; C++) {
						for (int E = 0; E < 10; E++) {
							vector<int> sp = { P, U, S, R, A, C, E };
							set<int> sp2 = { P, U, S, R, A, C, E };
							if (sp.size() == sp2.size()) {
								int USA = U * 100 + S * 10 + A;
								int USSR = U * 1000 + S * 100 + S * 10 + R;
								int PEACE = P + E * 1000 + A * 100 + C * 10 + E;
								if (USA + USSR == PEACE) {
									cout << USA << " + " << USSR << " = " << PEACE << endl;
									break;
								}
							}
						}
					}
				}
			}
		}
	}

	cout << endl;
}

void problem_4() {
	/*
		Задание 4, вариант 4
		Необходимо проверить принадлежность точки 
		закрашенной области на плоскости.
		Начало координат - левый нижний угол картинки.
	*/
	
	cout << "Первая точка (любые вещественные координаты): " << endl;
	double x1, y1;
	cin >> x1 >> y1;
	if (x1 >= 0 && y1 >= 0) {
		cout << "Точка не принадлежит закрашенной области.";
	}
	else {
		if (pow(x1, 2) + pow(y1, 2) > 1 && abs(x1 + y1) + abs(y1 - x1) <= 2) {
			cout << "Точка принадлежит закрашенной области.";
		}
		else {
			cout << "Точка не принадлежит закрашенной области.";
		}
	}

	cout << "Вторая точка (любые неотрицательные координаты): " << endl;
	double x2, y2;
	cin >> x2 >> y2;

	if (x2 < 0 || y2 < 0) {
		cout << "Точка не принадлежит закрашенной области.";
	}
	else {

	}
	cout << endl;


}

void problem_5() {
	/*
	Задание 5, вариант 5.
	Необходимо вычислить логическое выражение.
	A = ((x + y) ↔ z) | xyz,
	B = xyz ⊕ 1.
	*/
	cout << "X Y Z A B\n";

	int A, B;
	
	for (int x = 0; x < 2; x++) {
		for (int y = 0; y < 2; y++) {
			for (int z = 0; z < 2; z++) {
				A = !(x) || !(y) || !(z);
				B = !(x && y && z);
				cout << x << " " << y << " " << z << " " << A << " " << B << endl;
			}
		}
	}
	cout << endl;

}

void problem_6() {
	/*
	Задание 6, вариант 1.
	Необходимо придумать алгоритм и решить задачу, не используя цикла и условия.
	Даны натуральные числа n, a1, . . . , an. Определите количество членов ai после-
довательности a1, . . . , an, являющихся квадратами четных чисел.
	*/
	int n;
	cin >> n;
	cout << "Количество членов последовательности, являющихся квадратом четных чисел";

	cout << endl;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	
	bool flag = true;
	int problem;
	while (flag) {
		cin >> problem;
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
			return 0;
			break;
		default:
			problem_1();
			break;
		}
	}

}	
