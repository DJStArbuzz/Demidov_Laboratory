#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>

using namespace std;

struct Node {
	int info = -1;		  // Узел не существует, не заполен
	Node* pred = NULL;    // Предок
	Node* first = NULL;   // Первенец
	Node* brother = NULL; // Брат
};

void push(Node* Elem, string& s, int id, int data) {
	if (id == s.size() - 1) {
		Elem->info = data;
	}
	if (s[id] == 'f') {
		if (Elem->first == NULL) {
			Node* Buf = new Node;
			Buf->pred = Elem;
			Elem->first = Buf;
		}
		push(Elem->first, s, id + 1, data);
	}
	if (s[id] == 'b') {
		if (Elem->brother == NULL) {
			Node* Buf = new Node;
			Buf->pred = Elem->pred;
			Elem->brother = Buf;
		}
		push(Elem->brother, s, id + 1, data);
	}
}

void show(Node* Elem, int level) {
	for (int i = 0; i < level; i++) {
		cout << "   ";
	}
	cout << Elem->info << '\n';
	if (Elem->first != NULL) {
		show(Elem->first, level + 1);
	}
	// Отец не помнит брата, а брат брата - да
	if (Elem->brother != NULL) {
		show(Elem->brother, level);
	}
}

int main()
{
	// 1. Бинарные деревья
	/*
				 pred
				/    \
			l. son   r. son
		 l. son < pred < r. son
	
	*/

	// 2. Дерево общего вида
	/* I
			 pred
			  |
		(info | связь)
		/   /    \   \
		  vector son
	
	II Отец знает только первенца
			
			 pred
			  |
			(info) -> brat
			  |
			 son

		Корень - вершина, которая указывает сама не себя
	*/
	Node* Root = new Node;
	string s;
	s = "p"; // Предок
	push(Root, s, 0, 10);
	s = "fp"; // Первенец
	push(Root, s, 0, 5);
	s = "fbp"; // Брат первенца
	push(Root, s, 0, 4);
	s = "fbbp"; // Брат брата первенца
	push(Root, s, 0, 3);
	s = "fbfp"; // Первенец брата первенца
	push(Root, s, 0, 2);
	s = "fffp"; // 
	push(Root, s, 0, 11);

	s = "ffbp";
	push(Root, s, 0, 12);

	s = "ffbbp";
	push(Root, s, 0, 13);

	s = "ffbfp";
	push(Root, s, 0, 14);

	show(Root, 0);
}
