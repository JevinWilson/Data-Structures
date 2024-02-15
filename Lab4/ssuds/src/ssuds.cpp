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
        float start_value = list[0];

        // iv. sort the original using merge sort
        auto merge_sort_start = std::chrono::high_resolution_clock::now();
        ssuds::ArrayListUtility::merge_sort(list, 0, list.size() - 1);
        auto merge_sort_end = std::chrono::high_resolution_clock::now();
        auto merge_sort_time = std::chrono::duration_cast<std::chrono::milliseconds>(merge_sort_end - merge_sort_start).count();

        // v. sort the copy using bubble_sort
        auto bubble_sort_start = std::chrono::high_resolution_clock::now();
        ssuds::ArrayListUtility::bubble_sort(copy, ssuds::sortOrder::Ascending);
        auto bubble_sort_end = std::chrono::high_resolution_clock::now();
        auto bubble_sort_time = std::chrono::duration_cast<std::chrono::milliseconds>(bubble_sort_end - bubble_sort_start).count();

        // vi. find an element using binary_search
        auto binary_search_start = std::chrono::high_resolution_clock::now();
        int b_search_index = ssuds::ArrayListUtility::binary_search(list, start_value);
        auto binary_search_end = std::chrono::high_resolution_clock::now();
        auto binary_search_time = std::chrono::duration_cast<std::chrono::milliseconds>(binary_search_end - binary_search_start).count();

        // vii. find an element (linear search)
        auto find_start = std::chrono::high_resolution_clock::now();
        int find_index = list.find(start_value);
        auto find_end = std::chrono::high_resolution_clock::now();
        auto find_time = std::chrono::duration_cast<std::chrono::milliseconds>(find_end - find_start).count();

        return 0;
    }

}

#endif
