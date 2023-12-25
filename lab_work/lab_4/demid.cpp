#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <string>
#include <cmath>

using namespace std;

class AEROFLOT {
public:
    static const int maxStops = 3; // Максимальное количество промежуточных остановок

    int flightNumber;              // Номер рейса
    string destination;            // Название пункта назначения
    string airplaneType;           // Тип самолета
    string stops[maxStops];        // Статический массив-список промежуточных остановок

    // Конструктор класса AEROFLOT
    AEROFLOT(int flightNumber,
        const string& destination,
        const string& airplaneType,
        const string stops[]) :

        flightNumber(flightNumber),
        destination(destination),
        airplaneType(airplaneType) {
        for (int i = 0; i < maxStops; i++) {
            this->stops[i] = stops[i];
        }
    }

    // Процедура вывода данных о самолете
    void cout_airplane() {
        cout << "Номер рейса: " << flightNumber << endl;
        cout << "Название пункта назначения: " << destination << endl;
        cout << "Тип самолета: " << airplaneType << endl;
        cout << "Промежуточные остановки: ";
        for (int index = 0; index < maxStops; index++) {
            cout << stops[index] << " ";
        }
        cout << endl;
        cout << endl;

    }
};

void cin_from_file(vector<AEROFLOT>& airplane) {
    cout << "Введите имя файла: ";
    string fileName;
    cin >> fileName;

    // Ввод из файла
    ifstream inputFile(fileName);
    if (!inputFile.is_open()) {
        cout << "Ошибка открытия файла." << endl;
        cout << "Экстренный выход из программы!" << endl;
        exit(0);
    }

    int flightNumber;
    string destination, airplaneType;
    string stops[AEROFLOT::maxStops];

    while (inputFile >> flightNumber >> destination >> airplaneType) {
        for (int i = 0; i < AEROFLOT::maxStops; i++) {
            inputFile >> stops[i];
        }
        airplane.push_back(AEROFLOT(flightNumber, destination, airplaneType, stops));
    }

    inputFile.close();
}

void cin_from_keyboard(vector<AEROFLOT>& airplane) {
    // Ввод с клавиатуры
    int flightNumber;
    string destination, airplaneType;
    string stops[AEROFLOT::maxStops];

    cout << "Введите данные (номер рейса, пункт назначения, тип самолета, остановки):" << std::endl;
    while (cin >> flightNumber >> destination >> airplaneType) {
        for (int i = 0; i < AEROFLOT::maxStops; i++) {
            cin >> stops[i];
        }
        airplane.push_back(AEROFLOT(flightNumber, destination, airplaneType, stops));

        cout << "Продолжить ввод? (y/n): ";
        char continueInput;
        cin >> continueInput;
        if (continueInput != 'y') {
            break;
        }
    }
}

void cout_from_array(vector<AEROFLOT>& airplane) {
    if (airplane.size() != 0) {
        cout << "Все введенные Вами записи:" << endl;
        for (int index = 0; index < airplane.size(); index++) {
            airplane[index].cout_airplane();
        }
    }
    else {
        cout << "Нечего удалять." << endl;
    }
    cout << endl;
}

// Функция для сравнения записей по номеру рейса и типу самолета
bool compareAeroflot(const AEROFLOT& airplane1, const AEROFLOT& airplane2) {
    if (airplane1.flightNumber == airplane2.flightNumber) {
        return airplane1.airplaneType < airplane2.airplaneType;
    }
    return airplane1.flightNumber < airplane2.flightNumber;
}

// Сортировка записей
void sort_airplane_array(vector<AEROFLOT> airplane) {
    sort(airplane.begin(), airplane.end(), compareAeroflot);
    cout << "Отредактированные записи:" << endl;
    cout_from_array(airplane);
    cout << endl;
}

// Вывод на экран номеров рейсов и пунктов назначения, обслуживаемых самолетами заданного типа
void search_airplane_with_type(vector<AEROFLOT> airplaneArray) {
    string typeToSearch;
    cout << "Введите тип самолета для поиска: ";
    cin >> typeToSearch;

    cout << "Номера рейсов и пункты назначения для самолетов типа " << typeToSearch << ":" << endl;
    for (int index = 0; index < airplaneArray.size(); index++) {
        if (airplaneArray[index].airplaneType == typeToSearch) {
            cout << "Номер рейса: " << airplaneArray[index].flightNumber
                << ", Пункт назначения: " << airplaneArray[index].destination << endl;
        }
    }
}

// Вывод на экран самолетов, которые совершают остановки в заданном пункте
void search_airplane_with_place(vector<AEROFLOT> &airplaneArray) {
    string stopToSearch;
    cout << "Введите пункт для поиска: ";
    cin >> stopToSearch;

    cout << "Самолеты, совершающие остановки в пункте " << stopToSearch << ":" << std::endl;
    for (int index = 0; index < airplaneArray.size(); index++) {
        if (airplaneArray[index].destination == stopToSearch) {
            airplaneArray[index].cout_airplane();
        }
    }
}

void delete_place(vector<AEROFLOT> &airplaneArray) {
    if (airplaneArray.size() == 0) {
        cout << "Нечего удалять." << endl;
    }
    else {
        cout << "Введите номер самолета, который вы хотите удалить: ";

        int choise;
        cin >> choise;

        bool flag = true;
        for (int i = 0; i < airplaneArray.size(); i++) {
            if (airplaneArray[i].flightNumber == choise) {
                flag = false;
                for (int j = i; j < airplaneArray.size() - 1; j++) {
                    airplaneArray[j] = airplaneArray[j + 1];
                }
                airplaneArray.pop_back();
            }
        }
        if (flag) {
            cout << "Нет такого номера." << endl;
        }
    }
}

void operation() {
    cout << "1. Упорядочить записи по возрастанию." << endl;
    cout << "2. Вывести все рейсы." << endl;
    cout << "3. Вывод на экран номеров рейсов и пунктов назначения по введенному типу" << endl;
    cout << "4. Вывод на экран самолетов, которые совершают остановки по пункту." << endl;
    cout << "5. Удалить самолет по номеру." << endl;
    cout << "Выбор операции: ";
}

int main() {
    /*
    Лабораторная работа №4, Вариант 5

    Описать класс с именем AEROFLOT, содержащий следующие поля: номер
    рейса (int); название пункта назначения (string); тип самолета (string); список
    промежуточных остановок (статический массив string).
    Написать программу, выполняющую следующие действия:
    ∙ Ввод данных (файл, клавиатура на выбор пользователя).
    ∙ Упорядочить записи по возрастанию номера рейса и типу самолета.
    ∙ Вывод на экран номеров рейсов и пунктов назначения, обслуживаемых
    самолетами заданного типа.
    ∙ Вывод на экран самолетов, которые совершают остановки в заданном пункте.
    */
    setlocale(LC_ALL, "Russian");
    vector<AEROFLOT> airplaneArray;

    // Ввод данных из файла или с клавиатуры
    char choice;
    cout << "Выберите источник ввода данных (файл - 'f', клавиатура - 'k'): ";
    cin >> choice;

    if (choice == 'f') {
        cin_from_file(airplaneArray);
    }
    else if (choice == 'k') {
        cin_from_keyboard(airplaneArray);
    }
    else {
        cerr << "Некорректный выбор." << endl;
        return 1;
    }

    if (airplaneArray.size() == 0) {
        cout << "Работать не с чем!";
        return 0;
    }

    bool flag = true;
    int problem;
    while (flag) {
        operation();

        cin >> problem;
        cout << endl;

        switch (problem)
        {
        case(1):
            sort_airplane_array(airplaneArray);
            break;
        case(2):
            cout_from_array(airplaneArray);
            break;
        case(3):
            search_airplane_with_type(airplaneArray);
            break;
        case(4):
            search_airplane_with_place(airplaneArray);
            break;
        case(5):
            delete_place(airplaneArray);
            break;
        }
    }

    return 0;
}