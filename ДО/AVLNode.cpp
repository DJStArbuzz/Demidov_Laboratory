#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class AVLNode {
public:
    int key;
    AVLNode* left;
    AVLNode* right;
    int depth;
};

// Определяет какое поддерево больше
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Глубина
int depth(AVLNode* n) {
    // Левый сын, которого нет
    if (n == NULL) {
        return 0;
    }
    return n->depth;
}

// Узел
AVLNode* newNode(int key) {
    AVLNode* node = new AVLNode();
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->depth = 1;
    return node;
}

// Поворот вправо поддерева с корнем y
AVLNode* rightRotate(AVLNode* y) {
    // Эти 2 сына обязаны быть в реализации
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    // Вращение
    x->right = y;
    y->left = T2;

    // Пересобираем высоты
    y->depth = max(depth(y->left), depth(y->right)) + 1;
    x->depth = max(depth(x->left), depth(x->right)) + 1;
    return x;
}

// Поворот влево поддерева с корнем x
AVLNode* leftRotate(AVLNode* x) {
    // Эти 2 сына обязаны быть в реализации
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    // Вращение
    y->left = x;
    x->right = T2;

    // Пересобираем высоты
    x->depth = max(depth(x->left), depth(x->right)) + 1;
    y->depth = max(depth(y->left), depth(y->right)) + 1;
    return y;
}

int getBalance(AVLNode* N) {
    if (N == NULL) {
        return 0;
    }

    // Хотелось бы -1, 0, 1
    // Если вылезаем за рамки, то все меняем
    return depth(N->left) - depth(N->right);
}

// Вставка элемента
AVLNode* insert(AVLNode* node, int key) {
    if (node == NULL) {
        return newNode(key);
    }
    if (key < node->key) {
        node->left = insert(node->left, key);
    }
    else if (key > node->key ){
        node->right = insert(node->right, key);
    }
    else {
        return node;
    }
    node->depth = 1 + max(depth(node->left), depth(node->right));

    int balance = getBalance(node);
    // Поворот лево-лево
    if (balance > 1 && key < node->left->key) {
        return rightRotate(node); 
    }
    
    // Поврот вправо вправо
    if (balance < -1 && key > node->right->key) {
        return leftRotate(node);
    }

    // Поворот лево право
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Поворот право влево
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return 0;
}

// Удаление узла
AVLNode* minValueNode(AVLNode* node) {
    AVLNode* current = node;
    
    while (current->left != NULL) {
        current = current->left;
    }

    return current;
}

AVLNode* deleteNode(AVLNode* root, int key) 
{
    if (root == NULL) {
        return root;
    }

    if (key < root->key) {
        root->left = deleteNode(root->left, key);
    }
    else if (key > root->key) {
        root->right = deleteNode(root->right, key);
    }
    else {
        if ((root->left == NULL) || (root->right == NULL)) {
            AVLNode* temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            }
            else {
                *root = *temp;
            }

            free(temp);
        }
        else {
            // Заменили значение в текущем узле
            AVLNode* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key); // Удаление может быть рекурсивно
        }
    }

    // Спустились до уровня листа
    if (root == NULL) {
        return root;
    }

    root->depth = 1 + max(depth(root->left), depth(root->right));
    int balance = getBalance(root);

    // Лево-лево
    if (balance > 1 && getBalance(root->left) >= 0) {
        return rightRotate(root);
    }

    // Лево-право
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Право-право
    if (balance < -1 && getBalance(root->right) <= 0) {
        return leftRotate(root);
    }

    // Право-лево
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
    if (Elem->left != NULL) {
        show(Elem->left, level + 1);
    }

    for (int i = 0; i < level; i++) {
        cout << "  ";
    }

    cout << Elem->key << '\n';
    if (Elem->right != NULL) {
        show(Elem->right, level + 1);
    }
}

int main()
{
    // AVL дерево
    // баланс в дереве
    /*
        Примеры: баланс по количеству элементов
                 баланс по глубине дерева (смотрим на количество связей с края слева и с края справа)

        Поворот - если мы удаляем или добавляем элементы, то поменяется баланс. Мы будем перемешивать узлы в дереве, чтобы получить балансировку

        set и map - следствия AVL дерева
    */

    AVLNode* root = NULL;
    root = insert(root, 12);
    root = insert(root, 8);
    root = insert(root, 18);
    root = insert(root, 5);
    root = insert(root, 11);
    root = insert(root, 17);
    root = insert(root, 4);
    root = insert(root, 1);
    root = insert(root, 2);
    root = insert(root, 3);
    root = insert(root, 6);
    root = insert(root, 7);

    show(root, 0);
    root = deleteNode(root, 4);
    show(root, 0);

    return 0;
}

