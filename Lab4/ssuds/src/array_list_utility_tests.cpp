#include <gtest/gtest.h>
#include <array_list.h>
#include <array_list_utility.h>

class ArrayListUtilityTest : public ::testing::Test {
protected:
    ssuds::ArrayList<int> list;
};

TEST_F(ArrayListUtilityTest, Quicksort) {
    list.append(4);
    list.append(1);
    list.append(3);
    list.append(2);

    int left_index = 0;
    int right_index = list.size() - 1;
    ssuds::ArrayListUtility::quicksort(list, left_index, right_index, ssuds::sortOrder::Ascending);

    for (int i = 0; i < list.size() - 1; i++) {
        EXPECT_LE(list[i], list[i + 1]);
    }
}