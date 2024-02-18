#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <ostream>
#include <sstream>
#include <vector>
#include <cctype>

using namespace std;

class BigInteger
{
public:
    BigInteger();
    BigInteger(int value);
    BigInteger(long long value);
    BigInteger(std::string value);
    ~BigInteger();

    static const BigInteger ZERO;
    static const BigInteger ONE;
    static const BigInteger TEN;
    static const std::string baseChar;

    /**
     * Elementary arithmetic
     */
    BigInteger add(const BigInteger& bi) const;
    BigInteger substract(const BigInteger& bi) const;
    BigInteger multiply(const BigInteger& bi) const;
    BigInteger divide(const BigInteger& bi) const;

    /**
     * Complex arithmetic
     */
    BigInteger pow(const BigInteger& bi) const;
    BigInteger modulus(const BigInteger& bi) const;

    /**
     * Modification & Checking
     */
    int bitLength() const;
    int compare(const BigInteger& bi) const;
    BigInteger negate() const;
    BigInteger absolute() const;
    bool isPositive() const;
    bool isNegative() const;
    void swap(BigInteger& bi);

    /**
     * Operator
     */
    BigInteger operator+(const BigInteger& bi);
    BigInteger operator-(const BigInteger& bi);
    BigInteger operator*(const BigInteger& bi);
    BigInteger operator/(const BigInteger& bi);
    BigInteger operator%(const BigInteger& bi);
    BigInteger operator<<(const BigInteger& bi) const;
    BigInteger operator>>(const BigInteger& bi) const;
    BigInteger& operator+=(const BigInteger& bi);
    BigInteger& operator-=(const BigInteger& bi);
    BigInteger& operator*=(const BigInteger& bi);
    BigInteger& operator/=(const BigInteger& bi);
    BigInteger& operator--(); // pre
    BigInteger operator--(int); // post
    BigInteger& operator++(); // pre
    BigInteger operator++(int); // post
    bool operator==(const BigInteger& bi) const;
    bool operator!=(const BigInteger& bi) const;
    bool operator<(const BigInteger& bi) const;
    bool operator>(const BigInteger& bi) const;
    bool operator<=(const BigInteger& bi) const;
    bool operator>=(const BigInteger& bi) const;
    friend std::ostream& operator<<(std::ostream& stream, const BigInteger& bi) {
        stream << bi.toString();
        return stream;
    }

    std::string toString() const;

private:
    bool m_signed;
    std::string m_value;

};

const BigInteger BigInteger::ZERO = BigInteger("0");
const BigInteger BigInteger::ONE = BigInteger("1");
const BigInteger BigInteger::TEN = BigInteger("10");
// Base 32 max
const std::string BigInteger::baseChar = "0123456789abcdefghijklmnopqrstuv";

BigInteger::BigInteger()
    : m_signed(false)
    , m_value("0")
{

}

BigInteger::BigInteger(int value)
    : m_signed(value < 0)
{
    std::string str_value = std::to_string(value);
    if (m_signed) {
        str_value.erase(0, 1);
    }
    m_value = str_value;
}

BigInteger::BigInteger(long long value)
    : m_signed(value < 0)
{
    std::string str_value = std::to_string(value);
    if (m_signed) {
        str_value.erase(0, 1);
    }
    m_value = str_value;
}

BigInteger::BigInteger(std::string value)
    : m_signed(value.front() == '-')
{
    if (m_signed) {
        value.erase(0, 1);
    }
    // remove leading 0
    while (value.front() == '0' && value.length() != 1) {
        value.erase(0, 1);
    }
    m_value = value;
}

BigInteger::~BigInteger()
{

}

BigInteger BigInteger::add(const BigInteger& bi) const
{
    BigInteger addition;
    if (this->m_signed && !bi.m_signed) {
        // (-a)+(+b)
        addition = bi.substract(negate());
    }
    else if (!this->m_signed && bi.m_signed) {
        // (+a)+(-b)
        addition = substract(bi.negate());
    }
    else {
        // (+a)+(+b) or (-a)+(-b)
        std::string sum = this->m_value;
        std::string added = bi.m_value;
        int diffLength = std::abs(int(sum.length() - added.length()));
        if (sum.length() > added.length()) {
            added.insert(0, diffLength, '0');
        }
        else {
            sum.insert(0, diffLength, '0');
        }
        std::reverse(sum.begin(), sum.end());
        std::reverse(added.begin(), added.end());
        char carry = '0';

        int index = 0;
        for (char& c : sum) {
            c = (carry - '0') + (c - '0') + (added.at(index) - '0') + '0';
            if (c > '9') {
                c -= 10;
                carry = '1';
            }
            else {
                carry = '0';
            }
            index++;
        }
        if (carry > '0') {
            sum.append(1, carry);
        }
        std::reverse(sum.begin(), sum.end());
        addition = (this->m_signed ? BigInteger(sum).negate() : BigInteger(sum));
    }
    return addition;
}

BigInteger BigInteger::substract(const BigInteger& bi) const
{
    BigInteger substraction;
    if (this->m_signed && !bi.m_signed) {
        // (-a)-(+b)
        substraction = add(bi.negate());
    }
    else if (!this->m_signed && bi.m_signed) {
        // (+a)-(-b)
        substraction = add(bi.negate());
    }
    else {
        // (+a)-(+b) or (-a)-(-b)
        if (this->m_signed) {
            substraction = add(bi.negate());
        }
        else {
            bool invert_sign = (compare(bi) == -1);
            std::string sub = (invert_sign ? bi.m_value : this->m_value);
            std::string removed = (invert_sign ? this->m_value : bi.m_value);

            int diffLength = std::abs(int(sub.length() - removed.length()));
            if (sub.size() > removed.size()) {
                removed.insert(0, diffLength, '0');
            }
            else {
                sub.insert(0, diffLength, '0');
            }
            std::reverse(sub.begin(), sub.end());
            std::reverse(removed.begin(), removed.end());

            int index = 0;
            for (char& c : sub) {
                if (c < removed.at(index)) {
                    c += 10;
                    sub[index + 1]--;
                }
                c = (c - '0') - (removed.at(index) - '0') + '0';
                index++;
            }
            std::reverse(sub.begin(), sub.end());
            while (sub.front() == '0' && sub.length() != 1) {
                sub.erase(0, 1);
            }
            substraction = (invert_sign ? BigInteger(sub).negate() : BigInteger(sub));
        }
    }
    return substraction;
}

BigInteger BigInteger::multiply(const BigInteger& bi) const
{
    BigInteger multiplication;
    std::string mul = this->m_value;
    std::string multiplied = bi.m_value;
    std::reverse(mul.begin(), mul.end());
    std::reverse(multiplied.begin(), multiplied.end());
    int step = 0;
    char carry = '0';
    for (const char& c1 : mul) {
        std::string cur_op;
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
    bool positive = (this->m_signed && bi.m_signed) || (!this->m_signed && !bi.m_signed);
    if (!positive) {
        multiplication = multiplication.negate();
    }
    return multiplication;
}

BigInteger BigInteger::divide(const BigInteger& bi) const
{
    BigInteger division;
    if (bi == ZERO) {
        // division by zero
    }
    else if (bi == ONE) {
        division = (*this);
    }
    else if (compare(bi) == 0) {
        division = 1;
    }
    else {
        std::string dividend = this->m_value;
        std::string quotient, cur_quotient;
        std::reverse(dividend.begin(), dividend.end());
        BigInteger bi_abs = bi.absolute();
        do {
            cur_quotient.push_back(dividend.back());
            dividend.pop_back();
            BigInteger bi_dividend(cur_quotient);
            if (bi_dividend >= bi_abs) {
                BigInteger n = BigInteger(2);
                while (bi_abs.multiply(n) <= bi_dividend) {
                    n++;
                }
                n--;
                quotient.append(n.toString());
                cur_quotient = bi_dividend.substract(bi_abs.multiply(n)).toString();
            }
            else {
                quotient.push_back('0');
            }
        } while (!dividend.empty());
        division = BigInteger(quotient);
    }
    bool positive = (this->m_signed && bi.m_signed) || (!this->m_signed && !bi.m_signed);
    if (!positive) {
        division = division.negate();
    }
    return division;
}

BigInteger BigInteger::pow(const BigInteger& bi) const
{
    BigInteger ret;
    if (bi == ZERO) {
        ret = ONE;
    }
    else if (bi == ONE) {
        ret = (*this);
    }
    else {
        BigInteger initial_value = (*this);
        ret = (*this);
        for (BigInteger i = ONE; i < bi; i++) {
            ret *= initial_value;
        }
    }
    return ret;
}

BigInteger BigInteger::modulus(const BigInteger& bi) const
{
    BigInteger mod = substract(bi.multiply(divide(bi)));
    return mod;
}

int BigInteger::bitLength() const
{
    return toString().length();
}

int BigInteger::compare(const BigInteger& bi) const
{
    int comparison;
    if (this->m_signed && !bi.m_signed) {
        // -a, +b
        comparison = -1;
    }
    else if (!this->m_signed && bi.m_signed) {
        // +a, -b
        comparison = 1;
    }
    else {
        // +a, +b or -a, -b
        if (this->m_value.length() < bi.m_value.length()) {
            comparison = -1;
        }
        else if (this->m_value.length() > bi.m_value.length()) {
            comparison = 1;
        }
        else {
            bool positive = !this->m_signed;
            if (this->m_value < bi.m_value) {
                comparison = (positive ? -1 : 1);
            }
            else if (this->m_value > bi.m_value) {
                comparison = (positive ? 1 : -1);;
            }
            else {
                comparison = 0;
            }
        }
    }
    return comparison;
}

BigInteger BigInteger::negate() const
{
    std::string value = this->m_value;
    return BigInteger((this->m_signed ? value : value.insert(0, 1, '-')));
}

BigInteger BigInteger::absolute() const
{
    return (isPositive() ? (*this) : negate());
}

bool BigInteger::isPositive() const
{
    return !this->m_signed;
}

bool BigInteger::isNegative() const
{
    return this->m_signed;
}

void BigInteger::swap(BigInteger& bi)
{
    BigInteger tmp = (*this);
    (*this) = bi;
    bi = tmp;
}

BigInteger BigInteger::operator+(const BigInteger& bi)
{
    return this->add(bi);
}

BigInteger BigInteger::operator-(const BigInteger& bi)
{
    return this->substract(bi);
}

BigInteger BigInteger::operator*(const BigInteger& bi)
{
    return this->multiply(bi);
}

BigInteger BigInteger::operator/(const BigInteger& bi)
{
    return this->divide(bi);
}

BigInteger BigInteger::operator%(const BigInteger& bi)
{
    return this->modulus(bi);
}

BigInteger BigInteger::operator<<(const BigInteger& bi) const
{
    std::string bitwise_val = toString();
    for (BigInteger i = ZERO; i < bi; i++) {
        bitwise_val.push_back('0');
    }
    return BigInteger(bitwise_val);
}

BigInteger BigInteger::operator>>(const BigInteger& bi) const
{
    std::string bitwise_val = toString();
    for (BigInteger i = ZERO; i < bi && bitwise_val.length()>0; i++) {
        bitwise_val.pop_back();
    }
    if (bitwise_val.empty()) {
        bitwise_val.push_back('0');
    }
    return BigInteger(bitwise_val);
}

BigInteger& BigInteger::operator+=(const BigInteger& bi)
{
    (*this) = add(bi);
    return (*this);
}

BigInteger& BigInteger::operator-=(const BigInteger& bi)
{
    (*this) = substract(bi);
    return (*this);
}

BigInteger& BigInteger::operator*=(const BigInteger& bi)
{
    (*this) = multiply(bi);
    return (*this);
}

BigInteger& BigInteger::operator/=(const BigInteger& bi)
{
    (*this) = divide(bi);
    return (*this);
}

BigInteger& BigInteger::operator--()
{
    (*this) = substract(ONE);
    return (*this);
}

BigInteger BigInteger::operator--(int)
{
    BigInteger before_minus = (*this);
    (*this) = substract(ONE);
    return before_minus;
}

BigInteger& BigInteger::operator++()
{
    (*this) = add(ONE);
    return (*this);
}

BigInteger BigInteger::operator++(int)
{
    BigInteger before_plus = (*this);
    (*this) = add(ONE);
    return before_plus;
}

bool BigInteger::operator==(const BigInteger& bi) const
{
    bool equal = (compare(bi) == 0);
    return equal;
}

bool BigInteger::operator!=(const BigInteger& bi) const
{
    bool different = (compare(bi) != 0);
    return different;
}

bool BigInteger::operator<(const BigInteger& bi) const
{
    bool less = (compare(bi) == -1);
    return less;
}

bool BigInteger::operator>(const BigInteger& bi) const
{
    bool more = (compare(bi) == 1);
    return more;
}

bool BigInteger::operator<=(const BigInteger& bi) const
{
    int cmp = compare(bi);
    return (cmp == -1) || (cmp == 0);
}

bool BigInteger::operator>=(const BigInteger& bi) const
{
    int cmp = compare(bi);
    return (cmp == 0) || (cmp == 1);
}

std::string BigInteger::toString() const
{
    std::stringstream ss;
    if (m_signed) {
        ss << '-';
    }
    ss << m_value;
    return ss.str();
}

using namespace std;

int main(int argc, char const* argv[])
{


    BigInteger n("1000"), n2("56");
    cout << n2 - n << endl;
    cout << n2 + n << endl;
    cout << n - n2 << endl;
    cout << n / n2 << endl;
    BigInteger n3("-100");
    cout << n3;
    return 0;
}
