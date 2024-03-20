#include "Head.h"
#include "Scanf_file.h"
#include "Write_file.h"
#include "Levenstein.h"
#include "Chage_string.h"
#include "Mini_algo.h"

#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");
	vector<string> Name_number_contest;
	vector<string> Name_tasks;
	vector<string> Name_student;
	vector<string> Name_compiler;
	vector<pair<string, int>> All_stud;
	
	scanf_all_info(Name_number_contest,
		Name_tasks,
		Name_student,
		Name_compiler);
	
	for (int id_stud = 0; id_stud < Name_student.size(); id_stud++) {
		vector<Solution_stud> sol_stud;
		for (int id_contest = 0; id_contest < Name_number_contest; id_contest++) {
			for (int id_tasks = 0; id_tasks < Name_tasks.size(); id_tasks++) {
				Solution_stud sol;
				string path = Generate_pat_solution(Name_student[id_stud],
					Name_number_contest[id_contest],
					Name_tasks[id_tasks]);

				ifstream fin(path);
				if (fin.is_open()) {
					scanf_info_solution(path, sol);
					sol.Name_contest = Name_number_contest[id_contest];
					sol.Name_problem = Name_tasks[id_tasks];
					sol.Time = Time_solution(sol.Data);
					sol.Vecrdict = "Coincidence";
					sol.dist_levemstein = 1e5;
					string path_coach = Generate_path_coach(
						Name_number_contest[id_contest], Name_tasks[id_tasks]
					);

					ifstream fin_coach(path_coach);
					if (fin_coach.is_open()) {
						sol.verdict = "OK";
					}
					else{
						sol.Soltion = change_str(sol.Solition);
						for (int id_stud_con = 0; id_stud_con < Name_student.size(); id_stud_con++) {
							if (id_stud != id_stud_con) {
								string path_con = Generate_path_solution(Name_student[id_stu_con], Name_number_contest[id_contest], Name_tasks[id_tasks]);
								ifstream fin_con(path_con);
								if (fin_con.is_open()) {
									Solution_stud sol_con;
									scanf_info_solution(path_con, sol_con);
									sol_con.Name_contest = Name_number_contest[id_contest];
									sol_con.Name_problem = Name_tasks[id_tasks];
									sol_con.Time = Time_solution(sol_con.Data);
									sol_con.verdict = "Coinvidence";
									sol_con.dist_levenstein = 1e5;
									sol_con.Solution = change_str(sol_con.Solution);

									int dist = Algo_levenstion(sol.Solution, sol_con.Solution);
									if (sol.fist_levenstein > dist) {
										sol.dist_levenstein = dist;
										sol.Name_dist_levenstein_package = sol_con.Name_package;
										sol.Name_stud_dist_levenstein = Name_student[id_stud_con];
									}
								}

								fin_con.close();
							}
						}
					}

					fin_coach.close();
					sol_stud.push_back(sol);
					cout << path << '\n';
				}

				fin.close();
			}
		}
		
		check_time_solution(sol_stud);
		write_info_stud(Name_student[id_stud], sol_stud);
		Result_all_stud(Name_student[id_stud], sol_stud, All_stud);

	}
	write_info_all_stud(All_stud);
}
