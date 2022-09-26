//
// Created by Stephan on 24.09.2022.
//

#ifndef LAB2_SEM3_BIGINT_CONST_SIZE_H
#define LAB2_SEM3_BIGINT_CONST_SIZE_H
#include <iostream>
#include <string>
#include <cstring>


class BigInt_const_size {
public:
    static const size_t MAX_SIZE = 10;
protected:
    size_t length = 0;
    unsigned char arr[MAX_SIZE]{};

    void swap(BigInt_const_size & bi) {
        std::swap(length, bi.length);
        std::swap(arr, bi.arr);
    }
public:
    typedef enum Funcs {
        EXIT,
        SIZE,
        TO_STRING,
        ADDITION,
        SUBTRACTING,
        MULTIPLY_10,
        DIVIDE_10,
    } Funcs;

    // constructors
    BigInt_const_size() = default;
    BigInt_const_size(const long & x) {
        size_t l = std::to_string(std::abs(x)).length();

        if (l >= MAX_SIZE)
            throw std::invalid_argument("too big integer");
        length = l;
        arr[0] = (unsigned char) (x < 0);
        long y = std::abs(x);
        memset(arr+1, 0, MAX_SIZE-length-1);
        for (size_t i = 0; i < length; ++i, y/=10)
            arr[MAX_SIZE-i-1] = y%10;
    }
    BigInt_const_size(const std::string & x) {
        // нужна проверка строки
        if (x.empty())
            return;
        size_t l = (x[0] == '-') ? x.size()-1 : x.size();

        if (l >= MAX_SIZE)
            throw std::invalid_argument("too big integer");
        length = l;
        arr[0] = (unsigned char) (x[0] == '-');
        std::string s = x;
        if (isdigit(x[0]))
            s = "+" + x;
        memset(arr+1, 0, MAX_SIZE-length-1);
        // можно доработать
        for (size_t i = 1; i < s.length(); ++i)
            arr[MAX_SIZE+i-length-1] = s[i]-'0';
    }

    // assignment operator for my Ints
    BigInt_const_size & operator=(BigInt_const_size bi) {
        swap(bi);
        return *this;
    }

    // public methods
    [[nodiscard]] size_t size() const;
    [[nodiscard]] std::string to_string() const;
    // перегрузка оператора >>
    friend std::istream & operator>>(std::istream &, BigInt_const_size &);
    // перегрузка оператора <<
    friend std::ostream & operator<<(std::ostream &, const BigInt_const_size &);
    [[nodiscard]] BigInt_const_size additional_BI() const;
    [[nodiscard]] std::string additional_code() const;
    // перегрузка оператора +
    BigInt_const_size& operator+=(const BigInt_const_size bi);
    // перегрузка оператора -
    BigInt_const_size& operator-=(const BigInt_const_size bi);
    // деление на 10
    void devision_by_10();
    // умножение на 10
    void multiplication_with_10();
    // префикс-постфикс инкримент
    // префикс
    BigInt_const_size& operator++();
    // постфикс
    BigInt_const_size operator++(int);
    // префикс-постфикс декримент
    // префикс
    BigInt_const_size& operator--();
    // постфикс
    BigInt_const_size operator--(int);
};

BigInt_const_size operator+(const BigInt_const_size&, const BigInt_const_size&);
BigInt_const_size operator-(const BigInt_const_size&, const BigInt_const_size&);

#endif //LAB2_SEM3_BIGINT_CONST_SIZE_H
