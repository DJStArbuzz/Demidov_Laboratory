#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

/*  Задание 1, вариант 1:
    Необходимо реализовать собственный класс String для работы со строками.
*/
class ShebetaNI_String {
private:
    char* str = nullptr;  // Указатель на массив символов, который будет хранит строку
    size_t sz = 0;        // Переменная для отслеживания длины строки

public:
    // Конструкторы

    // 1. Конструктор по умолчанию
    ShebetaNI_String() : str(nullptr), sz(0) {}

    // 2. Конструктор с параметрами
    ShebetaNI_String(const char* string) {
        sz = strlen(string);
        str = new char[sz + 1]; // +1 для символа '\0
        strcpy_s(str, sz + 1, string);
    }

    // 3. Конструктор копирования
    ShebetaNI_String(const ShebetaNI_String& other) {
        sz = other.sz;
        str = new char[sz + 1]; // +1 для символа '\0'
        strcpy_s(str, sz + 1, other.str);
    }

    // 4. Деструктор
    ~ShebetaNI_String() {
        delete[] str;
    }

    // Методы класса ShebetaNI

    // 1. Возвращает длину строки
    size_t lenght() const {
        return sz;
    }

    // 2. Перегруженный оператор доступа к элементу строки по индексу
    char& operator[](size_t index) {
        return str[index];
    }

    // 3. Перегруженный оператор доступа к элементу строки 
    // по индексу для константных объектов.
    const char& operator[](size_t index) const {
        return str[index];
    }

    // 4. Добавляет содержимое переданной строки в конец текущей строки.
    void append(const ShebetaNI_String& string) {
        char* tmp = new char[sz + string.sz + 1];
        strcpy_s(tmp, sz + 1, str);
        strcpy_s(tmp + sz, string.sz + 1, string.str);

        delete[] str;
        str = tmp;
        sz += string.sz;
    }

    // 5 Возвращает подстроку, начиная с позиции start и содержащую count символов
    ShebetaNI_String substr(size_t start, size_t count) const {
        ShebetaNI_String result;
        if (start >= sz) {
            return str;
        }
        else {
            result.sz = min(count, sz - start);
            result.str = new char[result.sz + 1];
            strncpy_s(result.str, result.sz + 1,
                str + start, result.sz);
            return result;
        }
    }

    // Операторы
    // 1. Оператор присваивания (=)
    ShebetaNI_String& operator=(const ShebetaNI_String& other) {
        if (this != &other) {
            delete[] str;

            sz = other.sz;
            str = new char[sz + 1]; // +1 для символа '\0'
            strcpy_s(str, sz + 1, other.str);
        }
        return *this;
    }

    // 2. Оператор конкатенации (+)
    ShebetaNI_String operator+(const ShebetaNI_String& other) {
        ShebetaNI_String result = *this;
        result.append(other);
        return result;
    }

    // 3. Операторы сравнения
    bool operator==(const ShebetaNI_String& other) const {
        if (sz != other.sz) {
            return false;
        }
        return strcmp(str, other.str) == 0;
    }

    bool operator!=(const ShebetaNI_String& other) const {
        return !(*this == other);
    }

    bool operator<(const ShebetaNI_String& other) const {
        return strcmp(str, other.str) < 0;
    }

    bool operator>(const ShebetaNI_String& other) const {
        return strcmp(str, other.str) > 0;
    }

    bool operator<=(const ShebetaNI_String& other) const {
        return strcmp(str, other.str) <= 0;
    }

    bool operator>=(const ShebetaNI_String& other) const {
        return strcmp(str, other.str) >= 0;
    }

    // 4. Оператор ввода / вывода
    friend std::ostream& operator<<(std::ostream& os, const ShebetaNI_String& str);
    friend std::istream& operator>>(std::istream& is, ShebetaNI_String& str);
};

std::ostream& operator<<(std::ostream& os, const ShebetaNI_String& string) {
    os << string.str;
    return os;
}

std::istream& operator>>(std::istream& is, ShebetaNI_String& string) {
    std::vector<char> buffer;
    char ch;
    while (is.get(ch) && !isspace(ch)) { // считываем символы пока не встретим пробел или конец файла
        buffer.push_back(ch);
    }
    buffer.push_back('\0'); // добавляем нулевой символ в конец строки

    int length = buffer.size();
    string.sz = length - 1;
    string.str = new char[length];
    strcpy(string.str, buffer.data());

    return is;
}

void operation() {
    cout << "1. ---------" << endl;
    cout << "2. задание 2" << endl;
    cout << "3. задание 3" << endl;
    cout << "4. задание 4" << endl;
    cout << endl;
}

void problem2() {
    /*  Задание 2, вариант 9
        Текстовый файл состоит из символов. Текст разбит на строки различной длины.
        Вывести в файл все слова, предварительно преобразовав каждое из них по
        следующему правилу: из каждого слова нечетной длины удалить его среднюю букву.
    */
    ifstream cinFile("inputProblem2.txt");
    ofstream coutFile("outputProblem2.txt");

    ShebetaNI_String word, tmp;

    while (cinFile.is_open()) {
        cinFile >> tmp;
        if (tmp.lenght() == 1) {
            continue;
        }

        if (tmp.lenght() % 2 == 0) {
            cout << tmp << " ";
            coutFile << tmp << " ";
        }
        else {
            cout << tmp.substr(0, tmp.lenght() / 2) << tmp.substr(tmp.lenght() / 2 + 1, tmp.lenght() / 2) << " ";
            coutFile << tmp.substr(0, tmp.lenght() / 2) << tmp.substr(tmp.lenght() / 2 + 1, tmp.lenght() / 2) << " ";
        }

        if (cinFile.eof()) {
            break;
        }
    }

    cinFile.close();
    coutFile.close();
    cout << endl;
    cout << endl;
}

void problem3() {
    /*  Задание 3, вариант 10

    */
}

void problem4() {
    ShebetaNI_String word = "asda";
    cout << word;
    cout << endl;
    cout << word.lenght();
    cout << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");

    bool flag = true;
    int problem;
    while (flag) {
        operation();

        cin >> problem;
        cout << endl;

        switch (problem)
        {
        case(2):
            problem2();
            break;
        case(3):
            problem3();
            break;
        case(4):
            problem4();
            break;
        }
    }

    return 0;
}
