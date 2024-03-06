// ssuds.cpp : This file contains the 'main' function. Program execution begins and ends there.
#define DO_UNIT_TESTING 1
#include <iostream>
#if DO_UNIT_TESTING
#include <gtest/gtest.h>
#else
#include <linked_list.h>
#endif

#include <fstream> 
int main()
{
#if DO_UNIT_TESTING 1
    // Invoke all google test fixtures we've registered
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
#else
    ssuds::LinkedList<int> list;
    list.append(1);
    list.append(2);
    list.append(3);
    list.append(4);
    list.clear();
    list.append(10);
    list.append(6);
    list.append(7);
    list.prepend(1);
        
    std::cout << list << std::endl;

    unsigned int list_size = list.size();
    std::cout << "Size of list: " << list_size << std::endl;

    int value_find = 1;
    auto it = list.find(value_find);
    if (it!= list.end()) {
        std::cout << "Found value: " << value_find << " at index: " << it.index() << std::endl;
    }
    else {
        std::cout << "Value not found: " << value_find << std::endl;
    }


#endif
}
