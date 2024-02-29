#include <iostream>
#include <string>
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
    BigInteger(int numBI);
    BigInteger(long long numBi);
    BigInteger(string numBi);
    ~BigInteger();

    // Константы
    static const BigInteger ZERO;
    static const BigInteger ONE;
    static const BigInteger NONE;

    // Операции 
    BigInteger operator+(const BigInteger& numTmp);
    BigInteger& operator+=(const BigInteger& numTmp);
    BigInteger operator-(const BigInteger& numTmp);
    BigInteger& operator-=(const BigInteger& numTmp);
    BigInteger operator*(const BigInteger& numTmp);
    BigInteger& operator*=(const BigInteger& numTmp);
    BigInteger operator/(const BigInteger& numTmp);
    BigInteger& operator/=(const BigInteger& numTmp);
    BigInteger operator%(const BigInteger& numTmp);

    BigInteger addition(const BigInteger& numTmp) const;
    BigInteger substraction(const BigInteger& numTmp) const;
    BigInteger multiplication(const BigInteger& numTmp) const;
    BigInteger division(const BigInteger& numTmp) const;

    // Префиксный и постфискный инкремент и декремент
    BigInteger& operator++(); // преф
    BigInteger operator++(int); // пост
    BigInteger& operator--(); // преф
    BigInteger operator--(int); // пост

    // Операторы сравнения
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
    friend istream& operator>>(istream& in, const BigInteger& numTmp) {}
    void setNum(string tmpBI) { numBI = tmpBI; }

    // Метод toString
    string toString() const {
        if (numBI == "0") {
            return "0";
        }

        string s = "";
        if (negaFlag) {
            s = "-";
        }
        return s + numBI;
    };

    // Доп. операции
    int compare(const BigInteger& numTmp) const;
    bool isPositive() const;
    bool isNegative() const;
    void swap(BigInteger& numTmp);
    BigInteger modulus(const BigInteger& numTmp) const;
    BigInteger negate() const;
    BigInteger absolute() const;

    explicit operator bool() const {
        return (numBI.front() != '0');
    }
};
istream& operator >> (istream& in, BigInteger& tmp)
{
    string num;
    in >> num;
    tmp.setNum(num);
    return in;
}
// Константы "0", "1", "10"
const BigInteger BigInteger::ZERO = BigInteger("0");
const BigInteger BigInteger::ONE = BigInteger("1");
const BigInteger BigInteger::NONE = BigInteger("NONE");
// Конструктор по умолчанию
BigInteger::BigInteger()
    : numBI("0"),
    negaFlag(false) {}
// Конструктор с int-переменной
BigInteger::BigInteger(int num)
    : negaFlag(num < 0) {
    string strNum = to_string(num);
    if (negaFlag) {
        strNum.erase(0, 1);
    }
    numBI = strNum;
}
// Конструктор с long long-переменной
BigInteger::BigInteger(long long num)
    : negaFlag(num < 0) {
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
BigInteger::~BigInteger() {}
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
            s = (carry - '0') + (s - '0') + (tmpNum[index] - '0') + '0';
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
    BigInteger result;
    // Случай (-A) - (+B)
    if (this->negaFlag && !numTmp.negaFlag) {
        result = addition(numTmp.negate());
    }
    // Случай (+A) - (-B)
    else if (!this->negaFlag && numTmp.negaFlag) {
        result = addition(numTmp.negate());
    }
    // Случай (+A) - (+B) || (-A) - (-B)
    else {
        if (this->negaFlag) {
            result = addition(numTmp.negate());
        }
        else {
            bool flag = (compare(numTmp) == -1);
            string sub = (flag ? numTmp.numBI : this->numBI);
            string removed = (flag ? this->numBI : numTmp.numBI);

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
                if (c < removed[index]) {
                    c += 10;
                    sub[index + 1]--;
                }
                c = (c - '0') - (removed[index] - '0') + '0';
                index++;
            }
            reverse(sub.begin(), sub.end());
            while (sub.front() == '0' && sub.length() != 1) {
                sub.erase(0, 1);
            }
            result = (flag ? BigInteger(sub).negate() : BigInteger(sub));
        }
    }
    return result;
}
// Умножение
BigInteger BigInteger::multiplication(const BigInteger& numTmp) const
{
    BigInteger result;

    string mulTmp = this->numBI;
    string mul = numTmp.numBI;
    reverse(mulTmp.begin(), mulTmp.end());
    reverse(mul.begin(), mul.end());

    int step = 0;
    char carry = '0';
    for (const char& c1 : mulTmp) {
        string curr;
        curr.insert(0, step, '0');

        for (const char& c2 : mul) {
            unsigned char val = ((c1 - '0') * (c2 - '0')) + (carry - '0') + '0';
            carry = '0';
            if (val > '9') {
                while (val > '9') {
                    val -= 10;
                    carry++;
                }
            }
            curr.insert(0, 1, val);
        }
        if (carry > '0') {
            curr.insert(0, 1, carry);
            carry = '0';
        }
        result += BigInteger(curr);
        step++;
    }

    bool flagPo = (this->negaFlag && numTmp.negaFlag) || (!this->negaFlag && !numTmp.negaFlag);
    if (!flagPo) {
        result = result.negate();
    }
    return result;
}
// Деление
BigInteger BigInteger::division(const BigInteger& numTmp) const
{
    BigInteger result;

    if (numTmp == ZERO || numTmp == NONE || (*this) == NONE) {
        return NONE;
    }
    else if (numTmp == ONE) {
        result = (*this);
    }
    else if (compare(numTmp) == 0) {
        result = 1;
    }
    else {
        string div = this->numBI, quo, curQuo;
        reverse(div.begin(), div.end());

        BigInteger numTmpAbs = numTmp.absolute();
        while (!div.empty()) {
            curQuo.push_back(div.back());
            div.pop_back();

            BigInteger divTmp(curQuo);
            if (divTmp >= numTmpAbs) {
                BigInteger n = BigInteger(2);
                while (numTmpAbs.multiplication(n) <= divTmp) {
                    n++;
                }
                n--;
                quo.append(n.toString());
                curQuo = divTmp.substraction(numTmpAbs.multiplication(n)).toString();
            }
            else {
                quo.push_back('0');
            }
        }
        result = BigInteger(quo);
    }

    bool flagPo = (this->negaFlag && numTmp.negaFlag)
        || (!this->negaFlag && !numTmp.negaFlag);
    if (!flagPo) {
        result = result.negate();
    }
    return result;
}

BigInteger BigInteger::modulus(const BigInteger& numTmp) const
{
    BigInteger n1 = (*this), n2 = numTmp, mod;

    if (numTmp == ZERO) {
        return BigInteger("None");
    }
    mod = substraction(numTmp.multiplication(division(numTmp)));
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
        // Случай +A, +B || -A, -B
        if (this->numBI.length() < numTmp.numBI.length()) {
            result = -1;
        }
        else if (this->numBI.length() > numTmp.numBI.length()) {
            result = 1;
        }
        else {
            bool flagPo = !this->negaFlag;
            if (this->numBI < numTmp.numBI) {
                result = (flagPo ? -1 : 1);
            }
            else if (this->numBI > numTmp.numBI) {
                result = (flagPo ? 1 : -1);
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
// Сложение
BigInteger BigInteger::operator+(const BigInteger& numTmp)
{
    return this->addition(numTmp);
}
BigInteger& BigInteger::operator+=(const BigInteger& numTmp)
{
    (*this) = addition(numTmp);
    return (*this);
}
// Разность
BigInteger BigInteger::operator-(const BigInteger& numTmp)
{
    return this->substraction(numTmp);
}
BigInteger& BigInteger::operator-=(const BigInteger& numTmp)
{
    (*this) = substraction(numTmp);
    return (*this);
}
// Умножение
BigInteger BigInteger::operator*(const BigInteger& numTmp)
{
    return this->multiplication(numTmp);
}
BigInteger& BigInteger::operator*=(const BigInteger& numTmp)
{
    (*this) = multiplication(numTmp);
    return (*this);
}
// Деление
BigInteger BigInteger::operator/(const BigInteger& numTmp)
{
    return this->division(numTmp);
}
BigInteger& BigInteger::operator/=(const BigInteger& numTmp)
{
    (*this) = division(numTmp);
    return (*this);
}
// Остаток
BigInteger BigInteger::operator%(const BigInteger& numTmp)
{
    return this->modulus(numTmp);
}
// Декремент - префиксный и постфискный
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
// Инкремент - префиксный и постфискный
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
// Операторы сравнения
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
// Дополнительная функция - Факториал
BigInteger Factorial(int n) {
    BigInteger f(1);
    for (int i = 2; i <= n; i++)
        f *= i;
    return f;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    cout << "Лабораторная работа №6\n";
    BigInteger n1("-1001"), n2("3"), n3("-100"), n4("0");

    cout << "n2 + n1 = " << n1 + n2 << endl;
    cout << "n1 - n2 = " << n1 - n2 << endl;
    cout << "n2 / n1 = " << n1 / n2 << endl;
    cout << "n2 * n1 = " << n1 * n2 << endl;
    cout << "n2 % n1 = " << n1 % n2 << endl;
    cout << "\n\n\n\n";
    
    BigInteger n22;
    n22 = n3 / n4;
    cout << n22 << endl;
    cout << n22 / n1 << endl;
    cout << n3 / n4 << endl;

    cout << "\n\n\n\n";
    BigInteger n5(10), n6(4);
    cout << "10 % 3: ";
    cout << n5 % n6 << " " << (10) % (4) << endl;
    cout << "\n-10 % 3: ";
    BigInteger n7(-10), n8(4);
    cout << n7 % n8 << " " << (-10) % (4) << endl;
    BigInteger n9(10), n10(-4);
    cout << "\n10 % (-3): ";
    cout << n9 % n10 << " " << (10) % (-4) << endl;
    cout << "\n-10 % (-3): ";
    BigInteger n11(-10), n12(-4);
    cout << n11 % n12 << " " << (-10) % (-4) << endl;

    cout << "Введем еще одно число: ";
    cin >> n3;
    cout << n3 << " / " << 23 << " = " << n3 / 23 << "(" << n3 % 23 << ")" << endl;
    bool flag = bool(n3);
    cout << flag << endl;
    string s = n3.toString();
    cout << s << endl;

    cout << "Факториалы: " << endl;
    for (int i = 0; i <= 20; i++) {
        BigInteger Fib;
        Fib = Factorial(i);
        cout << "Факториал " << i << " = " << Fib << '\n';
    }
    return 0;
}
