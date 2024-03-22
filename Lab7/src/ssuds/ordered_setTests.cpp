#include <ordered_set.h>
#include <gtest/gtest.h>

TEST(OrderedSetTests, InsertAndSizeTest) {
    ssuds::OrderedSet<int> set;
    set.insert(1);
    set.insert(2);
    set.insert(3);
    set.insert(4);
    ASSERT_EQ(4, set.size());
}

TEST(OrderedSetTest, TraversalTest) {
    ssuds::OrderedSet<int> set;
    set.insert(3);
    set.insert(2);
    set.insert(1);
    set.insert(4);
    set.insert(5);

    std::vector<int> expected = {1, 2, 3, 4, 5};
    std::vector<int> result = set.traversal();
    ASSERT_EQ(expected, result);
}
/* don't forget to implement this
TEST(OrderedSetTest, RebalanceTest) {
    ssuds::OrderedSet<int> set;

}*/

TEST(OrderedSetTest, ClearTest) {
    ssuds::OrderedSet<int> set;
    set.insert(1);
    set.insert(2);
    set.insert(3);
    set.insert(4);
    set.clear();
    ASSERT_EQ(0, set.size());
}

TEST(OrderedSetTest, ContainsTest) {
    ssuds::OrderedSet<int> set;
    set.insert(1);
    set.insert(2);
    set.insert(3);

    ASSERT_TRUE(set.contains(1));
    ASSERT_TRUE(set.contains(2));
    ASSERT_FALSE(set.contains(4));
}

TEST(OrderedSetTest, Get_heightTest) {
    ssuds::OrderedSet<int> set;
    set.insert(1);
    set.insert(3);
    set.insert(5);
    set.rebalance();
    ASSERT_EQ(2, set.get_height());

    set.clear();
    set.insert(1);
    set.insert(2);
    set.insert(3);
    set.insert(4);
    set.rebalance();
    ASSERT_EQ(3, set.get_height());
}