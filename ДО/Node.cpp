#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>

using namespace std;

struct Node {
	int info;
	Node* pred = NULL;
	Node* left = NULL;
	Node* right = NULL;                      
};

// Добавление элемента
void push(Node* Elem, int data) {
	// Проверка есть ли дерево - есть ли  предок?
	if (Elem->pred == NULL) {
		Elem->info = data;
		Elem->pred = Elem;
	}
	// Куда нужно вставить элемент
	else {
		// Предок больше сына
		if (Elem->info > data) {
			// Левого сына нет
			if (Elem->left == NULL) {
				Node* Buf = new Node;
				Buf->info = data;
				Buf->pred = Elem;
				Elem->left = Buf;
			}
			// Сын левый есть, спускаемся дальше
			else {
				push(Elem->left, data);
			}
		}
		// Правый сын больше предка
		else if (Elem->info < data) {
			// Правого сына нет
			if (Elem->right == NULL) {
				Node* Buf = new Node;
				Buf->info = data;
				Buf->pred = Elem;
				Elem->right = Buf;
			}
			// Правый сын есть, спускаемся дальше
			else {
				push(Elem->right, data);
			}
		}
	}
}

// Вывод
void show(Node* Elem, int level) {
	if (Elem->left != NULL) {
		show(Elem->left, level + 1);
	}
	for (int i = 0; i < level; i++) {
		cout << "   ";
	}
	cout << Elem->info << '\n';

	if (Elem->right != NULL) {
		show(Elem->right, level + 1);
	}
}

// Как show, но с проверкой
void find_tree(Node* Elem, bool& flag, int data) {
	if (Elem->left != NULL) {
		find_tree(Elem->left, flag, data);
	}
	if (Elem->info == data) {
		flag = true;
	}
	if (Elem->right != NULL) {
		find_tree(Elem->right, flag, data);
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

	push(Root, 10);
	push(Root, 6);
	push(Root, 5);
	push(Root, 4);
	push(Root, 8);
	push(Root, 7);
	push(Root, 9);
	push(Root, 13);
	show(Root, 0);
}
