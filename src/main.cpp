//
// Created by Stephan on 15.09.2022.
//
#include <iostream>
#include "BigInt.h"
#include "BigInt_const_size.h"
#include "interaction.h"


bool execute_command(BigInt::Funcs id, BigInt &bi) {
    try {
        switch (id) {
            case BigInt::EXIT:
                return false;
            case BigInt::SIZE:
                std::cout << "current size of your number is " << bi.size() << "!\n";
                return true;
            case BigInt::TO_STRING:
                std::cout << "your number now is " << bi.to_string() << "!\n";
                return true;
            case BigInt::ADDITION: {
                std::cout << "enter your number for addition: ";
                int x = read_int();
                bi += x;
                return true;
            }
            case BigInt::SUBTRACTING: {
                std::cout << "enter your number for subtraction: ";
                int x = read_int();
                bi -= x;
                return true;
            }
            case BigInt::MULTIPLY_10: {
                bi = !bi;
                return true;
            }
            case BigInt::DIVIDE_10: {
                bi.devision_by_10();
                return true;
            }
            case BigInt::INCREMENT: {
                bi++;
                return true;
            }
            case BigInt::DECREMENT:
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
//    BigInt bi1(BigInt(1000));              // ???????????????????????? ???????????????? ??????????????
//    BigInt bi2(bi1.additional_BI());   // ?????????? ??????????-???? ?????????????????????? ?????????????????????? (???????????????? RVO)
//    bi2 = bi1.additional_BI();          // ?????????? ????????, ???? ?????????????????? ??????????????
//    bi2 = bi1.additional_BI();          // ?????????? ????????


    BigInt bi;
    std::cout << "enter your initial integer: ";
    try {
        std::cin >> bi;
    } catch (...) {
        std::cout << "wrong input" <<std::endl;
        return 1;
    }
    BigInt::Funcs command_id = BigInt::EXIT;
    print_instruction();
    do {
        std::cout << "id of command: ";
        unsigned long long int id = 0;
        try{
            std::cin >> id;
        } catch (...) {
            std::cout << "wrong input of command id";
            continue;
        }
        command_id = static_cast<BigInt::Funcs>(id);
    } while (execute_command(command_id, bi));
}