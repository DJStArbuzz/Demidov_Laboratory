#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <string>
#include <fstream>
#include <ctime>

using namespace std;

//  массив целых чисел
// мы хотим собрать сумму элементов с л по р
// max(x1,x2,x3,x4)

void write_file(string file_name, vector<int>&Arr, int n, int q, vector<pair<int, int>> &B)
{
	ofstream out(file_name);
	out << n << " " << q << "\n";
	for (int i = 0; i < n; i++) {
		out << Arr[i] << " ";
	}

	for (int i = 0; i < q; i++) {
		cout << B[i].first << " " << B[i].second << "\n";
	}
	out.close();
}

void generate_name_file(string& file_name, int num_test)
{
	if (num_test < 10)
	{
		file_name = "output/massiv/0";
		file_name = file_name + to_string(num_test);
		file_name = file_name + ".txt";
	}
	else
	{
		file_name = "output/massiv/";
		file_name = file_name + to_string(num_test);
		file_name = file_name + ".txt";
	}
}

int main()
{
	srand(time(0));
	for (int num_test = 1; num_test <= 99; num_test++)
	{
		string file_name = "";
		generate_name_file(file_name, num_test);
		
		int n, q;
		vector<int> A;
		vector<pair<int, int>> B;
		pair<int, int> tmp;
		int l, r;
		int a;

		if (num_test <= 20) {
			n = rand() % 10 + 1;
			q = rand() % 10 + 1;
			for (int i = 0; i < n; i++) {
				a = rand() % 100;
				A.push_back(a);
			}
			for (int i = 0; i < q; i++) {
				l = rand() % n + 1;
				r = rand() % n + 1;
				tmp.first = min(l, r);
				tmp.second = max(l, r);
				B.push_back(tmp);
			}
		}

		else if (num_test <= 80) {
			n = rand() % 10 + 1;
			q = rand() % 10 + 1;
			for (int i = 0; i < n; i++) {
				a = rand() % 100;
				A.push_back(a);
			}
			for (int i = 0; i < q; i++) {
				l = rand() % n + 1;
				r = rand() % n + 1;
				tmp.first = min(l, r);
				tmp.second = max(l, r);
				B.push_back(tmp);
			}
		}
		else {
			n = rand() % 10 + 1;
			q = rand() % 10 + 1;
			for (int i = 0; i < n; i++) {
				a = rand() % 100;
				A.push_back(a);
			}
			for (int i = 0; i < q; i++) {
				l = rand() % n + 1;
				r = rand() % n + 1;
				tmp.first = min(l, r);
				tmp.second = max(l, r);
				B.push_back(tmp);
			}
		}
		
		write_file(file_name, A, n, q, B);

		cout << "test " << num_test << " OK\n";
	}
}
