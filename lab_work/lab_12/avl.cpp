#include <iostream>

using namespace std;

class AVLNode {
public:
	int key;
	AVLNode* left;
	AVLNode* right;
	int depth;
};

int max(int a, int b) {
	return a > b ? a : b;
}

int depth(AVLNode* n) {
	if (n == NULL)
		return 0;
	return n->depth;
}

AVLNode* newNode(int key) {
	AVLNode* node = new AVLNode();
	node->key = key;
	node->left = NULL;
	node->right = NULL;
	node->depth = 1;
	return node;
}

//повернуть вправо поддерево с корнем y
AVLNode* rightRotate(AVLNode* y) {
	AVLNode* x = y->left;
	AVLNode* T2 = x->right;
	//вращение
	x->right = y;
	y->left = T2;
	y->depth = max(depth(y->left), depth(y->right)) + 1;
	x->depth = max(depth(x->left), depth(x->right)) + 1;
	return x;
}

//повернуть влево
AVLNode* leftRotate(AVLNode* x) {
	AVLNode* y = x->right;
	AVLNode* T2 = y->left;

	y->left = x;
	x->right = T2;
	x->depth = max(depth(x->left), depth(x->right)) + 1;
	y->depth = max(depth(y->left), depth(y->right)) + 1;
	return y;
}

int getBalance(AVLNode* N) {
	if (N == NULL)
		return 0;
	return depth(N->left) - depth(N->right);
}

//вставка элементов
AVLNode* insert(AVLNode* node, int key) {
	if (node == NULL)
		return newNode(key);
	if (key < node->key)
		node->left = insert(node->left, key);
	else if (key > node->key)
		node->right = insert(node->right, key);
	else
		return node;
	node->depth = 1 + max(depth(node->left), depth(node->right));
	int balace = getBalance(node);

	if (balace > 1 && key < node->left->key)
		return rightRotate(node);
	if (balace<-1 && key>node->right->key)
		return leftRotate(node);
	//лево право
	if (balace > 1 && key > node->left->key) {
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}
	//право лево
	if (balace < -1 && key < node->right->key) {
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}

	return node;
}

AVLNode* minValueNode(AVLNode* node) {
	AVLNode* current = node;
	while (current->left != NULL)
	{
		current = current->left;
	}
	return current;
}

AVLNode* deleteNode(AVLNode* root, int key) {
	if (root == NULL)
		return root;
	if (key < root->key)
		root->left = deleteNode(root->left, key);
	else if (key > root->key)
		root->right = deleteNode(root->right, key);
	else
	{
		if (root->left == NULL || root->right == NULL) {
			AVLNode* temp = root->left ? root->left : root->right;
			if (temp == NULL) {
				temp = root;
				root = NULL;
			}
			else
				*root = *temp;

			free(temp);
		}
		else
		{
			AVLNode* temp = minValueNode(root->right);
			root->key = temp->key;
			root->right = deleteNode(root->right, temp->key);
		}
	}

	if (root == NULL)
		return root;
	root->depth = 1 + max(depth(root->left), depth(root->right));
	int balance = getBalance(root);

	//лево лево
	if (balance > 1 && getBalance(root->left) >= 0)
		return rightRotate(root);
	//лево право
	if (balance > 1 && getBalance(root->left) < 0) {
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}
	//право право
	if (balance < -1 && getBalance(root->right) <= 0)
		return leftRotate(root);
	//право лево
	if (balance < -1 && getBalance(root->right) > 0) {
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}
	return root;
}

void inOrder(AVLNode* root) {
	if (root != NULL) {
		inOrder(root->left);
		cout << root->key << " ";
		inOrder(root->right);
	}
}

void show(AVLNode* Elem, int level) {
	if (Elem->left != NULL)
		show(Elem->left, level + 1);
	for (int i = 0; i < level; i++)
		cout << "          ";
	cout << Elem->key << "\n";
	if (Elem->right != NULL)
		show(Elem->right, level + 1);
}

// Поиск элемента в дереве по ключу
AVLNode* search(AVLNode* root, int key) {
	AVLNode* current = root;
	while (current != NULL) {
		if (key < current->key) {
			current = current->left;
		}
		else if (key > current->key) {
			current = current->right;
		}
		else {
			return current;
		}
	}
	return NULL;
}


// Очистка дерева
void clearTree(AVLNode* root) {
	if (root != NULL) {
		clearTree(root->left);
		clearTree(root->right);
		delete root;
	}
	else {
		return;
	}
}

// Копирование элемента в однонаправленный циклический список
class ListNode {
public:
	int key;
	ListNode* next;
};

ListNode* copyToLinkedList(AVLNode* root) {
	if (root == NULL)
		return NULL;

	ListNode* head = new ListNode();
	head->key = root->key;

	ListNode* current = head;

	if (root->left != NULL) {
		current->next = copyToLinkedList(root->left);
	}

	ListNode* temp = current;
	while (current->next != NULL)
		current = current->next;

	if (root->right != NULL) {
		current->next = copyToLinkedList(root->right);
	}

	return temp;
}

// Очистка однонаправленного циклического списка
void clearLinkedList(ListNode* head) {
	if (head != NULL) {
		ListNode* current = head->next;
		while (current != head) {
			ListNode* temp = current;
			current = current->next;
			delete temp;
		}
		delete head;
	}
}
void showLinkedList(ListNode* head) {
	ListNode* current = head;
	while (current != NULL) {
		cout << current->key << " ";
		current = current->next;
	}
	cout << endl;
}


int main()
{
	AVLNode* root = NULL;
	root = insert(root, 12);
	root = insert(root, 8);
	root = insert(root, 45);
	root = insert(root, 21);
	root = insert(root, 67);
	root = insert(root, 3);
	root = insert(root, 9);
	root = insert(root, 5);
	root = insert(root, 3);
	root = insert(root, 9);
	root = insert(root, 56);
	root = insert(root, 21);
	root = insert(root, 29);
	root = insert(root, 40);
	root = insert(root, 72);
	root = insert(root, 11);
	root = insert(root, 12);
	root = insert(root, 13);
	root = insert(root, 14);
	root = insert(root, 15);
	root = insert(root, 16);
	root = insert(root, 17);
	root = insert(root, 18);
	show(root, 0);


	cout << "\n-------------\n";
	AVLNode *tm = search(root, 21);
	
	show(tm, 0);
	cout << "\n-------------\n";
	show(root, 0);

	cout << "\n" << root->depth;

	cout << "\n-------------\n";


	cout << "\n-------------\n";

	ListNode* y = copyToLinkedList(root);
	showLinkedList(y);
}

