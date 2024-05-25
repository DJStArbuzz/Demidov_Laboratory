#include <iostream>

using namespace std;

// Реализуйте шаблонный класс deque — динамический массив
// Класс deque должен быть шаблонным.
template <typename T>
class deque {
private:
    T* data;
    int size;
    int capacity;
public:
    // Оба вида конструкторов. 
    // Обычный конструктор
    deque() {
        data = new T[1];
        size = 0;
        capacity = 1;
    }
    // Конструктор коипрования
    deque(const deque& other) {
        size = other.size;
        capacity = other.capacity;
        data = new T[capacity];
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }
    // Операция push_back, которая помогает вставлять элементы в конец дэка.
    void push_back(T value) {
        if (size == capacity) {
            T* newData = new T[2 * capacity];
            for (int i = 0; i < size; i++) {
                newData[i] = data[i];
            }
            capacity *= 2;
            delete[] data;
            data = newData;
        }
        data[size++] = value;
    }
    // Операция pop_back, которая используется для удаления элемента из задней части контейнера
    void pop_back() {
        if (size > 0) {
            size--;
        }
    }
    //  Операция push_front, которая помогает вставлять элементы в начало дэка.
    void push_front(T value) {
        if (size == capacity) {
            T* newData = new T[2 * capacity];
            for (int i = 0; i < size; i++) {
                newData[i + 1] = data[i];
            }
            capacity *= 2;
            delete[] data;
            data = newData;
        }
        else {
            for (int i = size; i > 0; i--) {
                data[i] = data[i - 1];
            }
        }
        data[0] = value;
        size++;
    }
    // Оператор [], дающий доступ к i-му элементу в массиве
    T& operator[](int index) {
        if (index >= 0 && index < size) {
            return data[index];
        }
        else {
            throw out_of_range("Индекс за пределами допустимого");
        }
    }
    // Метод back() - возвращает прямую ссылку на последний элемент в контейнере.
    T& back() {
        if (size > 0) {
            return data[size - 1];
        }
        else {
            throw out_of_range("Контейнер пуст");
        }
    }
    const T& back() const {
        if (size > 0) {
            return data[size - 1];
        }
        else {
            throw out_of_range("Контейнер пуст");
        }
    }
    // Метод front() - возвращает прямую ссылку на первый(нулевой) элемент в контейнере.
    T& front() {
        if (size > 0) {
            return data[0];
        }
        else {
            throw out_of_range("Контейнер пуст");
        }
    }
    const T& front() const {
        if (size > 0) {
            return data[0];
        }
        else {
            throw out_of_range("Контейнер пуст");
        }
    }
    // Метод empty() - проверка на наличие элелментов в контейнере
    bool empty() const {
        return getSize() == 0;
    }
    // Метод getSize() - метод, возвращающий размер контейнера
    int getSize() const {
        return size;
    }
    // Неконстантый итератор, унаследованный от std::iterator
    class iterator : public std::iterator<random_access_iterator_tag, T> {
    private:
        T* ptr;
    public:
        iterator(T* p) : ptr(p) {}

        T& operator*() {
            return *ptr;
        }

        iterator& operator++() {
            ptr++;
            return *this;
        }

        iterator operator++(int) {
            iterator tmp = *this;
            ptr++;
            return tmp;
        }

        bool operator==(const iterator& other) const {
            return ptr == other.ptr;
        }

        bool operator!=(const iterator& other) const {
            return ptr != other.ptr;
        }

        T& operator[](int index) {
            return *(ptr + index);
        }

        iterator& operator+=(int n) {
            ptr += n;
            return *this;
        }

        iterator operator+(int n) {
            iterator tmp = *this;
            tmp += n;
            return tmp;
        }

        iterator operator--() {
            ptr--;
            return *this;
        }

        iterator operator--(int) {
            iterator tmp = *this;
            ptr--;
            return tmp;
        }

        iterator& operator-=(int n) {
            ptr -= n;
            return *this;
        }

        iterator operator-(int n) {
            iterator tmp = *this;
            tmp -= n;
            return tmp;
        }

        int operator-(const iterator& other) {
            return ptr - other.ptr;
        }

        bool operator<(const iterator& other) {
            return ptr < other.ptr;
        }

        bool operator>(const iterator& other) {
            return ptr > other.ptr;
        }

        bool operator<=(const iterator& other) {
            return ptr <= other.ptr;
        }

        bool operator>=(const iterator& other) {
            return ptr >= other.ptr;
        }
    };
    // Константый итератор
    class const_iterator : public std::iterator<random_access_iterator_tag, const T> {
    private:
        const T* ptr;
    public:
        const_iterator(const T* p) : ptr(p) {}

        const T& operator*() {
            return *ptr;
        }

        const_iterator& operator++() {
            ptr++;
            return *this;
        }

        const_iterator operator++(int) {
            const_iterator tmp = *this;
            ptr++;
            return tmp;
        }

        bool operator==(const const_iterator& other) const {
            return ptr == other.ptr;
        }

        bool operator!=(const const_iterator& other) const {
            return ptr != other.ptr;
        }

        const T& operator[](int index) {
            return *(ptr + index);
        }

        const_iterator& operator+=(int n) {
            ptr += n;
            return *this;
        }

        const_iterator operator+(int n) {
            const_iterator tmp = *this;
            tmp += n;
            return tmp;
        }

        const_iterator operator--() {
            ptr--;
            return *this;
        }

        const_iterator operator--(int) {
            const_iterator tmp = *this;
            ptr--;
            return tmp;
        }

        const_iterator& operator-=(int n) {
            ptr -= n;
            return *this;
        }

        const_iterator operator-(int n) {
            const_iterator tmp = *this;
            tmp -= n;
            return tmp;
        }

        int operator-(const const_iterator& other) {
            return ptr - other.ptr;
        }

        bool operator<(const const_iterator& other) {
            return ptr < other.ptr;
        }

        bool operator>(const const_iterator& other) {
            return ptr > other.ptr;
        }

        bool operator<=(const const_iterator& other) {
            return ptr <= other.ptr;
        }

        bool operator>=(const const_iterator& other) {
            return ptr >= other.ptr;
        }
    };
    // Метод begin() возвращает итератор, который указывает на первый элемент контейнера
    iterator begin() {
        return iterator(data);
    }
    const_iterator begin() const {
        return const_iterator(data);
    }
    const_iterator cbegin() const {
        return const_iterator(data);
    }
    // Метод begin() возвращает итератор, который указывает на последний элемент контейнера
    iterator end() {
        return iterator(data + size);
    }
    const_iterator end() const {
        return const_iterator(data + size);
    }
    const_iterator cend() const {
        return const_iterator(data + size);
    }
    // rbegin() и rend() — это методы, которые используются для получения реверсивных итераторов.
    iterator rbegin() {
        return iterator(data + size - 1);
    }
    const_iterator rbegin() const {
        return const_iterator(data + size - 1);
    }
    const_iterator crbegin() const {
        return const_iterator(data + size - 1);
    }
    iterator rend() {
        return iterator(data - 1);
    }
    const_iterator rend() const {
        return const_iterator(data - 1);
    }
    const_iterator crend() const {
        return const_iterator(data - 1);
    }
    // Деструктор deque
    ~deque() {
        delete[] data;
    }
};

int main() {
    setlocale(LC_ALL, "RUS");
    
    cout << "Создадим контейнер: ";
    deque<int> deqFirst, deqEmpty;
    deqFirst.push_back(1);
    deqFirst.push_back(2);
    deqFirst.push_front(0);
    deqFirst.push_front(3);
    for (deque<int>::iterator it = deqFirst.begin(); it != deqFirst.end(); it++) {
        cout << *it << ' ';
    }

    cout << "\nУдалим последний элемент: ";
    deqFirst.pop_back();
    for (deque<int>::iterator it = deqFirst.begin(); it != deqFirst.end(); it++) {
        cout << *it << ' ';
    }
    cout << '\n';

    cout << "---------------\n";
    cout << "Нулевой и первый элементы в дэке: " << deqFirst[0] << ' ' << deqFirst[1] << '\n';
    
    cout << "Конец и начало дэка: ";
    cout << deqFirst.back() << " " << deqFirst.front() << '\n';

    cout << "Размер заполненного и пустого дэка: ";
    cout << deqFirst.getSize() << " " << deqEmpty.getSize() << '\n';

    cout << "Проверка на пустоту: ";
    cout << deqFirst.empty() << " " << deqEmpty.empty() << '\n';

    cout << "---------------\n";
    cout << "Обработка rbegin() и rend(): ";
    for (deque<int>::iterator it = deqFirst.rbegin(); it != deqFirst.rend(); it--) {
        cout << *it << ' ';
    }
    cout << '\n';

    cout << "---------------\n";
    cout << "Конструктор копирования + добавление новых элементов: ";
    deque<int> deqCopy = deqFirst;
    deqCopy.push_front(2);
    deqCopy.push_back(4);
    for (deque<int>::iterator it = deqCopy.begin(); it != deqCopy.end(); it++) {
        cout << *it << ' ';
    }
    cout << "\nРассмотрим элементы новго дэка: \n";
    cout << "Конец и начало: " << deqCopy.back() << " " << deqCopy.front() << '\n';
    cout << "Обратное начало: " << *deqCopy.rbegin() << '\n';

    cout << "---------------\n";
    cout << "Обработка ошибок:\n";
    try {
        cout << deqEmpty.front() << '\n'; // Будет выброшено исключение, так как контейнер пустой
    }
    catch (const out_of_range& e) {
        cout <<  "Ошибка: " << e.what() << endl;
    }

    try {
        cout << deqEmpty.back() << '\n'; // Будет выброшено исключение, так как контейнер пустой
    }
    catch (const out_of_range& e) {
        cout << "Ошибка: " << e.what() << endl;
    }

    try {
        cout << deqCopy[5] << '\n'; // Будет выброшено исключение, так как индекс больше, чем текущий размер
    }
    catch (const std::out_of_range& e) {
        cout << "Ошибка: " << e.what() << '\n';
    }

    return 0;
}
