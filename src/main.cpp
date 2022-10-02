//
// Created by Stephan on 15.09.2022.
//
#include <iostream>
#include <cmath>
#include "BigInt.h"
#include "BigInt_const_size.h"
#include "BigInt.h"
#include "interaction.h"


bool execute_command(BigInt_const_size::Funcs id, BigInt_const_size &bi) {
    try {
        switch (id) {
            case BigInt_const_size::EXIT:
                return false;
            case BigInt_const_size::SIZE:
                std::cout << "current size of your number is " << bi.size() << "!\n";
                return true;
            case BigInt_const_size::TO_STRING:
                std::cout << "your number now is " << bi.to_string() << "!\n";
                return true;
            case BigInt_const_size::ADDITION: {
                std::cout << "enter your number for addition: ";
                int x = read_int();
                bi += x;
                return true;
            }
            case BigInt_const_size::SUBTRACTING: {
                std::cout << "enter your number for subtraction: ";
                int x = read_int();
                bi -= x;
                return true;
            }
            case BigInt_const_size::MULTIPLY_10: {
                bi = !bi;
                return true;
            }
            case BigInt_const_size::DIVIDE_10: {
                bi.devision_by_10();
                return true;
            }
            case BigInt_const_size::INCREMENT: {
                bi++;
                return true;
            }
            case BigInt_const_size::DECREMENT:
                bi--;
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
    std::cout << "2 - print" << std::endl;
    std::cout << "3 - add int" << std::endl;
    std::cout << "4 - subtract int" << std::endl;
    std::cout << "5 - multiply with 10" << std::endl;
    std::cout << "6 - divide by 10" << std::endl;
    std::cout << "7 - increment" << std::endl;
    std::cout << "8 - decrement" << std::endl;
    std::cout << "9 - " << std::endl;
    std::cout << "10 - " << std::endl;
    std::cout << "11" << std::endl;
    std::cout << "12" << std::endl;
}

int main() {
    BigInt bi1("123");
    bi1 += std::string("100");
    std::cout << bi1 << std::endl;
    bi1 += -15;
    std::cout << bi1 << std::endl;
    bi1 += -210;
    std::cout << bi1 << std::endl;


    BigInt_const_size bi;
    std::cin >> bi;
    BigInt_const_size::Funcs command_id = BigInt_const_size::EXIT;
    print_instruction();
    do {
        std::cout << "id of command: ";
        unsigned long long int id = 0;
        std::cin >> id;
        command_id = static_cast<BigInt_const_size::Funcs>(id);
    } while (execute_command(command_id, bi));
}