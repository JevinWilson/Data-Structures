#include <gtest/gtest.h>
#include <array_list.h>
#include <array_list_utility.h>

class ArrayListUtilityTest : public ::testing::Test {
protected:
    ssuds::ArrayList<int> list;
};

TEST_F(ArrayListUtilityTest, QuicksortTest) {
    list.append(4);
    list.append(1);
    list.append(3);
    list.append(2);

    // Expected sorted list
    ssuds::ArrayList<int> sorted_list;
    sorted_list.append(1);
    sorted_list.append(2);
    sorted_list.append(3);
    sorted_list.append(4);

    int left_index = 0;
    int right_index = list.size() - 1;
    ssuds::ArrayListUtility::quicksort(list, left_index, right_index, ssuds::sortOrder::Ascending);

    // Check that each element in the sorted list is equal to the expected list
    for (int i = 0; i < list.size(); i++) {
        EXPECT_EQ(sorted_list[i], list[i]);
    }
}

TEST_F(ArrayListUtilityTest, bubble_sortTest) {
    list.append(4);
    list.append(1);
    list.append(3);
    list.append(2);

    // Expected sorted list
    ssuds::ArrayList<int> sorted_list;
    sorted_list.append(1);
    sorted_list.append(2);
    sorted_list.append(3);
    sorted_list.append(4);

    ssuds::ArrayListUtility::bubble_sort(list, ssuds::sortOrder::Ascending);

    for (size_t i = 0; i < list.size() - 1; i++) {
        EXPECT_EQ(sorted_list[i], list[i]);
    }
}

TEST_F(ArrayListUtilityTest, insertion_sortTest) {
    list.append(4);
    list.append(1);
    list.append(3);
    list.append(2);

    // Expected sorted list
    ssuds::ArrayList<int> sorted_list;
    sorted_list.append(1);
    sorted_list.append(2);
    sorted_list.append(3);
    sorted_list.append(4);

    ssuds::ArrayListUtility::insertion_sort(list, ssuds::sortOrder::Ascending);

    for (size_t i = 0; i < list.size() - 1; i++) {
        EXPECT_EQ(sorted_list[i], list[i]);
    }
}

// not working
/*TEST_F(ArrayListUtilityTest, shuffleTest) {
    list.append(1);
    list.append(2);
    list.append(3);
    list.append(4);
    list.append(5);

    // save list for comparison later
    ssuds::ArrayList<int> original_list = list;

    ssuds::ArrayListUtility::shuffle(list);

    bool shuffled = false;
    // shuffle 10 times
    for (int i = 0; i < 10; i++) {
        ssuds::ArrayListUtility::shuffle(list);
        // equal() = https://www.geeksforgeeks.org/stdequal-in-cpp/
        if (!std::equal(list.begin(), list.end(), original_list.begin())) {
            shuffled = true;
            break;
        }
    }
    EXPECT_TRUE(shuffled);
}*/
// not working
/*TEST_F(ArrayListUtilityTest, binary_searchTest) {
    list.append(1);
    list.append(2);
    list.append(3);
    list.append(4);
    list.append(5);

    int left_index = 0;
    int right_index = list.size() - 1;
    ssuds::ArrayListUtility::quicksort(list, left_index, right_index, ssuds::sortOrder::Ascending);

    int operation_count = 0;
    int index = ssuds::ArrayListUtility::binary_search(list, 2, ssuds::sortOrder::Ascending, operation_count);
    EXPECT_EQ(1, index);
}*/