//
// Created by Stephan on 24.09.2022.
//
#include <iostream>
#include <cstring>
#include <string>

#include "BigInt.h"

size_t BigInt::size() const {
    return length;
}
std::string BigInt::to_string() const {
    std::string s = (arr[0])? "-": "+";
    for (size_t i = 1; i <= length; ++i) {
        s += std::to_string(arr[i]);
    }
    return s;
}

bool BigInt::is_integer(const std::string & s) {
    if (s.empty())
        return false;
    char sign = s[0];
    bool sign_is_real = false;
    if (sign == '+' || sign == '-') {
        if (s.size() == 1)
            return false;
        sign_is_real = true;
    }
    else if (std::isdigit(sign))
        sign_is_real = false;
    else
        return false;

    for (size_t i = sign_is_real; i < s.size(); ++i)
        if (!std::isdigit(s[i]))
            return false;

    return true;
}

std::istream & operator>>(std::istream & istream, BigInt & bi) {
    std::string s;
    istream >> s;
    bi = BigInt(s);
    return istream;
}
std::ostream & operator<<(std::ostream & ostream, const BigInt & bi) {
    return ostream << bi.to_string();
}

BigInt BigInt::additional_BI() const {
    if (arr == nullptr || !length)
        throw std::invalid_argument("this function can't be called by empty object");
    BigInt bi;
    try{
        bi.arr = new unsigned char [length+1];
    } catch (std::bad_alloc & ba) {
        delete[] bi.arr;
        std::cerr << ba.what() << std::endl;
        throw ba;
    }
    bi.length = length;
    bi.arr[0] = (length == 1 && !arr[length]) ? 0 : arr[0];

    if (!arr[0]) {
        memcpy(bi.arr+1, arr+1, length * sizeof(char));
        return bi;
    }
    for (size_t i = 1; i <= length; ++i) {
        bi.arr[i] = 9-arr[i];
    }
    size_t i = 1;
    if (arr[0]) {
        unsigned char buf = 1;
        unsigned char sum = 0;
        for (i = length; i > 0; --i) {
            sum = buf+bi.arr[i];
            bi.arr[i] = sum % 10;
            buf = sum / 10;
        }
    }
    i = 1;
    while (bi.arr[i] == 0 && i < length)
        ++i;
    // bi.length = length-i-1;
    try {
        auto * copy = new unsigned char [length+2-i];
        std::memcpy(copy+1, bi.arr+i, length-i+1);
        copy[0] = bi.arr[0];
        delete[] bi.arr;
        bi.arr = copy;
    } catch (std::bad_alloc & ba) {
        std::cerr << ba.what() << std::endl;
        throw ba;
    }
    bi.length = bi.length-i+1;
    if (!(bi.length)) {
        bi.arr[0] = 0;
        bi.length = 1;
    }
    return bi;
}

std::string BigInt::additional_code() const {
    BigInt bi = this->additional_BI();
    return bi.to_string();
}

// перегрузка оператора +
/*
BigInt& BigInt::operator+=(const BigInt & bi) {
    BigInt a = this->additional_BI();
    BigInt b = bi.additional_BI();
    std::cout << a << " " << b << std::endl;
    unsigned char buf = 0;
    unsigned char sum = 0;
    BigInt res;
    size_t M = std::max(bi.length, length);
    try {
        res.arr = new unsigned char [M+1];
    } catch (std::bad_alloc & ba) {
        std::cerr << ba.what() << std::endl;
        throw ba;
    }

    long long int delta = a.length - b.length;
    unsigned char def = 0;
    if (delta > 0)
        def = b.arr[0] ? 9 : 0;
    else
        def = a.arr[0] ? 9 : 0;

    size_t m = std::max(a.length, b.length);
    for (size_t i = m; i > 0; --i) {
        if (delta > 0) {
            if (i-delta <= 0) {
                sum = a.arr[i] + buf + def;
            } else {
                sum = a.arr[i] + b.arr[i-delta] + buf;
            }
        } else if (delta < 0) {
            if (i+delta <= 0) {
                sum = b.arr[i] + buf + def;
            } else {
                sum = a.arr[i+delta] + b.arr[i] + buf;
            }
        } else {
            sum = a.arr[i] + b.arr[i] + buf;
        }
        res.arr[M-m+i] = sum % 10;
        buf = sum / 10;
    }

    size_t i = 1;
    while (res.arr[i] == 0 && i <= res.length)
        ++i;

    try {
        if (a.arr[0]) {
            if (b.arr[0]) {
                // отрицательное переполнение
                if (buf==1 && (0 == res.length+1-i)) {
                    ++res.length;
                    res.arr[0] = 9-!buf;
                    auto * copy = new unsigned char [res.length+1];
                    std::memcpy(copy+1, arr, res.length);
                    delete[] res.arr;
                    res.arr = copy;
                } else if (!buf) {
                    ++res.length;
                    res.arr[0] = 9-!buf;
                    auto * copy = new unsigned char [res.length+1];
                    std::memcpy(copy+1, arr, res.length);
                    delete[] res.arr;
                    res.arr = copy;
                }
                res.arr[0] = 1;
            } else {
                if (buf) {
                    res.arr[0] = 0;
                } else {
                    res.arr[0] = 1;
                }
            }
        } else {
            if (b.arr[0]) {
                if (buf) {
                    res.arr[0] = 0;
                } else {
                    res.arr[0] = 1;
                }
            } else {
                // положительное переполнение
                if (buf) {
                    ++res.length;
                    res.arr[0] = buf;
                    auto * copy = new unsigned char [res.length+1];
                    std::memcpy(copy+1, arr, res.length);
                    delete[] res.arr;
                    res.arr = copy;
                }
                res.arr[0] = 0;
            }
        }
    } catch (...) {
        delete[] res.arr;
        throw std::logic_error("error in \'if\' block of addition");
    }
    i = 1;
    while (res.arr[i] == 0 && i <= res.length)
        ++i;
    try {
        auto * copy = new unsigned char [res.length+2-i];
        std::memcpy(copy+1, res.arr+i, res.length-i+1);
        copy[0] = res.arr[0];
        delete[] res.arr;
        res.arr = copy;
    } catch (std::bad_alloc & ba) {
        std::cerr << ba.what() << std::endl;
        throw ba;
    }
    std::cout << res;
    res.length = res.length+1-i;
    if (!(res.length)) {
        res.arr[0] = 0;
        res.length = 1;
    }
    if (res.arr[0]) {
        res = res.additional_BI();
    }
    *this = res;
    return *this;
}
*/

BigInt& BigInt::operator+=(const BigInt & bi) {
    BigInt a = this->additional_BI();
    BigInt b = bi.additional_BI();
    std::cout << "input to +=: " << a << " " << b << std::endl;
    BigInt res;

    // инициализируем res.arr
    size_t pr_len = std::max(this->length, bi.length);
    res.arr = new unsigned char [pr_len+2];
    memset(res.arr, 0, pr_len+2);

    // допиливаем a и b до нормального вида
    //=============================
    size_t a_len = a.length;
    unsigned char *a_arr = nullptr;
    unsigned char *b_arr = nullptr;
    try {
        a_arr = new unsigned char [pr_len+1];
        b_arr = new unsigned char [pr_len+1];
    } catch (std::bad_alloc & ba) {
        delete[] a_arr;
        delete[] b_arr;
        std::cerr << ba.what() << std::endl;
        throw ba;
    }

    {
        if (a.arr[0]) {
            if (pr_len != length)
                std::memset(a_arr + 1, 9, pr_len);
            else
                std::memset(a_arr + 1, 0, pr_len);
        }
        else
            std::memset(a_arr + 1, 0, pr_len);
        std::memcpy(a_arr + pr_len - a_len + 1, a.arr+1, a_len);
        a_arr[0] = a.arr[0];
    }

    size_t b_len = b.length;
    {
        if (b.arr[0])
            if (bi.length != pr_len)
                std::memset(b_arr + 1, 9, pr_len);
            else
                std::memset(b_arr + 1, 0, pr_len);
        else
            std::memset(b_arr + 1, 0, pr_len);
        std::memmove(b_arr + pr_len - b_len + 1, b.arr+1, b_len);
        b_arr[0] = b.arr[0];
    }
    //=============================

    unsigned char buf = 0;
    unsigned char sum = 0;
    // сложение 2 чисел
    for (size_t i = pr_len; i > 0; --i) {
        sum = a_arr[i] + b_arr[i] + buf;
        res.arr[i] = sum % 10;
        buf = sum / 10;
    }

    delete[] a_arr;
    delete[] b_arr;

    try {
        if (a.arr[0] && b.arr[0]) {
            if (buf) {
                // расширить
                memmove(res.arr+2, res.arr+1, pr_len);
                res.arr[1] = 9;
                res.length = pr_len+1;
            } else {
                // оставить как есть
                size_t i = 1;
                for (; i < pr_len+1 && !res.arr[i]; ++i) {}
                auto * copy = new unsigned char [pr_len+2-i];
                memmove(copy+1, res.arr+i, pr_len+1-i);
                delete[] res.arr;
                res.arr = copy;
                res.length = pr_len+1-i;
            }
            res.arr[0] = 1;
        } else if (!(a.arr[0] || b.arr[0])) {
            if (buf) {
                // расширить
                memmove(res.arr+2, res.arr+1, pr_len);
                res.arr[1] = 1;
                res.length = pr_len+1;
            } else {
                // оставить как есть
                size_t i = 1;
                for (; i < pr_len+1 && !res.arr[i]; ++i) {}
                auto * copy = new unsigned char [pr_len+2-i];
                memmove(copy+1, res.arr+i, pr_len+1-i);
                delete[] res.arr;
                res.arr = copy;
                res.length = pr_len+1-i;
            }
            res.arr[0] = 0;
        } else {
            // оставить как есть
            size_t i = 1;
            for (; i < pr_len+1 && !res.arr[i]; ++i) {}
            auto * copy = new unsigned char [pr_len+2-i];
            memmove(copy+1, res.arr+i, pr_len+1-i);
            delete[] res.arr;
            res.arr = copy;
            res.length = pr_len+1-i;
            res.arr[0] = !buf;
        }
    } catch (...) {
        delete[] res.arr;
        throw std::logic_error("error in \'if\' block of addition");
    }

    std::cout << "pr result: " << res << std::endl;
    if (res.arr[0]) {
        res = res.additional_BI();
    }

    *this = res;
    std::cout << "result: " << res << std::endl;
    return *this;
}

BigInt operator+(const BigInt& a, const BigInt& b) {
    BigInt copy = a;
    copy += b;
    return copy;
}

// перегрузка оператора -=
BigInt& BigInt::operator-=(const BigInt & bi) {
    BigInt _copy = bi;
    if (bi.length == 1 && !bi.arr[1])
        _copy.arr[0] = 0;
    else
        _copy.arr[0] = !_copy.arr[0];
    return (*this += _copy);
}
BigInt operator-(const BigInt& a, const BigInt& b) {
    BigInt copy = a;
    copy -= b;
    return copy;
}

// префикс
BigInt& BigInt::operator++() {
    *this += 1;
    return *this;
}
// постфикс
BigInt BigInt::operator++(int) {
    BigInt copy = *this;
    ++*this;
    return copy;
}
// префикс
BigInt& BigInt::operator--() {
    *this -= 1;
    return *this;
}
// постфикс
BigInt BigInt::operator--(int) {
    BigInt copy = *this;
    --*this;
    return copy;
}

// деление на 10
void BigInt::devision_by_10() {
    if (length == 1) {
        arr[1] = 0;
        arr[0] = 0;
        return;
    }
    --length;
    try {
        auto * copy = new unsigned char [length+1];
        std::memcpy(copy, arr, (length+1) * sizeof(char));
        delete[] arr;
        arr = copy;
    } catch (std::bad_alloc & ba) {
        std::cerr << ba.what() << std::endl;
        delete[] arr;
        arr = nullptr;
        length = 0;
        throw ba;
    }
    if (length == 1 && arr[length-1] == 0)
        arr[0] = 0;
}
// умножение на 10
void BigInt::multiplication_with_10() {
    if (length == 1 && arr[1] == 0)
        return;
    try {
        auto * copy = new unsigned char [length+2];
        std::memmove(copy, arr, (length+1) * sizeof(unsigned char));
        delete[] arr;
        arr = copy;
    } catch (std::bad_alloc & ba) {
        std::cerr << ba.what() << std::endl;
        throw ba;
    }
    ++length;
    arr[length] = 0;
}
BigInt BigInt::operator!() const {
    BigInt copy = *this;
    copy.multiplication_with_10();
    return copy;
}

bool operator<(const BigInt& a, const BigInt& b) {
    std::string s1 = a.to_string();
    std::string s2 = b.to_string();
    if (s1[0] != s2[0])
        return (s1[0] == '-');

    if (s1.size() != s2.size()) {
        if (s1[0] == '-')
            return s1.size() > s2.size();
        else
            return s1.size() < s2.size();
    }

    for (size_t i = 0; i < s1.size(); ++i) {
        if (s1[i] != s2[i]) {
            if (s1[0] == '-')
                return s1[i] > s2[i];
            else
                return s1[i] < s2[i];
        }
    }
    return false;
}
bool operator>(const BigInt& a, const BigInt& b) {
    return b < a;
}