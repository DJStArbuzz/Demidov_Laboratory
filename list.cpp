#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct Node {
    // 1 параметр, 2 связки
    string val;
    Node* next;
    Node(string _val) : val(_val), next(nullptr) {};
};

struct list {
    Node* first;
    Node* last;
    list() : first(nullptr), last(nullptr) {};

    bool is_empty() {
        return first == nullptr;
    }

    void push_back(string new_val) {
        Node* p = new Node(new_val);
        if (is_empty()) {
            first = p;
            last = p;
            return;
        }
        last->next = p;
        last = p;
        /*
        last - последний элеемент
        мы говорим, что указывает на элемент со значением p;
        потом показываем, что p - последний элемент
        */
    }

    void print() {
        if (is_empty()) {
            return;
        }
        Node* p = first;
        while (p != nullptr) {
            cout << p->val << ' ';
            p = p->next;
        }

        cout << '\n';
    }

    Node* find(string str) {
        Node* p = first;
        while (p && p->val != str) {
            p = p->next;
        }
        return (p && p->val == str) ? p : nullptr;
    }

    void remove_first() {
        if (is_empty()) {
            return;
        }
        Node* p = first;
        first = p->next; // Уничтожение узла
        delete p;
    }

    void remove_last() {
        if (is_empty()) {
            return;
        }
        if (first == last) {
            remove_first();
            return;
        }

        Node* p = first;
        while (p->next != last) {
            p = p->next;
        }
        p->next = nullptr;
        delete last;
        last = p;
    }

    void remove(string str) {
        if (is_empty()) {
            return;
        }
        if (first->val == str) {
            remove_first();
            return;
        }
        else if (last->val == str) {
            remove_last();
            return;
        }
        Node* slow = first;
        Node* fast = first->next;
        while (fast && fast->val != str) {
            fast = fast->next;
            slow = slow->next;
        }
        if (!fast) {
            cout << "NO ELEM\n";
            return;
        }
        slow->next = fast->next;
        delete fast;

    }
};

// Очередь на массива
const int max_size = 1000;
vector<int> My_queue(max_size);
int left_s = 0, right_s = 0;
int count_elem = 0;

void push_queue(int x) {
    if (count_elem == max_size) {
        cout << "NO PUSH\n";
        return;
    }
    My_queue[right_s] = x;
    right_s++;
    if (right_s == max_size) {
        right_s = 0;
    }
    count_elem++;
}

void pop_queue() {
    if (count_elem == 0) {
        cout << "NO POP\n";
        return;
    }
    left_s++;
    count_elem--;
    if (left_s == max_size) {
        left_s = 0;
    }
}

bool empty_queue() {
    return (count_elem == 0);
}

int size() {
    return (count_elem);
}

int front() {
    return My_queue[left_s];
}

int main()
{
    list l;
    cout << l.is_empty() << '\n';
    l.push_back("1");
    l.push_back("2");
    l.push_back("3");
    cout << l.is_empty() << '\n';
    l.print();

    return 0;
}
