//
// Created by Stephan on 08.09.2022.
//

#include "gtest/gtest.h"
#include "test_classes.h"
#include "BigInt/BigInt.h"
#include "BigInt_const_size.h"


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
    ASSERT_EQ(bi2.additional_code(), "+0");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}