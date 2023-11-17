#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <set>
#include <iomanip>

using namespace std;

void generate_Per_Alp(string &Alp, string &Eq_Alp, int n) {
	vector<int> Mark(n);
	Eq_Alp = Alp;
	int u;
	for (int i = 0; i < n; i++) {
		u = rand() % n;
		
		while (Mark[u] == 1) {
			u = rand() % n;
		}

		Mark[u] = 1;
		Eq_Alp[i] = Alp[u];
	}
}

void generate_Per_Alp2(string& Alp, string& Eq_Alp, int n) {
	long long num = (rand() * rand() + rand());
	vector<int> Mark(n);

	Eq_Alp = Alp;
	int count;
	int u;

	for (int i = 0; i < u; i++) {
		int x = num % (n - i);
		count = 0;

		for (int j = 0; j < n; j++) {
			if (Mark[j] == 0) {
				if (count == x) {
					u = j;
					break;
				}
				count++;
			}
		}
		Mark[u] = 1;
		Eq_Alp[i] = Alp[u];
	}
}

void menu() {
	cout << "1. Работа с файлом" << endl;
	cout << "2. Работа с клавиатурой" << endl;
	cout << "3. Характеристика" << endl;
	cout << "4. Вывод в файл" << endl;
}

void work() {
	int n;
	cin >> n;
	while (n != 0) {
		switch (n)
		{
		case(1):
			break;

		case(2):
			break;

		default:
			break;
		}
	}
}

int main()
{

}
