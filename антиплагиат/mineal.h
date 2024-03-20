#pragma once
#include <string>
#include <vector>
#include "had.h"


void Result_all_stud(
	string Name_student,
	vector<Solution_stud>& sol_stud,
	vector<pair<string, int>>& All_stud)
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

int Time_solution(string Data) {
	string day = "";
	day += Data[0] + Data[1];

	string month;
	months += Data[3] + Data[4];
	
	string year = "";
	year += Data[6] + Data[7] + Data[8] + Data[9];
	
	string clock = "";
	clock += Data[11] + Data[12];

	string minute = "";
	minute += Data[14] + Data[15];

	int time = (stoi(year) * 365 + stoi(month) * 31 + stoi(day));
	time = (time * 24 + stoi(clock)) * 60 + stoi(minute);
	return time;
}

void check_time_solution(vector<Solution_stud> &sol_stud) 
{
	for (int i = 0; i < sol_stud.size(); i++) {
		if (sol_stud[i].verdict != "OK") {
			int raz = 1e5;
			for (int j = 0; j < sol_stud.size(); j++) {
				if (i != j) {
					if (raz > abs(sol_stud[i].Time - sol_stud[j].Time) 
					{
						raz = abs(sol_stud[i].Time - sol_stud[j].Time);
					}
				}
			}
		}

		if (raz <= 3) {
			sol_stud[i].verdict = "Time";
		}
	}
}
