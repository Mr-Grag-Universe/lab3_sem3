//
// Created by Stephan on 24.09.2022.
//
#include <iostream>
#include <cstring>
#include <string>

#include "BigInt_const_size.h"

size_t BigInt_const_size::size() const {
    return length;
}
std::string BigInt_const_size::to_string() const {
    std::string s = (arr[0])? "-": "+";
    for (size_t i = 1; i <= length; ++i) {
        s += std::to_string(arr[MAX_SIZE-length+i-1]);
    }
    return s;
}

BigInt_const_size BigInt_const_size::additional_BI() const {
    BigInt_const_size bi;
    bi.length = length;
    bi.arr[0] = arr[0];
    if (!arr[0]) {
        memcpy(bi.arr+1, arr+1, (MAX_SIZE-1) * sizeof(char));
        return bi;
    }
    for (size_t i = 1; i < MAX_SIZE; ++i) {
        bi.arr[i] = 9-arr[i];
    }
    size_t i = 1;
    while (bi.arr[i] == 0 && i < MAX_SIZE)
        ++i;
    bi.length = MAX_SIZE-i;
    if (!(bi.length)) {
        bi.arr[0] = 0;
        bi.length = 1;
    }
    return bi;
}

std::string BigInt_const_size::additional_code() const {
    BigInt_const_size bi = this->additional_BI();
    return bi.to_string();
}

