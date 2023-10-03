#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <set>
#include <iomanip>

const double PI = acos(-1.0);


void problem_1() {
	/* Задание 1, вариант 9
		Необходимо вычислить два выражения A и B, зависящих
		от переменных, который вводить пользователь.
		Цель - вывести оба выражения и их разность с точностью
		в 0,000001.
	*/
	std::cout << "Задание №1" << std::endl;

	// Число pi = 3.14159...

	std::cout << "Введите градус: ";
	double alpha;
	std::cin >> alpha;

	bool flag = (alpha != 90) && (alpha != 270) ? true : false;
	alpha = alpha * PI / 180;
	bool flag2 = sin(PI / 4 - alpha / 2) != 0 ? true : false;

	double a, b;

	// Вводимое пользователем переменная

	if (flag) {
		a = tan(alpha) + pow(cos(alpha), -1) - 1;
		std::cout << "Выражение A = " << std::fixed << std::setprecision(6) << a << std::endl;
	}
	else {
		std::cout << "Тангенс 90 градусов не определен." << std::endl;
	}

	if (flag2) {
		b = pow(2, 0.5) * sin(alpha / 2) / sin(PI / 4 - alpha / 2);
		std::cout << "Выражение B = " << std::fixed << std::setprecision(6) << b << std::endl;
	}
	else {
		std::cout << "Деление на 0\n";
	}

	if (flag && flag2) {
		a = tan(alpha) + pow(cos(alpha), -1) - 1;
		b = pow(2, 0.5) * sin(alpha / 2) / sin(PI / 4 - alpha / 2);
		std::cout << "Разность выражений A и B = " << std::fixed << std::setprecision(6) << a - b << "\n";
	}
	else {
		std::cout << "Поиск разности невозможен\n";
	}
	std::cout << std::endl;
}

void problem_2() {

	/* Задание 2, вариант 9
		Необходимо решить уравнение, аккуратно рассмотреть все возможные принципиально
		разные варианты значений коэффициентов. Коэффициенты: a; b; c; d; e;
		f; r вводятся с клавиатуры и являются действительными числами. Вывести ответ
		необходимо в виде чисел с фиксированной точкой (точность 0,000001).
	*/

	std::cout << "Задание №2" << std::endl;

	std::cout << "Введите a и b: ";
	double a_2, b_2;
	std::cin >> a_2 >> b_2;

	if ((a_2 == 0 && b_2 != 1) || b_2 <= 0) {
		std::cout << "Нет решений." << std::endl;
	}
	else if (a_2 == 0 && b_2 == 1) {
		std::cout << "Бесконечное количество решений.";
	}
	else {
		double x1 = pow(b_2, -1.0 / a_2);
		double x2 = -1.0 * pow(b_2, -1.0 / a_2);
		std::cout << "Решения: " << x1 << " и " << x2 << ".\n";
	}
	std::cout << std::endl;
}

void problem_3() {
	/*
		Задание 3, вариант 8.
		Числовой ребус USA + USSR = PEACE.
		P и U не могут быть равны 0.
		P = 1.
	*/

	int P = 10000;

	std::cout << "Возможные варианты решения ребуса:\n";
	std::cout << "USA + USSR + PEACE\n";
	
	for (int U = 9; U > 1; --U) {
		for (int S = 0; S < 10; S++) {
			for (int R = 0; R < 10; R++) {
				for (int A = 0; A < 10; A++) {
					for (int C = 0; C < 10; C++) {
						for (int E = 0; E < 10; E++) {
							std::vector<int> sp = { P, U, S, R, A, C, E };
							std::set<int> sp2 = { P, U, S, R, A, C, E };
							if (sp.size() == sp2.size()) {
								int USA = U * 100 + S * 10 + A;
								int USSR = U * 1000 + S * 100 + S * 10 + R;
								int PEACE = P + E * 1000 + A * 100 + C * 10 + E;
								if (USA + USSR == PEACE) {
									std::cout << USA << " + " << USSR << " = " << PEACE << std::endl;
									break;
								}
							}
						}
					}
				}
			}
		}
	}

	std::cout << std::endl;
}

void problem_4() {
	/*
		Задание 4, вариант 4
		Необходимо проверить принадлежность точки 
		закрашенной области на плоскости.
		Начало координат - левый нижний угол картинки.
	*/
	
	std::cout << "Первая точка (любые вещественные координаты): " << std::endl;
	double x1, y1;
	std::cin >> x1 >> y1;
	if (x1 >= 0 && y1 >= 0) {
		std::cout << "Точка не принадлежит закрашенной области.";
	}
	else {
		if (pow(x1, 2) + pow(y1, 2) > 1 && abs(x1 + y1) + abs(y1 - x1) <= 2) {
			std::cout << "Точка принадлежит закрашенной области.";
		}
		else {
			std::cout << "Точка не принадлежит закрашенной области.";
		}
	}

	std::cout << "\nВторая точка (любые неотрицательные координаты): " << std::endl;
	double x2, y2;
	std::cin >> x2 >> y2;

	if (x2 < 0 || y2 < 0) {
		std::cout << "Точка не принадлежит закрашенной области.";
	}
	else {
		if ((int(x2) % 3 == 0 && int(y2) % 3 == 0)
			|| (int(x2) % 3 == 0 && int(y2) % 3 != 0) || 
			(int(x2) % 3 != 0 && int(y2) % 3 == 0))  {
			std::cout << "Точка принадлежит закрашенной области.";
		}
		else {
			std::cout << "Точка не принадлежит закрашенной области.";
		}
	}
	std::cout << std::endl;


}

void problem_5() {
	/*
	Задание 5, вариант 5.
	Необходимо вычислить логическое выражение.
	A = ((x + y) ↔ z) | xyz,
	B = xyz ⊕ 1.
	*/
	std::cout << "X Y Z A B\n";

	int A, B;
	
	for (int x = 0; x < 2; x++) {
		for (int y = 0; y < 2; y++) {
			for (int z = 0; z < 2; z++) {
				A = !(x) || !(y) || !(z);
				B = !(x && y && z);
				std::cout << x << " " << y << " " << z << " " << A << " " << B << std::endl;
			}
		}
	}
	std::cout << std::endl;

}

void problem_6() {
	/*
	Задание 6, вариант 1.
	Необходимо придумать алгоритм и решить задачу, не используя цикла и условия.
	Даны натуральные числа n, a1, . . . , an. Определите количество членов ai 
	последовательности a1, . . . , an, являющихся квадратами четных чисел.
	*/
	int n;
	std::cin >> n;
	int k = 0;
	for (int i = 1; i * i <= n; i++) {
		if (i % 2 == 0) {
			k++;
		}
	}
	std::cout << "Количество членов последовательности, являющихся квадратом четных чисел " << k << std::endl;
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
