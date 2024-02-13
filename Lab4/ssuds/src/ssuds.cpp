// ssuds.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <gtest/gtest.h>


int main()
{
    // Invoke all google test fixtures we've registered
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
