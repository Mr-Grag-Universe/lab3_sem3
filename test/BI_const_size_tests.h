//
// Created by Stephan on 30.09.2022.
//

#ifndef LAB2_SEM3_BI_CONST_SIZE_TESTS_H
#define LAB2_SEM3_BI_CONST_SIZE_TESTS_H
#include "gtest/gtest.h"
#include "BigInt/BigInt.h"

TEST(CONST_initial_funcs, constructors) {
    BigInt_const_size bi1;
    ASSERT_EQ(bi1.size(), 0);
    BigInt_const_size bi2("11");
    ASSERT_EQ(bi2.size(), 2);
    ASSERT_EQ(bi2.to_string(), "+11");
    BigInt_const_size bi5(100);
    ASSERT_EQ(bi5.size(), 3);
    ASSERT_EQ(bi5.to_string(), "+100");
    BigInt_const_size bi3("-122");
    ASSERT_EQ(bi3.size(), 3);
    ASSERT_EQ(bi3.to_string(), "-122");
    BigInt_const_size bi4(bi2);
    ASSERT_EQ(bi4.size(), 2);
    ASSERT_EQ(bi4.to_string(), "+11");
    bi3 = bi2;
    ASSERT_EQ(bi3.size(), 2);
    ASSERT_EQ(bi3.to_string(), "+11");
    ASSERT_ANY_THROW(bi3 = BigInt_const_size("1000000000"));
    ASSERT_ANY_THROW(bi3 = BigInt_const_size("asdd"));
}
TEST(CONST_initial_funcs, input) {
}

TEST(CONST_methods, add_code) {
    BigInt_const_size bi1("111");
    ASSERT_EQ(bi1.size(), 3);
    ASSERT_EQ(bi1.to_string(), "+111");
    ASSERT_EQ(bi1.additional_code(), "+111");
    BigInt_const_size bi2("-999999999");
    ASSERT_EQ(bi2.size(), 9);
    ASSERT_EQ(bi2.to_string(), "-999999999");
    ASSERT_EQ(bi2.additional_code(), "-1");
}

TEST(CONST_methods, devision_by_10) {
    BigInt_const_size bi1("111");
    ASSERT_EQ(bi1.size(), 3);
    ASSERT_EQ(bi1.to_string(), "+111");
    bi1.devision_by_10();
    ASSERT_EQ(bi1.size(), 2);
    ASSERT_EQ(bi1.to_string(), "+11");
    BigInt_const_size bi2("-999999999");
    ASSERT_EQ(bi2.size(), 9);
    ASSERT_EQ(bi2.to_string(), "-999999999");
    bi2.devision_by_10();
    ASSERT_EQ(bi2.size(), 8);
    ASSERT_EQ(bi2.to_string(), "-99999999");
    BigInt_const_size bi3("1");
    bi3.devision_by_10();
    ASSERT_EQ(bi3.size(), 1);
    ASSERT_EQ(bi3.to_string(), "+0");
    BigInt_const_size bi4("0");
    bi4.devision_by_10();
    ASSERT_EQ(bi4.size(), 1);
    ASSERT_EQ(bi4.to_string(), "+0");
}

TEST(CONST_methods, multiplication_with_10) {
    BigInt_const_size bi1("111");
    ASSERT_EQ(bi1.size(), 3);
    ASSERT_EQ(bi1.to_string(), "+111");
    bi1.multiplication_with_10();
    ASSERT_EQ(bi1.size(), 4);
    ASSERT_EQ(bi1.to_string(), "+1110");
    BigInt_const_size bi2("-999999999");
    ASSERT_EQ(bi2.size(), 9);
    ASSERT_EQ(bi2.to_string(), "-999999999");
    ASSERT_ANY_THROW(bi2.multiplication_with_10());
    ASSERT_EQ(bi2.size(), 9);
    ASSERT_EQ(bi2.to_string(), "-999999999");
    BigInt_const_size bi3("1");
    bi3.multiplication_with_10();
    ASSERT_EQ(bi3.size(), 2);
    ASSERT_EQ(bi3.to_string(), "+10");
    BigInt_const_size bi4("0");
    bi4.multiplication_with_10();
    ASSERT_EQ(bi4.size(), 1);
    ASSERT_EQ(bi4.to_string(), "+0");
}

TEST(CONST_overloaded_operators, plus_ass) {
    BigInt_const_size bi1("123");
    bi1 += std::string("100");
    EXPECT_EQ(bi1.size(), 3);
    EXPECT_EQ(bi1.to_string(), "+223");
    bi1 += -15;
    EXPECT_EQ(bi1.size(), 3);
    EXPECT_EQ(bi1.to_string(), "+208");
    bi1 += -210;
    EXPECT_EQ(bi1.size(), 1);
    EXPECT_EQ(bi1.to_string(), "-2");
    bi1 = std::string("999999999");
    ASSERT_ANY_THROW(bi1 += bi1);
    bi1 = -999999999;
    BigInt_const_size bi2 = 999999999;
    ASSERT_ANY_THROW(bi1 -= bi2);
}

TEST(CONST_overloaded_operators, plus) {
    BigInt_const_size bi1("123");
    BigInt_const_size bi2("120");
    bi1 = bi2 + std::string("100");
    EXPECT_EQ(bi1.size(), 3);
    EXPECT_EQ(bi1.to_string(), "+220");
    bi1 = bi2 + (-15);
    EXPECT_EQ(bi1.size(), 3);
    EXPECT_EQ(bi1.to_string(), "+105");
}

TEST(CONST_overloaded_operators, minus_ass) {
    BigInt_const_size bi1("123");
    bi1 -= std::string("100");
    EXPECT_EQ(bi1.size(), 2);
    EXPECT_EQ(bi1.to_string(), "+23");
    bi1 -= -15;
    EXPECT_EQ(bi1.size(), 2);
    EXPECT_EQ(bi1.to_string(), "+38");
    bi1 -= 210;
    EXPECT_EQ(bi1.size(), 3);
    EXPECT_EQ(bi1.to_string(), "-172");
}

TEST(CONST_overloaded_operators, minus) {
    BigInt_const_size bi1("123");
    BigInt_const_size bi2("120");
    bi1 = bi2 - std::string("100");
    EXPECT_EQ(bi1.size(), 2);
    EXPECT_EQ(bi1.to_string(), "+20");
    bi1 = bi2 - 15;
    EXPECT_EQ(bi1.size(), 3);
    EXPECT_EQ(bi1.to_string(), "+105");
}

TEST(CONST_overloaded_operators, increment) {
BigInt_const_size bi1 = 0;
    bi1++;
    EXPECT_EQ(bi1.size(), 1);
    EXPECT_EQ(bi1.to_string(), "+1");
    ++bi1;
    EXPECT_EQ(bi1.size(), 1);
    EXPECT_EQ(bi1.to_string(), "+2");
    BigInt_const_size bi2 = (++bi1)++;
    EXPECT_EQ(bi2.size(), 1);
    EXPECT_EQ(bi2.to_string(), "+3");
    EXPECT_EQ(bi1.size(), 1);
    EXPECT_EQ(bi1.to_string(), "+4");

    ASSERT_ANY_THROW(++BigInt_const_size(999999999));
    ASSERT_ANY_THROW(BigInt_const_size(999999999)++);
}

TEST(CONST_overloaded_operators, decrement) {
    BigInt_const_size bi1 = 0;
    bi1--;
    EXPECT_EQ(bi1.size(), 1);
    EXPECT_EQ(bi1.to_string(), "-1");
    --bi1;
    EXPECT_EQ(bi1.size(), 1);
    EXPECT_EQ(bi1.to_string(), "-2");
    BigInt_const_size bi2 = (--bi1)--;
    EXPECT_EQ(bi2.size(), 1);
    EXPECT_EQ(bi2.to_string(), "-3");
    EXPECT_EQ(bi1.size(), 1);
    EXPECT_EQ(bi1.to_string(), "-4");

    ASSERT_ANY_THROW(--BigInt_const_size(-999999999));
    ASSERT_ANY_THROW(BigInt_const_size(-999999999)--);
}

TEST(CONST_methods, special_test) {
    BigInt_const_size A = 100;
    BigInt_const_size B = 50;
    BigInt_const_size C = !(A + A - B) - B;
    EXPECT_EQ(C.to_string(), "+" + std::to_string((100*2-50)*10-50));
}


#endif //LAB2_SEM3_BI_CONST_SIZE_TESTS_H
