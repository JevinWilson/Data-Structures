// ssuds.cpp : This file contains the 'main' function. Program execution begins and ends there.
#define DO_UNIT_TESTING 0
#include <iostream>
#if DO_UNIT_TESTING
#include <gtest/gtest.h>
#else
#include <array_list.h>
#include <array_list_utility.h>
#include <random>
#include <fstream>
#include <chrono>
#endif


#define DO_TIMING_BUBBLE_SORT 0
#define DO_TIMING_QUCKSORT 0
#define DO_TIMING_OTHERS 1

#include <fstream> 
int main()
{
#if DO_UNIT_TESTING
    // Invoke all google test fixtures we've registered
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
#else
    // Do our stress-testing and data gathering routine
    // Now do our "stress test" -- generate a list of random floats of size 100 (and then of increasing sizes, step of 100 up to 1000000000)
    std::ofstream results("..\\..\\..\\output\\results.txt");
    std::ofstream results_csv("..\\..\\..\\output\\results.csv");
    // Reference: https://www.cplusplus.com/reference/random/
    std::default_random_engine generator;
    std::chrono::steady_clock::time_point start, end, overall_start, overall_end;
    std::uniform_real_distribution<float> distribution(-10000000.0f, 10000000.0f);
    std::mt19937 mt(generator);
    std::chrono::milliseconds elapsed;

    overall_start = std::chrono::steady_clock::now();

    results_csv << ", Copy-time";

    results_csv << ", QS - ops, QS - time";

    results_csv << ", BS - ops, BS - time";

    results_csv << ", BSearch - ops, BSearch - time, LSearch - ops, LSearch - time";
    results_csv << std::endl;

    // The quick test for testing my main
    //for (int sample_size = 1000; sample_size <= 30000; sample_size += 5000)
    // The longer test (took about x minutes in a Release build on my machine)
    for (int sample_size = 1000; sample_size <= 250000; sample_size += 5000)
    {
        std::cout << "Batch-processing sample size=" << sample_size << "...";
        // Generate the sample
        results << "SampleSize=" << sample_size << std::endl;
        results << "=========================" << std::endl;
        results_csv << sample_size << ",";
        ssuds::ArrayList<float> AL;
        for (int i = 0; i < sample_size; i++)
        {
            float num = distribution(mt);
            AL.append(num);
        }

        // Get every 10th item from our original list to find later
        ssuds::ArrayList<float> AL_find_values;
        for (int i = 0; i < sample_size; i += 10)
            AL_find_values.append(AL[i]);

        // Make a backup copy of AL
        std::cout << "copy...";
        start = std::chrono::steady_clock::now();
        ssuds::ArrayList<float> AL_copy(AL);
        end = std::chrono::steady_clock::now();
        elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        results << "\tCopy time: " << elapsed.count() << "ms" << std::endl;
        results_csv << elapsed.count() << ",";


        // Sort AL using quicksort
        std::cout << "quicksort...";
        start = std::chrono::steady_clock::now();
        unsigned long num_ops = ssuds::quicksort(AL, ssuds::SortOrder::ASCENDING);
        end = std::chrono::steady_clock::now();
        elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        results << "\tQuicksort: " << elapsed.count() << "ms and " << num_ops << " operations" << std::endl;
        results_csv << num_ops << ", " << elapsed.count() << ",";

        // Sort AL_copy using bubble-sort
        std::cout << "bubble-sort...";
        start = std::chrono::steady_clock::now();
        num_ops = ssuds::bubblesort(AL_copy, ssuds::SortOrder::ASCENDING);
        end = std::chrono::steady_clock::now();
        elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        results << "\tBubblesort: " << elapsed.count() << "ms and " << num_ops << " operations" << std::endl;
        results_csv << num_ops << ", " << elapsed.count() << ",";

        // Find all the "find values" and average our cost times
        long long bin_search_avg = 0, find_avg = 0;// Find our item with binary search
        unsigned long bin_num_ops_avg = 0, find_num_ops_avg = 0;
        std::cout << "linear-search and binary-search...";
        for (int i = 0; i < AL_find_values.size(); i++)
        {
            start = std::chrono::steady_clock::now();
            ssuds::find_binary_search(AL, ssuds::SortOrder::ASCENDING, AL_find_values[i], &num_ops);
            end = std::chrono::steady_clock::now();
            elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            bin_num_ops_avg += num_ops;
            bin_search_avg += elapsed.count();

            start = std::chrono::steady_clock::now();
            num_ops = AL.find(AL_find_values[i]);
            end = std::chrono::steady_clock::now();
            elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            find_num_ops_avg += num_ops;
            find_avg += elapsed.count();
        }

        find_avg /= AL_find_values.size();
        find_num_ops_avg /= AL_find_values.size();
        bin_num_ops_avg /= AL_find_values.size();
        bin_search_avg /= AL_find_values.size();
        
        
        results << "\tBinarySearch: " << bin_search_avg << "ms and " << bin_num_ops_avg << " operations" << std::endl;
        results_csv << bin_num_ops_avg << ", " << bin_search_avg << ",";

        // Find our item with linear search (Lab1)
        std::cout << "linear-search...";
        
        results << "\tLinear Search: " << find_avg << "ms and " << find_num_ops_avg << " operations" << std::endl;
        results_csv << find_num_ops_avg << ", " << find_avg << ",";

        std::cout << "done!" << std::endl;
        results_csv << "\n";
    }

    overall_end = std::chrono::steady_clock::now();
    std::chrono::minutes elapsed_min = std::chrono::duration_cast<std::chrono::minutes>(overall_end - overall_start);
    std::cout << "Entire test process took " << elapsed_min.count() << " minutes" << std::endl;

#endif
}
