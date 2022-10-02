//
// Created by Stephan on 30.09.2022.
//

#ifndef LAB2_SEM3_BI_TESTS_H
#define LAB2_SEM3_BI_TESTS_H
#include "gtest/gtest.h"
#include "BigInt/BigInt.h"

TEST(DINAMIC_initial_funcs, constructors) {
    BigInt bi1;
    ASSERT_EQ(bi1.size(), 0);
    BigInt bi2("11");
    ASSERT_EQ(bi2.size(), 2);
    ASSERT_EQ(bi2.to_string(), "+11");
    BigInt bi5(100);
    ASSERT_EQ(bi5.size(), 3);
    ASSERT_EQ(bi5.to_string(), "+100");
    BigInt bi3("-122");
    ASSERT_EQ(bi3.size(), 3);
    ASSERT_EQ(bi3.to_string(), "-122");
    BigInt bi4(bi2);
    ASSERT_EQ(bi4.size(), 2);
    ASSERT_EQ(bi4.to_string(), "+11");
    bi3 = bi2;
    ASSERT_EQ(bi3.size(), 2);
    ASSERT_EQ(bi3.to_string(), "+11");
    // ASSERT_ANY_THROW(bi3 = BigInt("1000000000"));
    ASSERT_ANY_THROW(bi3 = BigInt("asdd"));
}
TEST(CONST_initial_funcs, input) {
}

TEST(DINAMIC_methods, add_code) {
    BigInt bi1("111");
    ASSERT_EQ(bi1.size(), 3);
    ASSERT_EQ(bi1.to_string(), "+111");
    ASSERT_EQ(bi1.additional_code(), "+111");
    BigInt bi2("-999999999");
    ASSERT_EQ(bi2.size(), 9);
    ASSERT_EQ(bi2.to_string(), "-999999999");
    ASSERT_EQ(bi2.additional_code(), "-1");
}

TEST(DINAMIC_methods, devision_by_10) {
    BigInt bi1("111");
    ASSERT_EQ(bi1.size(), 3);
    ASSERT_EQ(bi1.to_string(), "+111");
    bi1.devision_by_10();
    ASSERT_EQ(bi1.size(), 2);
    ASSERT_EQ(bi1.to_string(), "+11");
    BigInt bi2("-999999999");
    ASSERT_EQ(bi2.size(), 9);
    ASSERT_EQ(bi2.to_string(), "-999999999");
    bi2.devision_by_10();
    ASSERT_EQ(bi2.size(), 8);
    ASSERT_EQ(bi2.to_string(), "-99999999");
    BigInt bi3("1");
    bi3.devision_by_10();
    ASSERT_EQ(bi3.size(), 1);
    ASSERT_EQ(bi3.to_string(), "+0");
    BigInt bi4("0");
    bi4.devision_by_10();
    ASSERT_EQ(bi4.size(), 1);
    ASSERT_EQ(bi4.to_string(), "+0");
}

TEST(DINAMIC_methods, multiplication_with_10) {
    BigInt bi1("111");
    ASSERT_EQ(bi1.size(), 3);
    ASSERT_EQ(bi1.to_string(), "+111");
    bi1.multiplication_with_10();
    ASSERT_EQ(bi1.size(), 4);
    ASSERT_EQ(bi1.to_string(), "+1110");
    BigInt bi2("-999999999");
    ASSERT_EQ(bi2.size(), 9);
    ASSERT_EQ(bi2.to_string(), "-999999999");
    ASSERT_NO_THROW(bi2.multiplication_with_10());
    ASSERT_EQ(bi2.size(), 10);
    ASSERT_EQ(bi2.to_string(), "-9999999990");
    BigInt bi3("1");
    bi3.multiplication_with_10();
    ASSERT_EQ(bi3.size(), 2);
    ASSERT_EQ(bi3.to_string(), "+10");
    BigInt bi4("0");
    bi4.multiplication_with_10();
    ASSERT_EQ(bi4.size(), 1);
    ASSERT_EQ(bi4.to_string(), "+0");
}

TEST(DINAMIC_overloaded_operators, plus_ass) {
    BigInt bi1("123");
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
    ASSERT_NO_THROW(bi1 += bi1);
    bi1 = -999999999;
    BigInt bi2 = 999999999;
    ASSERT_NO_THROW(bi1 -= bi2);
}

TEST(DINAMIC_overloaded_operators, plus) {
    BigInt bi1("123");
    BigInt bi2("120");
    bi1 = bi2 + std::string("100");
    EXPECT_EQ(bi1.size(), 3);
    EXPECT_EQ(bi1.to_string(), "+220");
    bi1 = bi2 + (-15);
    EXPECT_EQ(bi1.size(), 3);
    EXPECT_EQ(bi1.to_string(), "+105");
}

TEST(DINAMIC_overloaded_operators, minus_ass) {
    BigInt bi1("123");
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

TEST(DINAMIC_overloaded_operators, minus) {
    BigInt bi1("123");
    BigInt bi2("120");
    bi1 = bi2 - std::string("100");
    EXPECT_EQ(bi1.size(), 2);
    EXPECT_EQ(bi1.to_string(), "+20");
    bi1 = bi2 - 15;
    EXPECT_EQ(bi1.size(), 3);
    EXPECT_EQ(bi1.to_string(), "+105");
}

TEST(DINAMIC_overloaded_operators, increment) {
    BigInt bi1 = 0;
    bi1++;
    EXPECT_EQ(bi1.size(), 1);
    EXPECT_EQ(bi1.to_string(), "+1");
    ++bi1;
    EXPECT_EQ(bi1.size(), 1);
    EXPECT_EQ(bi1.to_string(), "+2");
    BigInt bi2 = (++bi1)++;
    EXPECT_EQ(bi2.size(), 1);
    EXPECT_EQ(bi2.to_string(), "+3");
    EXPECT_EQ(bi1.size(), 1);
    EXPECT_EQ(bi1.to_string(), "+4");

    ASSERT_NO_THROW(++BigInt(999999999));
    ASSERT_NO_THROW(BigInt(999999999)++);
}

TEST(DINAMIC_overloaded_operators, decrement) {
    BigInt bi1 = 0;
    bi1--;
    EXPECT_EQ(bi1.size(), 1);
    EXPECT_EQ(bi1.to_string(), "-1");
    --bi1;
    EXPECT_EQ(bi1.size(), 1);
    EXPECT_EQ(bi1.to_string(), "-2");
    BigInt bi2 = (--bi1)--;
    EXPECT_EQ(bi2.size(), 1);
    EXPECT_EQ(bi2.to_string(), "-3");
    EXPECT_EQ(bi1.size(), 1);
    EXPECT_EQ(bi1.to_string(), "-4");

    ASSERT_NO_THROW(--BigInt(-999999999));
    ASSERT_NO_THROW(BigInt(-999999999)--);
    bi1 = --BigInt(-999999999);
    bi2 = BigInt(-999999999)--;
    EXPECT_EQ(bi1.to_string(), "-1000000000");
    EXPECT_EQ(bi2.to_string(), "-999999999");
}

TEST(DINAMIC_methods, special_test) {
    BigInt A = 100;
    BigInt B = 50;
    BigInt C = !(A + A - B) - B;
    EXPECT_EQ(C.to_string(), "+" + std::to_string((100*2-50)*10-50));
}


#endif //LAB2_SEM3_BI_TESTS_H
