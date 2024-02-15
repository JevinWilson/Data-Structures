// ssuds.cpp : This file contains the 'main' function. Program execution begins and ends there.

#ifndef MAIN_PROGRAM_1

#include <iostream>
#include <gtest/gtest.h>
#include <array_list.h>
#include <array_list_utility.h>
#include <fstream>
#include <vector>
#include <chrono>
#include <random>


int main()
{
    // Invoke all google test fixtures we've registered
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}

#else
// MAIN_PROGRAM_2
int main() {

}

#endif
