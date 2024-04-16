#include <iostream>

class Permutation {
private:
    int* perm;
    int size;
public:
    Permutation(unsigned int n) {
        size = n;
        perm = new int[size];
        for (int i = 0; i < size; i++) {
            perm[i] = i;
        }
    }

    Permutation(unsigned int n, int* arr) {
        size = n;
        perm = new int[size];
        for (int i = 0; i < size; i++) {
            perm[i] = arr[i];
        }
    }

    Permutation operator*(const Permutation& p) const {
        Permutation result(size);
        for (int i = 0; i < size; i++) {
            result.perm[i] = perm[p.perm[i]];
        }
        return result;
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

    void next() {
        int i = size - 1;
        while (i > 0 && perm[i - 1] >= perm[i]) {
            i--;
        }

        if (i == 0) {
            return;
        }

        int j = size - 1;
        while (perm[j] <= perm[i - 1]) {
            j--;
        }

        std::swap(perm[i - 1], perm[j]);

        j = size - 1;
        while (i < j) {
            std::swap(perm[i], perm[j]);
            i++;
            j--;
        }
    }

    void previous() {
        int i = size - 1;
        while (i > 0 && perm[i - 1] <= perm[i]) {
            i--;
        }

        if (i == 0) {
            return;
        }

        int j = size - 1;
        while (perm[j] >= perm[i - 1]) {
            j--;
        }

        std::swap(perm[i - 1], perm[j]);

        j = size - 1;
        while (i < j) {
            std::swap(perm[i], perm[j]);
            i++;
            j--;
        }
    }

    bool operator<(const Permutation& p) const {
        for (int i = 0; i < size; i++) {
            if (perm[i] < p.perm[i]) {
                return true;
            }
            else if (perm[i] > p.perm[i]) {
                return false;
            }
        }
        return false;
    }

    bool operator>(const Permutation& p) const {
        return p < *this;
    }

    bool operator==(const Permutation& p) const {
        for (int i = 0; i < size; i++) {
            if (perm[i] != p.perm[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const Permutation& p) const {
        return !(*this == p);
    }

    bool operator<=(const Permutation& p) const {
        return *this < p || *this == p;
    }

    bool operator>=(const Permutation& p) const {
        return *this > p || *this == p;
    }

    friend std::ostream& operator<<(std::ostream& os, const Permutation& p) {
        for (int i = 0; i < p.size; i++) {
            os << p.perm[i] << " ";
        }
        return os;
    }

    ~Permutation() {
        delete[] perm;
    }
};

int main() {
    int arr1[] = { 1, 2, 0 };
    int arr2[] = { 1, 0, 2 };

    Permutation p1(3, arr1);
    Permutation p2(3, arr2);

    std::cout << "p1: " << p1 << std::endl;
    std::cout << "p2: " << p2 << std::endl;

    Permutation p3 = p1 * p2;
    std::cout << "p1 * p2: " << p3 << std::endl;

    ++p1;
    std::cout << "++p1: " << p1 << std::endl;

    --p2;
    std::cout << "--p2: " << p2 << std::endl;

    std::cout << "p1 < p2: " << (p1 < p2) << std::endl;
}
