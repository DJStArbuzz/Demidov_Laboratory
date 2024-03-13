#pragma once
#include "had.h"

void Result_all_stud(
	string Name_student,
	vector<Solution_stud> &sol_stud,
	vector<pair<string, int>> &All_stud) 
{
	pair<string, int> info_one_stud;
	info_one_stud.first = Name_student;
	int count_accept = 0;
	for (int i = 0; i < sol_stud.size(); i++) {
		if (sol_stud[i].verdict == "OK") {
			count_accept++;
		}

		if (sol_stud[i].verdict == "Coincidence" &&
			sol_stud[i].dist_levenstein > 40) {
			count_accept++;
		}
	}

	info_one_stud.second = count_accept;
	All_stud.push_back(info_one_stud);
}

string Generate_path_solution(string Name_student,
	string Name_number_contest,
	string Name_tasks)
{
	string path = Folder_base_put + Folder_base_stud;
	path += Name_student + '/';
	path += Name_number_contest + '/';
	path += Name_tasks + ".txt";
	return path;
}

string Generate_path_coach(string Name_number_contest,
	string Name_tasks) {
	string path = Folder_base_put + Folder_base_stud;
	path += Nick_name_coach + '/';
	path += Name_number_contest + '/';
	path += Name_tasks + ".txt";

		return path;
}
