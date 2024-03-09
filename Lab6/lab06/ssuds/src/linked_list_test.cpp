/*#include <gtest/gtest.h>
#include <linked_list.h>

#define EXECUTE_LINKED_LIST_TESTS 1
#if EXECUTE_LINKED_LIST_TESTS


TEST(LinkedListTest, append_and_size)
{
	ssuds::LinkedList<int> list;
	list.append(1);
	list.append(2);
	list.append(3);

	EXPECT_EQ(list.size(), 3);
}

TEST(LinkedListTest, prepend_and_size) {
	ssuds::LinkedList<float> list;
	list.append(1.0f);
	list.append(2.0f);
	list.append(3.0f);
	EXPECT_EQ(list.size(), 3);

	list.prepend(10.0f);
	EXPECT_EQ(list.size(), 4);
	EXPECT_EQ(list[0], 10.0f);
}

TEST(LinkListTest, clear) {
	ssuds::LinkedList<std::string> list;
	list.append("Hi");
	list.append("I'm");
	list.append("Jevin");
	list.clear();

	EXPECT_EQ(list.size(), 0);
}

TEST(LinkedListTest, find) {
	ssuds::LinkedList<int> list;
	list.append(1);
	list.append(2);
	list.append(3);
	list.append(4);

	auto find = list.find(3);
	ASSERT_NE(find, list.end());
	EXPECT_EQ(*find, 3);
}

TEST(LinkedListTest, find_not_found) {
	ssuds::LinkedList<int> list;
	list.append(1);
	list.append(2);
	list.append(3);
	list.append(4);

	auto find = list.find(5);
	EXPECT_EQ(find, list.end());
}

TEST(LinkedListTest, remove) {
	ssuds::LinkedList<int> list;
	list.append(1);
	list.append(2);
	list.append(3);
	list.append(4);
	
	auto remove = list.find(2);
	ASSERT_NE(remove, list.end());

	list.remove(remove);
	EXPECT_EQ(list.size(), 3);
}

#endif*/

