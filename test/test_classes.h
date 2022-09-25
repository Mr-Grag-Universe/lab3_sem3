//
// Created by Stephan on 17.09.2022.
//

#ifndef LAB2_SEM3_TEST_CLASSES_H
#define LAB2_SEM3_TEST_CLASSES_H
#include "gtest/gtest.h"

class Test1 : public ::testing::Test
{
public:
    virtual void SetUp() {
    }
    virtual void TearDown() {

    }
protected:
protected:
};

class Test2 : public  ::testing::Test {
public:
protected:
};

#endif //LAB2_SEM3_TEST_CLASSES_H
