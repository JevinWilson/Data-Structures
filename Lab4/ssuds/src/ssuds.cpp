// ssuds.cpp : This file contains the 'main' function. Program execution begins and ends there.

//#define MAIN_PROGRAM_1 // comment to run the first program


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
//#define MAIN_PROGRAM_1

#else
// MAIN_PROGRAM_2
int main() {
    std::ofstream out_file("times.csv");
    if (!out_file.is_open()) {
        std::cerr << "couldn't open" << std::endl;
        return 1;
    }

    out_file << "shuffle_time, copy_time, merge_sort_time, bubble_sort_time, binary_search_time, find_time, shuffle_op, merge_sort_op, bubble_sort_op, binary_search_op\n";

    for (int size = 1000; size <= 250000; size += 5000) {
        std::cout << "size: " << size << std::endl;
        ssuds::ArrayList<float> list = ssuds::ArrayListUtility::generate_random_list(size);

        // i. shuffle the ArrayList
        int shuffle_op = 0;
        auto shuffle_start = std::chrono::high_resolution_clock::now();
        //std::cout << "Shuffling list..." << std::endl;
        shuffle_op = ssuds::ArrayListUtility::shuffle(list);
        //std::cout << "Shuffling completed." << std::endl;
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
        int merge_sort_op = 0;
        auto merge_sort_start = std::chrono::high_resolution_clock::now();
        //std::cout << "merge_sort" << std::endl;
        ssuds::ArrayListUtility::merge_sort(list, 0, list.size() - 1, merge_sort_op);
        //std::cout << "merge_sort completed." << std::endl;
        auto merge_sort_end = std::chrono::high_resolution_clock::now();
        auto merge_sort_time = std::chrono::duration_cast<std::chrono::milliseconds>(merge_sort_end - merge_sort_start).count();

        // v. sort the copy using bubble_sort
        int bubble_sort_op = 0;
        auto bubble_sort_start = std::chrono::high_resolution_clock::now();
        //std::cout << "bubble_sort" << std::endl;
        bubble_sort_op = ssuds::ArrayListUtility::bubble_sort(copy, ssuds::sortOrder::Ascending);
        //std::cout << "bubble_sort completed." << std::endl;
        auto bubble_sort_end = std::chrono::high_resolution_clock::now();
        auto bubble_sort_time = std::chrono::duration_cast<std::chrono::milliseconds>(bubble_sort_end - bubble_sort_start).count();

        // vi. find an element using binary_search
        int binary_search_op = 0;
        auto binary_search_start = std::chrono::high_resolution_clock::now();
        //std::cout << "binary_search" << std::endl;
        int b_search_index = ssuds::ArrayListUtility::binary_search(list, start_value, ssuds::sortOrder::Ascending, binary_search_op);
        //std::cout << "binary_search completed." << std::endl;
        auto binary_search_end = std::chrono::high_resolution_clock::now();
        auto binary_search_time = std::chrono::duration_cast<std::chrono::milliseconds>(binary_search_end - binary_search_start).count();

        // vii. find an element (linear search)
        auto find_start = std::chrono::high_resolution_clock::now();
        //std::cout << "find" << std::endl;
        int find_index = list.find(start_value);
        //std::cout << "find completed." << std::endl;
        auto find_end = std::chrono::high_resolution_clock::now();
        auto find_time = std::chrono::duration_cast<std::chrono::milliseconds>(find_end - find_start).count();

        out_file << shuffle_time << ", " << copy_time << ", " << merge_sort_time << ", " << bubble_sort_time << ", " << binary_search_time << ", " << find_time << ", " << shuffle_op << ", " << merge_sort_op << ", " << bubble_sort_op << ", " << binary_search_op << "\n";
        //out_file.flush();
    }
    out_file.close();
    //std::cout << "done" << std::endl;
    return 0;
}

// PC got to hot at size of 151,000

#endif


