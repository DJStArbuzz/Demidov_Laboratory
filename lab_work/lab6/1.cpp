#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

class BigInteger
{
private:
    string numBI;  // Число
    bool negaFlag; // Наличие унарного минуса

public:
    // Конструкторы
    BigInteger();
    BigInteger(int num);
    BigInteger(long long num);
    BigInteger(string num);
    ~BigInteger();

    // Константы
    static const BigInteger ZERO;
    static const BigInteger ONE;
    static const BigInteger TEN;
    static const string baseChar;

    BigInteger addition(const BigInteger& numTmp) const;
    BigInteger substraction(const BigInteger& numTmp) const;
    BigInteger multiplication(const BigInteger& numTmp) const;
    BigInteger division(const BigInteger& numTmp) const;

    // 1. Операции 
    BigInteger operator+(const BigInteger& numTmp);
    BigInteger& operator+=(const BigInteger& numTmp);
    BigInteger operator-(const BigInteger& numTmp);
    BigInteger& operator-=(const BigInteger& numTmp);
    BigInteger operator*(const BigInteger& numTmp);
    BigInteger& operator*=(const BigInteger& numTmp);
    BigInteger operator/(const BigInteger& numTmp);
    BigInteger& operator/=(const BigInteger& numTmp);
    BigInteger operator%(const BigInteger& numTmp);
    
    // 2. Префиксный и постфискный инкремент и декремент
    BigInteger& operator++(); // преф
    BigInteger operator++(int); // пост
    BigInteger& operator--(); // преф
    BigInteger operator--(int); // пост

    // 3. Операторы сравнения
    bool operator==(const BigInteger& numTmp) const;
    bool operator!=(const BigInteger& numTmp) const;
    bool operator<(const BigInteger& numTmp) const;
    bool operator>(const BigInteger& numTmp) const;
    bool operator<=(const BigInteger& numTmp) const;
    bool operator>=(const BigInteger& numTmp) const;
    
    // 4. Вывод в поток и ввод из потока 
    friend ostream& operator<<(ostream& out, const BigInteger& numTmp) {
        out << numTmp.toString();
        return out;
    }
    friend istream& operator>>(istream& in, const BigInteger& numTmp) {
    }
    void setNum(string tmpBI) { numBI = tmpBI; }

    // 5. Метод toString
    string toString() const;

    // Доп. операции
    int compare(const BigInteger& numTmp) const;
    bool isPositive() const;
    bool isNegative() const;
    void swap(BigInteger& numTmp);
    BigInteger modulus(const BigInteger& numTmp) const;
    BigInteger negate() const;
    BigInteger absolute() const;
};
istream& operator >> (istream& in, BigInteger& tmp)
{
    string name;
    in >> name;
    tmp.setNum(name);
    return in;
}
// Константы "0", "1", "10"
const BigInteger BigInteger::ZERO = BigInteger("0");
const BigInteger BigInteger::ONE = BigInteger("1");
const BigInteger BigInteger::TEN = BigInteger("10");
// Конструктор по умолчанию
BigInteger::BigInteger()
    : numBI("0"),
    negaFlag(false){}
// Конструктор с int-переменной
BigInteger::BigInteger(int num)
    : negaFlag(num < 0)
{
    string strNum = to_string(num);
    if (negaFlag) {
        strNum.erase(0, 1);
    }
    numBI = strNum;
}
// Конструктор с long long-переменной
BigInteger::BigInteger(long long num)
    : negaFlag(num < 0){
    string strNum = to_string(num);
    if (negaFlag) {
        strNum.erase(0, 1);
    }

    numBI = strNum;
}
// Конструктор с string-переменной
BigInteger::BigInteger(string num)
: negaFlag(num[0] == '-')
{
    if (negaFlag) {
        num.erase(0, 1);
    }
    while (num[0] == '0' && num.length() != 1) {
        num.erase(0, 1);
    }
    numBI = num;
}
// Деструктор
BigInteger::~BigInteger(){}
// Сложение
BigInteger BigInteger::addition(const BigInteger& numTmp) const
{
    BigInteger result;
    // Случай (-A) + B
    if (this->negaFlag && !numTmp.negaFlag) {
        result = numTmp.substraction(negate());
    }
    // Случай A + (-B)
    else if (!this->negaFlag && numTmp.negaFlag) {
        result = substraction(numTmp.negate());
    }
    // Случай A + B || -(A) + (-B)
    else {
        string tmpNum = numTmp.numBI;
        string tmp2 = this->numBI;
        int lenDif = abs(int(tmp2.length() - tmpNum.length()));
        if (tmp2.length() > tmpNum.length()) {
            tmpNum.insert(0, lenDif, '0');
        }
        else {
            tmp2.insert(0, lenDif, '0');
        }

        reverse(tmp2.begin(), tmp2.end());
        reverse(tmpNum.begin(), tmpNum.end());
        char carry = '0';

        int index = 0;
        for (char& s : tmp2) {
            s = (carry - '0') + (s - '0') + (tmpNum.at(index) - '0') + '0';
            if (s > '9') {
                s -= 10;
                carry = '1';
            }
            else {
                carry = '0';
            }
            index++;
        }
        if (carry > '0') {
            tmp2.append(1, carry);
        }
        reverse(tmp2.begin(), tmp2.end());
        result = (this->negaFlag ? BigInteger(tmp2).negate() : BigInteger(tmp2));
    }
    return result;
}
// Вычитание
BigInteger BigInteger::substraction(const BigInteger& numTmp) const
{
    BigInteger substractionion;
    // Случай (-A) - (+B)
    if (this->negaFlag && !numTmp.negaFlag) {
        substractionion = addition(numTmp.negate());
    }
    // Случай (+A) - (-B)
    else if (!this->negaFlag && numTmp.negaFlag) {
        // (+a)-(-b)
        substractionion = addition(numTmp.negate());
    }
    // Случай (+A) - (+B) || (-A) - (-B)
    else {
        if (this->negaFlag) {
            substractionion = addition(numTmp.negate());
        }
        else {
            bool invert_sign = (compare(numTmp) == -1);
            string sub = (invert_sign ? numTmp.numBI : this->numBI);
            string removed = (invert_sign ? this->numBI : numTmp.numBI);

            int diffLength = abs(int(sub.length() - removed.length()));
            if (sub.size() > removed.size()) {
                removed.insert(0, diffLength, '0');
            }
            else {
                sub.insert(0, diffLength, '0');
            }
            reverse(sub.begin(), sub.end());
            reverse(removed.begin(), removed.end());

            int index = 0;
            for (char& c : sub) {
                if (c < removed.at(index)) {
                    c += 10;
                    sub[index + 1]--;
                }
                c = (c - '0') - (removed.at(index) - '0') + '0';
                index++;
            }
            reverse(sub.begin(), sub.end());
            while (sub.front() == '0' && sub.length() != 1) {
                sub.erase(0, 1);
            }
            substractionion = (invert_sign ? BigInteger(sub).negate() : BigInteger(sub));
        }
    }
    return substractionion;
}
// Умножение
BigInteger BigInteger::multiplication(const BigInteger& numTmp) const
{
    BigInteger multiplication;
    string mul = this->numBI;
    string multiplied = numTmp.numBI;
    reverse(mul.begin(), mul.end());
    reverse(multiplied.begin(), multiplied.end());
    int step = 0;
    char carry = '0';
    for (const char& c1 : mul) {
        string cur_op;
        cur_op.insert(0, step, '0');
        for (const char& c2 : multiplied) {
            unsigned char val = ((c1 - '0') * (c2 - '0')) + (carry - '0') + '0';
            carry = '0';
            if (val > '9') {
                while (val > '9') {
                    val -= 10;
                    carry++;
                }
            }
            cur_op.insert(0, 1, val);
        }
        if (carry > '0') {
            cur_op.insert(0, 1, carry);
            carry = '0';
        }
        multiplication += BigInteger(cur_op);
        step++;
    }
    bool positive = (this->negaFlag && numTmp.negaFlag) || (!this->negaFlag && !numTmp.negaFlag);
    if (!positive) {
        multiplication = multiplication.negate();
    }
    return multiplication;
}
// Деление
BigInteger BigInteger::division(const BigInteger& numTmp) const
{
    BigInteger division;
    if (numTmp == ZERO) {
        // Деление на нуль невозможно
    }
    else if (numTmp == ONE) {
        division = (*this);
    }
    else if (compare(numTmp) == 0) {
        division = 1;
    }
    else {
        string divisionnd = this->numBI;
        string quotient, cur_quotient;
        reverse(divisionnd.begin(), divisionnd.end());
        BigInteger numTmp_abs = numTmp.absolute();
        do {
            cur_quotient.push_back(divisionnd.back());
            divisionnd.pop_back();
            BigInteger numTmp_divisionnd(cur_quotient);
            if (numTmp_divisionnd >= numTmp_abs) {
                BigInteger n = BigInteger(2);
                while (numTmp_abs.multiplication(n) <= numTmp_divisionnd) {
                    n++;
                }
                n--;
                quotient.append(n.toString());
                cur_quotient = numTmp_divisionnd.substraction(numTmp_abs.multiplication(n)).toString();
            }
            else {
                quotient.push_back('0');
            }
        } while (!divisionnd.empty());
        division = BigInteger(quotient);
    }
    bool positive = (this->negaFlag && numTmp.negaFlag) || (!this->negaFlag && !numTmp.negaFlag);
    if (!positive) {
        division = division.negate();
    }
    return division;
}

BigInteger BigInteger::modulus(const BigInteger& numTmp) const
{
    BigInteger mod = substraction(numTmp.multiplication(division(numTmp)));
    return mod;
}

int BigInteger::compare(const BigInteger& numTmp) const
{
    int result;
    if (this->negaFlag && !numTmp.negaFlag) {
        // Случай -А, +Б
        result = -1;
    }
    else if (!this->negaFlag && numTmp.negaFlag) {
        // Случай +А, -Б
        result = 1;
    }
    else {
        // +a, +b or -a, -b
        if (this->numBI.length() < numTmp.numBI.length()) {
            result = -1;
        }
        else if (this->numBI.length() > numTmp.numBI.length()) {
            result = 1;
        }
        else {
            bool positive = !this->negaFlag;
            if (this->numBI < numTmp.numBI) {
                result = (positive ? -1 : 1);
            }
            else if (this->numBI > numTmp.numBI) {
                result = (positive ? 1 : -1);;
            }
            else {
                result = 0;
            }
        }
    }
    return result;
}

BigInteger BigInteger::negate() const
{
    string num = this->numBI;
    return BigInteger((this->negaFlag ? num : num.insert(0, 1, '-')));
}

BigInteger BigInteger::absolute() const
{
    return (isPositive() ? (*this) : negate());
}

bool BigInteger::isPositive() const
{
    return !this->negaFlag;
}

bool BigInteger::isNegative() const
{
    return this->negaFlag;
}

void BigInteger::swap(BigInteger& numTmp)
{
    BigInteger tmp = (*this);
    (*this) = numTmp;
    numTmp = tmp;
}

BigInteger BigInteger::operator+(const BigInteger& numTmp)
{
    return this->addition(numTmp);
}

BigInteger BigInteger::operator-(const BigInteger& numTmp)
{
    return this->substraction(numTmp);
}

BigInteger BigInteger::operator*(const BigInteger& numTmp)
{
    return this->multiplication(numTmp);
}

BigInteger BigInteger::operator/(const BigInteger& numTmp)
{
    return this->division(numTmp);
}

BigInteger BigInteger::operator%(const BigInteger& numTmp)
{
    return this->modulus(numTmp);
}


BigInteger& BigInteger::operator+=(const BigInteger& numTmp)
{
    (*this) = addition(numTmp);
    return (*this);
}

BigInteger& BigInteger::operator-=(const BigInteger& numTmp)
{
    (*this) = substraction(numTmp);
    return (*this);
}

BigInteger& BigInteger::operator*=(const BigInteger& numTmp)
{
    (*this) = multiplication(numTmp);
    return (*this);
}

BigInteger& BigInteger::operator/=(const BigInteger& numTmp)
{
    (*this) = division(numTmp);
    return (*this);
}

BigInteger& BigInteger::operator--()
{
    (*this) = substraction(ONE);
    return (*this);
}

BigInteger BigInteger::operator--(int)
{
    BigInteger before_minus = (*this);
    (*this) = substraction(ONE);
    return before_minus;
}

BigInteger& BigInteger::operator++()
{
    (*this) = addition(ONE);
    return (*this);
}

BigInteger BigInteger::operator++(int)
{
    BigInteger before_plus = (*this);
    (*this) = addition(ONE);
    return before_plus;
}

bool BigInteger::operator==(const BigInteger& numTmp) const
{
    bool equal = (compare(numTmp) == 0);
    return equal;
}

bool BigInteger::operator!=(const BigInteger& numTmp) const
{
    bool different = (compare(numTmp) != 0);
    return different;
}

bool BigInteger::operator<(const BigInteger& numTmp) const
{
    bool less = (compare(numTmp) == -1);
    return less;
}

bool BigInteger::operator>(const BigInteger& numTmp) const
{
    bool more = (compare(numTmp) == 1);
    return more;
}

bool BigInteger::operator<=(const BigInteger& numTmp) const
{
    int cmp = compare(numTmp);
    return (cmp == -1) || (cmp == 0);
}

bool BigInteger::operator>=(const BigInteger& numTmp) const
{
    int cmp = compare(numTmp);
    return (cmp == 0) || (cmp == 1);
}

string BigInteger::toString() const
{
    stringstream ss;
    if (negaFlag) {
        ss << '-';
    }
    ss << numBI;
    return ss.str();
}

// Дополнительная функция
BigInteger Factorial(int n) {
    BigInteger f(1);
    for (int i = 2; i <= n;i++)
        f *= i;
    return f;
}

using namespace std;

int main()
{
    BigInteger n("1000"), n2("56");
    cout << n2 - n << endl;
    cout << n2 + n << endl;
    cout << n - n2 << endl;
    cout << n / n2 << endl;
    BigInteger n3("-100");
    cout << n3;
    BigInteger n4;
    cin >> n4;
    cout << n4;
    cout << "Fact" << endl;
    for (int i = 0; i <= 20; i++) {
        BigInteger Fib;
        Fib = Factorial(i);
        cout << "Fibonacci " << i << " = " << Fib << '\n';
    }
    return 0;
}