// ssuds.cpp : This file contains the 'main' function. Program execution begins and ends there.
#define MAIN_PROGRAM_1


#include <iostream>
#include <gtest/gtest.h>
#include <array_list.h>
#include <array_list_utility.h>
#include <fstream>
#include <vector>
#include <chrono>
#include <random>

#ifndef MAIN_PROGRAM_1
int main()
{
    // Invoke all google test fixtures we've registered
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}

#else
// MAIN_PROGRAM_2
int main() {
    std::ofstream out_file("times.txt");
    if (!out_file.is_open()) {
        std::cerr << "couldn't open" << std::endl;
        return 1;
    }

    for (int size = 1000; size <= 250000; size += 5000) {
        ssuds::ArrayList<float> list = generate_random_list(size);

        // i. shuffle the ArrayList
        auto shuffle_start = std::chrono::high_resolution_clock::now();
        ssuds::ArrayListUtility::shuffle(list);
        auto shuffle_end = std::chrono::high_resolution_clock::now();
        auto shuffle_time = std::chrono::duration_cast<std::chrono::milliseconds>(shuffle_end - shuffle_start).count();

        // ii. make a copy of the ArrayList
        auto copy_start = std::chrono::high_resolution_clock::now();
        ssuds::ArrayList<float> copy(list);
        auto copy_end = std::chrono::high_resolution_clock::now();
        auto copy_time = std::chrono::duration_cast<std::chrono::milliseconds>(copy_end - copy_start).count();

        // iii. record the starting value

        // iv. sort the original using merge sort

        return 0;
    }

}

#endif
