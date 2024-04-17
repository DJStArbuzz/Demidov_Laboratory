#include <iostream>

using namespace std;
class Permutation {
private:
	int* list;
	int size;

public:
	Permutation(unsigned int n) {
		size = n;
        list = new int[size];
		for (int i = 0; i < size; i++) {
            list[i] = i;
		}
	}
    Permutation(unsigned int n, int arr[]) {
        size = n;
        list = new int[size];
        for (int i = 0; i < size; i++) {
            list[i] = arr[i];
        }
    }
    ~Permutation() {
        delete[] list;
    }

    
    void increment() {
        int i = size - 2;
        while (i >= 0 && list[i] > list[i + 1]) {
            i--;
        }

        if (i == -1) {
            return;
        }

        int j = size - 1;
        while (list[j] < list[i]) {
            j--;
        }

        swap(list[i], list[j]);
        reverse(list + i + 1, list + size);
    }

    void decrement() {
        int i = size - 2;
        while (i >= 0 && list[i] < list[i + 1]) {
            i--;
        }

        if (i == -1) {
            return;
        }

        int j = size - 1;
        while (list[j] > list[i]) {
            j--;
        }

        swap(list[i], list[j]);
        reverse(list + i + 1, list + size);
    }

    Permutation& operator++() {
        next();
        return *this;
    }

    Permutation operator++(int) {
        Permutation temp = *this;
        next();
        return temp;
    }

    Permutation& operator--() {
        previous();
        return *this;
    }

    Permutation operator--(int) {
        Permutation temp = *this;
        previous();
        return temp;
    }

    Permutation operator*(const Permutation& other) {
        Permutation result(size);
        for (int i = 0; i < size; i++) {
            result.list[i] = other.list[list[i]];
        }
        return result;
    }

    void next() {
        increment();
    }

    void previous() {
        decrement();
    }
    bool operator<(const Permutation& other) const {
        for (int i = 0; i < size; i++) {
            if (list[i] < other.list[i]) {
                return true;
            }
            else if (list[i] > other.list[i]) {
                return false;
            }
        }
        return false;
    }

    bool operator>(const Permutation& other) const {
        return other < *this;
    }

    bool operator==(const Permutation& other) const {
        for (int i = 0; i < size; i++) {
            if (list[i] != other.list[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const Permutation& other) const {
        return !(*this == other);
    }

    bool operator<=(const Permutation& other) const {
        return *this < other || *this == other;
    }

    bool operator>=(const Permutation& other) const {
        return *this > other || *this == other;
    }

    void print() const {
        for (unsigned int i = 0; i < size; ++i) {
            cout << list[i] << " ";
        }
        cout << '\n';
    }

};

int main() {
    setlocale(LC_ALL, "Russian");
    int arr1[] = { 1, 0, 2 , 4, 5};
    int arr2[] = { 2, 3, 0 , 1, 4 };

    Permutation p1(5, arr1);
    Permutation p2(5, arr2);

    cout << "p1: ";
    p1.print();
    cout << "p2: ";
    p2.print();

    Permutation p3 = p1 * p2;
    cout << "p1 * p2: ";
    p3.print();

    p3.next();
    cout << "p3 после next(): ";
    p3.print();

    p3.previous();
    cout << "p3 после previous(): ";
    p3.print();

    p3.previous();
    cout << "p3 после previous() * 2: ";
    p3.print();
    int arr3[] = { 0, 1, 2 , 3, 4 };
    Permutation p4(5, arr3);

    p4.previous();
    cout << "p4 после previous(): ";
    p4.print();

    --p4;
    p4.print();
    
    cout << (p1 < p2);

    return 0;
}
