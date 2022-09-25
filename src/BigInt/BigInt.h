//
// Created by Stephan on 24.09.2022.
//

#ifndef LAB3_SEM3_BIGINT_H
#define LAB3_SEM3_BIGINT_H
#include <iostream>
#include <string>
#include <cstring>

class BigInt {
protected:
    size_t length = 0;
    unsigned char * arr;

    void swap(BigInt & bi) {
        std::swap(length, bi.length);
        std::swap(arr, bi.arr);
    }
public:
    typedef enum Funcs {
        EXIT,
    } Funcs;
    // constructors
    BigInt() = default;
    BigInt(int x) : length(std::to_string(x).length()), arr(new unsigned char[length+1]) {
        arr[0] = (x < 0);
        for (size_t i = length; i; --i, x/=10)
            arr[i] = x % 10;
    }

    // copy-constructor
    BigInt(const BigInt &bi) : length(bi.length), arr(new unsigned char[bi.length+1]) {
        std::memcpy(arr, bi.arr, (length+1) * sizeof(char));
    }

    // assignment operator for my Ints
    BigInt & operator=(BigInt bi) {
        swap(bi);
        return *this;
    }

    // public methods
    size_t size() {
        return length;
    }
    unsigned char * copy_arr() {
        return nullptr;
    }
};


#endif //LAB3_SEM3_BIGINT_H
