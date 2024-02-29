#include <iostream>
#include <string>
#include <vector>

using namespace std;

// 1-ое задание: класс BigInteger
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
    static const BigInteger ZERO_BI;
    static const BigInteger ONE_BI;
    static const BigInteger TEN_BI;
    static const BigInteger NONE_BI;

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
    BigInteger modulus(const BigInteger& numTmp) const;

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
const BigInteger BigInteger::ZERO_BI = BigInteger("0");
const BigInteger BigInteger::ONE_BI = BigInteger("1");
const BigInteger BigInteger::TEN_BI = BigInteger("10");
const BigInteger BigInteger::NONE_BI = BigInteger("NONE_BI");
// Конструктор по умолчанию
BigInteger::BigInteger(): 
    numBI("0"),
    negaFlag(false) {}
// Конструктор с int-переменной
BigInteger::BigInteger(int num): 
    negaFlag(num < 0) {
    string strNum = to_string(num);
    if (negaFlag) {
        strNum.erase(0, 1);
    }
    numBI = strNum;
}
// Конструктор с long long-переменной
BigInteger::BigInteger(long long num): 
    negaFlag(num < 0) {
    string strNum = to_string(num);
    if (negaFlag) {
        strNum.erase(0, 1);
    }
    numBI = strNum;
}
// Конструктор с string-переменной
BigInteger::BigInteger(string num): 
    negaFlag(num[0] == '-')
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
    if (numTmp == NONE_BI || (*this) == NONE_BI) {
        return NONE_BI;
    }
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
    if (numTmp == NONE_BI || (*this) == NONE_BI) {
        return NONE_BI;
    }
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
    if (numTmp == NONE_BI || (*this) == NONE_BI) {
        return NONE_BI;
    }
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

    if (numTmp == ZERO_BI || numTmp == NONE_BI || (*this) == NONE_BI) {
        return NONE_BI;
    }
    else if (numTmp == ONE_BI) {
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

    if (numTmp == ZERO_BI) {
        return BigInteger("NONE_BI");
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
    (*this) = substraction(ONE_BI);
    return (*this);
}
BigInteger BigInteger::operator--(int)
{
    BigInteger before_minus = (*this);
    (*this) = substraction(ONE_BI);
    return before_minus;
}
// Инкремент - префиксный и постфискный
BigInteger& BigInteger::operator++()
{
    (*this) = addition(ONE_BI);
    return (*this);
}
BigInteger BigInteger::operator++(int)
{
    BigInteger before_plus = (*this);
    (*this) = addition(ONE_BI);
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

// 2-ое задание: класс BigRational
class BigRational
{
private:
    string numeratorBR;    // Числитель числа
    string denominatorBR;  // Знаменатель числа
    bool negaFlag;         // Наличие унарного минуса

public:
    // Конструкторы
    BigRational();
    BigRational(int numeratorBR, int denominatorBR);
    BigRational(long long numeratorBR, long long denominatorBR);
    BigRational(string numeratorBR, string denominatorBR);
    BigRational(BigInteger numeratorBR, BigInteger denominatorBR);
    ~BigRational();

    // Константы
    static const BigRational ZERO_BR;
    static const BigRational ONE_BR;
    static const BigRational NONE_BR;

    // Операции 
    BigRational operator+(const BigRational& numTmp);
    BigRational& operator+=(const BigRational& numTmp);
    BigRational operator-(const BigRational& numTmp);
    BigRational& operator-=(const BigRational& numTmp);
    BigRational operator*(const BigRational& numTmp);
    BigRational& operator*=(const BigRational& numTmp);
    BigRational operator/(const BigRational& numTmp);
    BigRational& operator/=(const BigRational& numTmp);

    BigRational addition(const BigRational& numTmp) const;
    BigRational substraction(const BigRational& numTmp) const;
    BigRational multiplication(const BigRational& numTmp) const;
    BigRational division(const BigRational& numTmp) const;

    // Операторы сравнения
    bool operator==(const BigRational& numTmp) const;
    bool operator!=(const BigRational& numTmp) const;
    bool operator<(const BigRational& numTmp) const;
    bool operator>(const BigRational& numTmp) const;
    bool operator<=(const BigRational& numTmp) const;
    bool operator>=(const BigRational& numTmp) const;

    // 4. Вывод в поток и ввод из потока 
    friend ostream& operator<<(ostream& out, const BigRational& numTmp) {
        out << numTmp.toString();
        return out;
    }
    friend istream& operator>>(istream& in, const BigRational& numTmp) {}
    void setNum(string numeratorTmpBR, string denominatorTmpBR)
    { 
        numeratorBR = numeratorTmpBR; 
        denominatorBR = denominatorTmpBR;
    }

    // Метод toString
    string toString() const {
        if (numeratorBR == "0") {
            return "0/1";
        }
        string res = "";
        if (negaFlag) {
            res = "-";
        }
        res += numeratorBR + '/' + denominatorBR;
        return res;
    };

    // Доп. операции
    int compare(const BigRational& numTmp) const;
    bool isPositive() const;
    bool isNegative() const;
    void swap(BigRational& numTmp);
    string asDecimal(int precision = 0);
    string toString();
    double toDouble();
    BigRational negate() const;
    BigRational absolute() const;
};

istream& operator>> (istream& in, BigRational& tmp)
{
    string num;
    in >> num;

    string resNum = "", resDet = "1";
    bool flag = true;
    for (char& c : num) {
        if (c == '.') {
            flag = false;
        }
        else {
            if (flag) {
                resNum += c;
            }
            else {
                resNum += c;
                resDet += '0';
            }
        }
    }

    tmp.setNum(resNum, resDet);
    return in;
}
// Константы "0", "1", "10"
const BigRational BigRational::ZERO_BR = BigRational("0", "1");
const BigRational BigRational::ONE_BR = BigRational("1", "1");
const BigRational BigRational::NONE_BR = BigRational("NONE_BR", "NONE_BR");

BigRational::BigRational(): 
    numeratorBR("0"),
    denominatorBR("1"),
    negaFlag(false) {}
// Конструктор с double-переменной
BigRational::BigRational(int num, int den): 
    negaFlag((num < 0 && den > 0) || (num > 0 && den < 0))
{
    string strNum = to_string(num),
           strDen = to_string(den);
    
    if (den < 0 && num > 0) {
        strDen.erase(0, 1);
        strNum = '-' + strNum;
    }
    else if (den < 0 && num < 0) {
        strDen.erase(0, 1);
        strNum.erase(0, 1);
    }
    if (negaFlag) {
        strNum.erase(0, 1);
    }
    if (strDen == "0") {
        numeratorBR = "NONE_BR", denominatorBR = "NONE_BR";
    }
    else {
        numeratorBR = strNum, denominatorBR = strDen;
    }
}
// Конструктор с long double-переменной
BigRational::BigRational(long long num, long long den) :
    negaFlag((num < 0 && den > 0) || (num > 0 && den < 0))
{
    string strNum = to_string(num),
        strDen = to_string(den);

    if (den < 0 && num > 0) {
        strDen.erase(0, 1);
        strNum = '-' + strNum;
    }
    else if (den < 0 && num < 0) {
        strDen.erase(0, 1);
        strNum.erase(0, 1);
    }

    if (negaFlag) {
        strNum.erase(0, 1);
    }
    if (strDen == "0") {
        numeratorBR = "NONE_BR", denominatorBR = "NONE_BR";
    }
    else {
        numeratorBR = strNum, denominatorBR = strDen;
    }
}
// Конструктор с BigInteger-переменной
BigRational::BigRational(BigInteger num, BigInteger den) :
    negaFlag((num < 0 && den > 0) || (num > 0 && den < 0))
{
    string strNum = num.toString(),
        strDen = den.toString();

    if (den < 0 && num > 0) {
        strDen.erase(0, 1);
        strNum = '-' + strNum;
    }
    else if (den < 0 && num < 0) {
        strDen.erase(0, 1);
        strNum.erase(0, 1);
    }
    if (negaFlag) {
        strNum.erase(0, 1);
    }
    if (strDen == "0") {
        numeratorBR = "NONE_BR", denominatorBR = "NONE_BR";
    }
    else {
        numeratorBR = strNum, denominatorBR = strDen;
    }
}
// Конструктор с string-переменной
BigRational::BigRational(string num, string den):
    negaFlag((num[0] == '-' && den[0] != '-') || (num[0] != '-' && den[0] == '-'))
{
    if (den[0] == '-' && num[0] != '-') {
        den.erase(0, 1);
        num = '-' + num;
    }
    else if (den[0] == '-' && num[0] == '-') {
        den.erase(0, 1);
        den.erase(0, 1);
    }
    if (negaFlag) {
        num.erase(0, 1);
    }
    while (num[0] == '0' && num.length() != 1) {
        num.erase(0, 1);
    }

    if (den == "0") {
        numeratorBR = "NONE_BR", denominatorBR = "NONE_BR";
    }
    else {
        numeratorBR = num, denominatorBR = den;
    }
}
// Деструктор
BigRational::~BigRational() {}
int BigRational::compare(const BigRational& numTmp) const
{
    int result;

    BigRational n1(this->numeratorBR, this->denominatorBR), n2 = numTmp;
    n1.negaFlag = this->negaFlag;
    
    if (n1.negaFlag && !n2.negaFlag) {
        // Случай -А, +Б
        result = -1;
    }
    else if (!n1.negaFlag && n2.negaFlag) {
        // Случай +А, -Б
        result = 1;
    }
    else {
        // Случай +A, +B || -A, -B
        BigInteger num1 = this->numeratorBR,
            den1 = this->denominatorBR,
            num2 = numTmp.numeratorBR,
            den2 = numTmp.denominatorBR, resNum1, resNum2;

        resNum1 = num1 * den2, resNum2 = num2 * den1;
        string resNumStr1 = resNum1.toString(),
            resNumStr2 = resNum2.toString();

        if (resNumStr1.length() < resNumStr2.length()) {
            result = -1;
        }
        else if (resNumStr1.length() > resNumStr2.length()) {
            result = 1;
        }
        else {
            bool flagPo = !this->negaFlag;
            if (resNumStr1 < resNumStr2) {
                result = (flagPo ? -1 : 1);
            }
            else if (resNumStr1 > resNumStr2) {
                result = (flagPo ? 1 : -1);
            }
            else {
                result = 0;
            }
        }
    }
    return result;
}
// Сложение
BigRational BigRational::addition(const BigRational& numTmp) const
{
    BigRational result;

    if (numTmp == NONE_BR || (*this) == NONE_BR) {
        return NONE_BR;
    }

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
        BigInteger num1 = this->numeratorBR,     
            den1 = this->denominatorBR,
            num2 = numTmp.numeratorBR,       
            den2 = numTmp.denominatorBR, resDen, resNum;

        if (den1 != den2) {
            BigInteger multNum1 = num1 * den2,
                multNum2 = num2 * den1;

            resDen = den1 * den2;
            resNum = multNum1 + multNum2;
        }
        else {
            resDen = den1;
            resNum = num1 + num2;
        }

        BigRational res(resNum, resDen);
        result = res;
        result = (this->negaFlag ? result.negate() : result);
    }
    return result;
}
BigRational BigRational::substraction(const BigRational& numTmp) const
{
    BigRational result;

    if (numTmp == NONE_BR || (*this) == NONE_BR) {
        return NONE_BR;
    }

    //Случай(-A) - (+B)
        if (this->negaFlag && !numTmp.negaFlag) {
            result = addition(numTmp.negate());
        }
    // Случай (+A) - (-B)
        else if (!this->negaFlag && numTmp.negaFlag) {
            result = addition(numTmp.negate());
        }
    // Случай (+A) - (+B) || (-A) - (-B)
    else {
        BigInteger num1 = this->numeratorBR,     
            den1 = this->denominatorBR,
            num2 = numTmp.numeratorBR,       
            den2 = numTmp.denominatorBR, resDen, resNum;

        if (den1 != den2) {
            BigInteger multNum1 = num1 * den2,
                multNum2 = num2 * den1;

            resDen = den1 * den2;
            resNum = multNum1 - multNum2;
        }
        else {
            resDen = den1;
            resNum = num1 - num2;
        }

        BigRational res(resNum, resDen);
        result = res;
        result = (this->negaFlag ? result.negate() : result);

    }
    return result;
}
// Умножение
BigRational BigRational::multiplication(const BigRational& numTmp) const
{
    if (numTmp == NONE_BR || (*this) == NONE_BR) {
        return NONE_BR;
    }

    BigInteger num1 = this->numeratorBR,
        den1 = this->denominatorBR,
        num2 = numTmp.numeratorBR,
        den2 = numTmp.denominatorBR, resDen, resNum;
    
    resNum = num1 * num2;
    resDen = den1 * den2;

    BigRational result(resNum, resDen);
    if ((this->isNegative() && numTmp.isPositive()) ||
        (numTmp.isNegative() && this->isPositive())) {
        result.negaFlag = true;
    }
    else {
        result.negaFlag = false;
    }

    return result;
}
// Деление
BigRational BigRational::division(const BigRational& numTmp) const
{
    if (numTmp == NONE_BR || (*this) == NONE_BR) {
        return NONE_BR;
    }

    BigInteger num1 = this->numeratorBR,
        den1 = this->denominatorBR,
        num2 = numTmp.numeratorBR,
        den2 = numTmp.denominatorBR, resDen, resNum;

    resNum = num1 * den2;
    resDen = den1 * num2;

    BigRational result(resNum, resDen);
    if ((this->isNegative() && numTmp.isPositive()) ||
        (numTmp.isNegative() && this->isPositive())) {
        result.negaFlag = true;
    }
    else {
        result.negaFlag = false;
    }

    return result;
}
BigRational BigRational::negate() const
{
    string num = this->numeratorBR;
    if (!this->negaFlag) {
        num.insert(0, 1, '-');
    }
    BigRational res(num, this->denominatorBR);

    return res;
}

BigRational BigRational::absolute() const
{
    return (isPositive() ? (*this) : negate());
}

bool BigRational::isPositive() const
{
    return !this->negaFlag;
}

bool BigRational::isNegative() const
{
    return this->negaFlag;
}

void BigRational::swap(BigRational& numTmp)
{
    BigRational tmp = (*this);
    (*this) = numTmp;
    numTmp = tmp;
}
// Сложение
BigRational BigRational::operator+(const BigRational& numTmp)
{
    return this->addition(numTmp);
}
BigRational& BigRational::operator+=(const BigRational& numTmp)
{
    (*this) = addition(numTmp);
    return (*this);
}
// Разность
BigRational BigRational::operator-(const BigRational& numTmp)
{
    return this->substraction(numTmp);
}
BigRational& BigRational::operator-=(const BigRational& numTmp)
{
    (*this) = substraction(numTmp);
    return (*this);
}
// Умножение
BigRational BigRational::operator*(const BigRational& numTmp)
{
    return this->multiplication(numTmp);
}
BigRational& BigRational::operator*=(const BigRational& numTmp)
{
    (*this) = multiplication(numTmp);
    return (*this);
}
// Деление
BigRational BigRational::operator/(const BigRational& numTmp)
{
    return this->division(numTmp);
}
BigRational& BigRational::operator/=(const BigRational& numTmp)
{
    (*this) = division(numTmp);
    return (*this);
}
// Операторы сравнения
bool BigRational::operator==(const BigRational& numTmp) const
{
    bool equal = (compare(numTmp) == 0);
    return equal;
}
bool BigRational::operator!=(const BigRational& numTmp) const
{
    bool different = (compare(numTmp) != 0);
    return different;
}
bool BigRational::operator<(const BigRational& numTmp) const
{
    bool less = (compare(numTmp) == -1);
    return less;
}
bool BigRational::operator>(const BigRational& numTmp) const
{
    bool more = (compare(numTmp) == 1);
    return more;
}
bool BigRational::operator<=(const BigRational& numTmp) const
{
    int cmp = compare(numTmp);
    return (cmp == -1) || (cmp == 0);
}
bool BigRational::operator>=(const BigRational& numTmp) const
{
    int cmp = compare(numTmp);
    return (cmp == 0) || (cmp == 1);
}
string BigRational::asDecimal(int precision)
{
    string resultMainPart = "", resFracPart = "";
    BigInteger num(this->numeratorBR), den(this->denominatorBR);
    BigInteger absNum = num.absolute();
    vector<BigInteger> list;

    if (num < BigInteger(0))
    {
        resultMainPart = "-";
    }
    resultMainPart += (absNum / den).toString();
    
    BigInteger fractionalPart = absNum % den;
    if (fractionalPart == BigInteger(0))
    {
        return resultMainPart;
    }
    
    if (fractionalPart != BigInteger(0))
    {
        resultMainPart += ".";
        list.push_back(fractionalPart);
    }

    bool flag = false;
    for (int i = 0; i < precision; i++)
    {
        fractionalPart *= 10;
        resFracPart += (fractionalPart / den).toString();
        fractionalPart = fractionalPart % den;    
        
        if (fractionalPart == 0)
        {
            break;
        }
        
        list.push_back(resFracPart);
    }
    return resultMainPart + resFracPart;
}
string BigRational::toString() {
    string res = this->asDecimal(5);
    return res;
}
double BigRational::toDouble() {
    string str = this->asDecimal(5);

    double result = 0.0;
    double fraction = 1.0;
    bool isNegative = false;

    size_t index = 0;
    if (str[0] == '-') {
        isNegative = true;
        index = 1;
    }
    while (isdigit(str[index])) {
        result = result * 10 + (str[index] - '0');
        index++;
    }
    if (str[index] == '.') {
        index++;
        while (isdigit(str[index])) {
            fraction /= 10;
            result = result + (str[index] - '0') * fraction;
            index++;
        }
    }
    if (isNegative) {
        result *= -1;
    }

    return result;
}
int main()
{
    setlocale(LC_ALL, "Russian");
    cout << "Лабораторная работа №6\nBigInteger:\n";
    BigInteger n1("-1001"), n2("3"), n3("1"), n4("0");

    cout << "n1 + n2 = " << n1 + n2 << endl;
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
    cout << n22 + n4 << endl;

    cout << "\n\n\n\n";

    BigInteger n5(10), n6(3);
    cout << "10 % 3: ";
    cout << n5 % n6 << " " << (10) % (3) << endl;

    BigInteger n7(-10), n8(3);
    cout << "\n-10 % 3: ";
    cout << n7 % n8 << " " << (-10) % (3) << endl;

    BigInteger n9(10), n10(-3);
    cout << "\n10 % (-3): ";
    cout << n9 % n10 << " " << (10) % (-3) << endl;

    BigInteger n11(-10), n12(-3);
    cout << "\n-10 % (-3): ";
    cout << n11 % n12 << " " << (-10) % (-3) << endl;

    cout << "\n\n\n\nBigRational:\n";
    
    BigRational br1(-6, 2), br2(4, 5), br3(1, 3), ad, su, mu, di;
    
    ad = br1 + br2;
    su = br1 - br2;
    mu = br1 * br2;
    di = br1 / br2;

    cout << ad << endl;
    cout << su << endl;
    cout << mu << endl;
    cout << di << endl;

    cout << (br1 > br2) << endl;

    double n = br3.toDouble();
    string s = br3.asDecimal(10);
    cout << s << endl;
    cout << br3.toString() << endl;
    cout << n + 1.5 << endl;

    BigRational a;
    cin >> a;
    cout << a;
    return 0;
}
