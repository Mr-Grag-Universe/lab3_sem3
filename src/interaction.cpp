//
// Created by Stephan on 17.09.2022.
//
#include <iostream>

#include "interaction.h"
#include "BigInt.h"

int read_int() {
    std::string s;
    if (!(std::cin >> s)) {
        std::cout << "end of this stream" << std::endl;
        throw std::runtime_error("");
    }
    int n;
    try {
        n = std::stoi(s);
    } catch (const std::invalid_argument & e) {
        std::cerr << e.what() << std::endl;
        throw std::runtime_error("wrong input");
    } catch (const std::out_of_range & e) {
        std::cerr << e.what() << std::endl;
        throw std::invalid_argument("wrong input");
    }
    return n;
}
