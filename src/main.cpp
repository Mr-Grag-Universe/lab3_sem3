//
// Created by Stephan on 15.09.2022.
//
#include <iostream>
#include <cmath>
#include "BigInt.h"
#include "BigInt_const_size.h"
#include "interaction.h"


bool execute_command(BigInt_const_size::Funcs id, BigInt_const_size &bi) {
    try {
        switch (id) {
            case BigInt_const_size::EXIT:
                return false;
            case BigInt_const_size::SIZE:
                return true;
            default:
                return true;
        }
    } catch (...) {
        std::cout << "error in execution.";
        return true;
    }
}

void print_instruction() {
    std::cout << "0 - exit" << std::endl;
    std::cout << "1 - size" << std::endl;
    std::cout << "2 - integer" << std::endl;
    std::cout << "3 - " << std::endl;
    std::cout << "4 - " << std::endl;
    std::cout << "5 - " << std::endl;
    std::cout << "6 - " << std::endl;
    std::cout << "7 - " << std::endl;
    std::cout << "8 - " << std::endl;
    std::cout << "9 - " << std::endl;
    std::cout << "10 - " << std::endl;
    std::cout << "11" << std::endl;
    std::cout << "12" << std::endl;
}

int main() {
    BigInt_const_size bi1("111");
    std::cout << bi1.size() << bi1.to_string();
    std::cout << bi1.additional_code() << std::endl;

    BigInt_const_size bi2("-999999999");
    std::cout << bi2.size() << " " << bi2.to_string() << std::endl;
    std::cout << bi2.additional_code() << std::endl;

    BigInt_const_size bi;
    BigInt_const_size::Funcs command_id = BigInt_const_size::EXIT;
    print_instruction();
    do {
        std::cout << "id of command: ";
        unsigned long long int id = 0;
        std::cin >> id;
        command_id = static_cast<BigInt_const_size::Funcs>(id);
    } while (execute_command(command_id, bi));
}