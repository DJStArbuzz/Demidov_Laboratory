#include <iomanip>
#include <vector>
#include <iostream>
#include <string>

using namespace std;

class BigInteger {
    string number;
public:
    // Конструкторы:
    BigInteger(unsigned long long n = 0);
    BigInteger(string&);
    BigInteger(const char*);
    BigInteger(BigInteger&);

    BigInteger& operator=(const BigInteger&);

    // 1. Сложение, вычитание, умножение, деление
    // остаток по модулю, работающие так же, как и для int
    friend BigInteger& operator+=(BigInteger&, const BigInteger&);
    friend BigInteger operator+(const BigInteger&, const BigInteger&);
    friend BigInteger operator-(const BigInteger&, const BigInteger&);
    friend BigInteger& operator-=(BigInteger&, const BigInteger&);
    friend BigInteger& operator*=(BigInteger&, const BigInteger&);
    friend BigInteger operator*(const BigInteger&, const BigInteger&);
    friend BigInteger& operator/=(BigInteger&, const BigInteger&);
    friend BigInteger operator/(const BigInteger&, const BigInteger&);
    friend BigInteger operator%(const BigInteger&, const BigInteger&);
    friend BigInteger& operator%=(BigInteger&, const BigInteger&);
    friend BigInteger& operator^=(BigInteger&, const BigInteger&);
    friend BigInteger operator^(BigInteger&, const BigInteger&);

    // 2. Префикс/постфиксный инкремент и декремент
    BigInteger& operator++();
    BigInteger operator++(int temp);
    BigInteger& operator--();
    BigInteger operator--(int temp);

    // 3. Операторы сравнения
    friend bool operator==(const BigInteger&, const BigInteger&);
    friend bool operator!=(const BigInteger&, const BigInteger&);
    friend bool operator>(const BigInteger&, const BigInteger&);
    friend bool operator>=(const BigInteger&, const BigInteger&);
    friend bool operator<(const BigInteger&, const BigInteger&);
    friend bool operator<=(const BigInteger&, const BigInteger&);

    // 4. Вывод в поток и ввод из потока
    friend ostream& operator<<(ostream&, const BigInteger&);
    friend istream& operator>>(istream&, BigInteger&);

    // 5. Метод toString(), возвращающий строковое представление числа
    string toString() {
        return number;
    }

    // 6. Конструирование из int
     
    // 7. Неявное преобразование в bool

    // Дополнительно
    friend BigInteger sqrt(BigInteger& a);
    friend BigInteger Factorial(int n);
    friend void divide_by_2(BigInteger& a);
    friend bool Null(const BigInteger&);
    friend int Length(const BigInteger&);
    int operator[](const int)const;
};

BigInteger::BigInteger(string& s) {
    number = "";
    int n = s.size();
    for (int i = n - 1; i >= 0;i--) {
        if (!isdigit(s[i]))
            throw("ERROR");
        number.push_back(s[i] - '0');
    }
}
BigInteger::BigInteger(unsigned long long tmp) {
    while (tmp) {
        number.push_back(tmp % 10);
        tmp /= 10;
    }
}
BigInteger::BigInteger(const char* s) {
    number = "";
    for (int i = strlen(s) - 1; i >= 0;i--)
    {
        if (!isdigit(s[i]))
            throw("ERROR");
        number.push_back(s[i] - '0');
    }
}
BigInteger::BigInteger(BigInteger& a) {
    number = a.number;
}

bool Null(const BigInteger& a) {
    if (a.number.size() == 1 && a.number[0] == 0)
    {
        return true;
    }
    return false;
}
int Length(const BigInteger& a) {
    return a.number.size();
}

int BigInteger::operator[](const int index)const {
    if (number.size() <= index || index < 0)
        throw("ERROR");
    return number[index];
}

bool operator==(const BigInteger& first, const BigInteger& second) {
    return first.number == second.number;
}

bool operator!=(const BigInteger& first, const BigInteger& second) {
    return !(first == second);
}

bool operator<(const BigInteger& first, const BigInteger& second) {
    int n = Length(first), m = Length(second);
    if (n != m)
    {
        return n < m;
    }
    while (n--) {
        if (first.number[n] != second.number[n])
        {
            return first.number[n] < second.number[n];
        }
    }
    return false;
}
bool operator>(const BigInteger& first, const BigInteger& second) {
    return second < first;
}

bool operator>=(const BigInteger& first, const BigInteger& second) {
    return !(first < second);
}

bool operator<=(const BigInteger& first, const BigInteger& second) {
    return !(first > second);
}


BigInteger& BigInteger::operator=(const BigInteger& first) {
    number = first.number;
    return *this;
}

BigInteger& BigInteger::operator++() {
    int i, n = number.size();
    for (i = 0; i < n && number[i] == 9;i++)
        number[i] = 0;
    if (i == n)
        number.push_back(1);
    else
        number[i]++;
    return *this;
}
BigInteger BigInteger::operator++(int temp) {
    BigInteger aux;
    aux = *this;
    ++(*this);
    return aux;
}

BigInteger& BigInteger::operator--() {
    if (number[0] == 0 && number.size() == 1)
        throw("UNDERFLOW");
    int i, n = number.size();
    for (i = 0; number[i] == 0 && i < n;i++)
        number[i] = 9;
    number[i]--;
    if (n > 1 && number[n - 1] == 0)
        number.pop_back();
    return *this;
}
BigInteger BigInteger::operator--(int temp) {
    BigInteger aux;
    aux = *this;
    --(*this);
    return aux;
}

BigInteger& operator+=(BigInteger& a, const BigInteger& b) {
    int t = 0, s, i;
    int n = Length(a), m = Length(b);
    if (m > n)
        a.number.append(m - n, 0);
    n = Length(a);
    for (i = 0; i < n;i++) {
        if (i < m)
            s = (a.number[i] + b.number[i]) + t;
        else
            s = a.number[i] + t;
        t = s / 10;
        a.number[i] = (s % 10);
    }
    if (t)
        a.number.push_back(t);
    return a;
}
BigInteger operator+(const BigInteger& first, const BigInteger& second) {
    BigInteger tmp;
    tmp = first;
    tmp += second;
    return tmp;
}

BigInteger& operator-=(BigInteger& a, const BigInteger& b) {
    if (a < b)
        throw("UNDERFLOW");
    int n = Length(a), m = Length(b);
    int i, t = 0, s;
    for (i = 0; i < n;i++) {
        if (i < m)
            s = a.number[i] - b.number[i] + t;
        else
            s = a.number[i] + t;
        if (s < 0)
            s += 10,
            t = -1;
        else
            t = 0;
        a.number[i] = s;
    }
    while (n > 1 && a.number[n - 1] == 0)
        a.number.pop_back(),
        n--;
    return a;
}
// Оператор вычитания
BigInteger operator-(const BigInteger& a, const BigInteger& b) {
    BigInteger temp;
    temp = a;
    temp -= b;
    return temp;
}
// Оператор умножения
BigInteger& operator*=(BigInteger& a, const BigInteger& b)
{
    if (Null(a) || Null(b)) {
        a = BigInteger();
        return a;
    }
    int n = a.number.size(), m = b.number.size();
    vector<int> v(n + m, 0);
    for (int i = 0; i < n;i++)
        for (int j = 0; j < m;j++) {
            v[i + j] += (a.number[i]) * (b.number[j]);
        }
    n += m;
    a.number.resize(v.size());
    for (int s, i = 0, t = 0; i < n; i++)
    {
        s = t + v[i];
        v[i] = s % 10;
        t = s / 10;
        a.number[i] = v[i];
    }
    for (int i = n - 1; i >= 1 && !v[i];i--)
        a.number.pop_back();
    return a;
}
BigInteger operator*(const BigInteger& a, const BigInteger& b) {
    BigInteger temp;
    temp = a;
    temp *= b;
    return temp;
}

BigInteger& operator/=(BigInteger& a, const BigInteger& b) {
    if (Null(b))
        throw("Arithmetic Error: Division By 0");
    if (a < b) {
        a = BigInteger();
        return a;
    }
    if (a == b) {
        a = BigInteger(1);
        return a;
    }
    int i, lgcat = 0, cc;
    int n = Length(a), m = Length(b);
    vector<int> cat(n, 0);
    BigInteger t;
    for (i = n - 1; t * 10 + a.number[i] < b;i--) {
        t *= 10;
        t += a.number[i];
    }
    for (; i >= 0; i--) {
        t = t * 10 + a.number[i];
        for (cc = 9; cc * b > t;cc--);
        t -= cc * b;
        cat[lgcat++] = cc;
    }
    a.number.resize(cat.size());
    for (i = 0; i < lgcat;i++)
        a.number[i] = cat[lgcat - i - 1];
    a.number.resize(lgcat);
    return a;
}
BigInteger operator/(const BigInteger& a, const BigInteger& b) {
    BigInteger temp;
    temp = a;
    temp /= b;
    return temp;
}

BigInteger& operator%=(BigInteger& a, const BigInteger& b) {
    if (Null(b))
        throw("Arithmetic Error: Division By 0");
    if (a < b) {
        return a;
    }
    if (a == b) {
        a = BigInteger();
        return a;
    }
    int i, lgcat = 0, cc;
    int n = Length(a), m = Length(b);
    vector<int> cat(n, 0);
    BigInteger t;
    for (i = n - 1; t * 10 + a.number[i] < b;i--) {
        t *= 10;
        t += a.number[i];
    }
    for (; i >= 0; i--) {
        t = t * 10 + a.number[i];
        for (cc = 9; cc * b > t;cc--);
        t -= cc * b;
        cat[lgcat++] = cc;
    }
    a = t;
    return a;
}
BigInteger operator%(const BigInteger& a, const BigInteger& b) {
    BigInteger temp;
    temp = a;
    temp %= b;
    return temp;
}
void divide_by_2(BigInteger& a) {
    int add = 0;
    for (int i = a.number.size() - 1; i >= 0;i--) {
        int digit = (a.number[i] >> 1) + add;
        add = ((a.number[i] & 1) * 5);
        a.number[i] = digit;
    }
    while (a.number.size() > 1 && !a.number.back())
        a.number.pop_back();
}
// Корень
BigInteger sqrt(BigInteger& a) {
    BigInteger left(1), right(a), v(1), mid, prod;
    divide_by_2(right);
    while (left <= right) {
        mid += left;
        mid += right;
        divide_by_2(mid);
        prod = (mid * mid);
        if (prod <= a) {
            v = mid;
            ++mid;
            left = mid;
        }
        else {
            --mid;
            right = mid;
        }
        mid = BigInteger();
    }
    return v;
}
// Вывод
istream& operator>>(istream& in, BigInteger& a) {
    string s;
    in >> s;
    int n = s.size();
    for (int i = n - 1; i >= 0;i--) {
        if (!isdigit(s[i]))
            throw("Не число");
        a.number[n - i - 1] = s[i];
    }
    return in;
}

ostream& operator<<(ostream& out, const BigInteger& a) {
    for (int i = a.number.size() - 1; i >= 0;i--)
        cout << (short)a.number[i];
    return cout;
}

BigInteger Factorial(int n) {
    BigInteger f(1);
    for (int i = 2; i <= n;i++)
        f *= i;
    return f;
}

int main()
{
    BigInteger first("12345");
    cout << "The number of number"
        << " in first big integer = "
        << Length(first) << '\n';
    BigInteger second(12345);
    if (first == second) {
        cout << "first and second are equal!\n";
    }
    else
        cout << "Not equal!\n";
    BigInteger third("10000");
    BigInteger fourth("100000");
    if (third < fourth) {
        cout << "third is smaller than fourth!\n";
    }
    BigInteger fifth("10000000");
    if (fifth > fourth) {
        cout << "fifth is larger than fourth!\n";
    }

    // Printing all the numbers
    cout << "first = " << first << '\n';
    cout << "second = " << second << '\n';
    cout << "third = " << third << '\n';
    cout << "fourth = " << fourth << '\n';
    cout << "fifth = " << fifth << '\n';

    // Incrementing the value of first
    first++;
    cout << "After incrementing the"
        << " value of first is : ";
    cout << first << '\n';
    BigInteger sum;
    sum = (fourth + fifth);
    cout << "Sum of fourth and fifth = "
        << sum << '\n';
    BigInteger product;
    product = second * third;
    cout << "Product of second and third = "
        << product << '\n';

    // Print the fibonacci number from 1 to 100
    cout << "-------------------------Fibonacci"
        << "------------------------------\n";
    for (int i = 0; i <= 100; i++) {
        BigInteger Fib;
        Fib = NthFibonacci(i);
        cout << "Fibonacci " << i << " = " << Fib << '\n';
    }
}
