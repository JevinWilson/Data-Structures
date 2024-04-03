#include <gtest/gtest.h>
#include <hash_table.h>

TEST(HashMapTests, FindTest) {
    ssuds::HashMap<std::string, int> Map;

    Map["Bob"] = 42;
    Map["Sue"] = 99;
    Map["carl"] = -1;

    auto it = Map.find("Bob");
    ASSERT_NE(it, Map.end());
    EXPECT_EQ((*it).value, 42);
}

TEST(HashMapTests, RemoveContainsTest) {
    ssuds::HashMap<std::string, int> Map;

    Map["Bob"] = 42;
    Map["Sue"] = 99;
    Map["carl"] = -1;

    bool remove = Map.remove("Bob");
    EXPECT_TRUE(remove);

    auto it = Map.find("Bob");
    EXPECT_EQ(it, Map.end());
    EXPECT_FALSE(Map.contains("Bob"));
}
