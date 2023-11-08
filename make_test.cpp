#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <string>
#include <fstream>
#include <ctime>

using namespace std;

//max(x1,x2,x3,x4)

void write_file(string file_name, int a1, int a2, int a3, int a4)
{
	ofstream out(file_name);
	out << a1 << " " << a2 << " " << a3 << " " << a4;
	out.close();
}

void generate_name_file(string& file_name, int num_test)
{
	if (num_test < 10)
	{
		file_name = "output/MAX/0";
		file_name = file_name + to_string(num_test);
		file_name = file_name + ".txt";
	}
	else
	{
		file_name = "output/MAX/";
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
		int a1, a2, a3, a4;
		if (num_test <= 20)
		{
			a1 = rand() % 100 + 1;
			a2 = rand() % 100 + 1;
			a3 = rand() % 100 + 1;
			a4 = rand() % 100 + 1;
		}
		else if (num_test <= 80)
		{
			a1 = (rand() * rand() + rand()) % 1000000 + 1;
			a2 = (rand() * rand() + rand()) % 1000000 + 1;
			a3 = (rand() * rand() + rand()) % 1000000 + 1;
			a4 = (rand() * rand() + rand()) % 1000000 + 1;
		}
		else
		{
			a1 = (rand() * rand() + rand()) % 1000000000 + 1;
			a2 = (rand() * rand() + rand()) % 1000000000 + 1;
			a3 = (rand() * rand() + rand()) % 1000000000 + 1;
			a4 = (rand() * rand() + rand()) % 1000000000 + 1;
		}
		write_file(file_name, a1, a2, a3, a4);
	}
}
