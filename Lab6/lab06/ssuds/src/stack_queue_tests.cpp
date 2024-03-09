#include <gtest/gtest.h>
#include <stack.h>
#include <queue.h>

/********************** Stack Tests **********************/
TEST(StackPPTest, PushAndPopTest) {
    ssuds::stack<int> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.push(4);
    stack.push(5);
    EXPECT_EQ(stack.size(), 5);
    stack.pop();
    stack.pop();
    EXPECT_EQ(stack.size(), 3);
}

TEST(StackTopTest, TopTest) {
    ssuds::stack<int> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.push(100);
    EXPECT_EQ(stack.top(), 100);
}

TEST(StackEmptyTest, EmptyTest) {
    ssuds::stack<int> stack;
    EXPECT_EQ(stack.empty(), true);
    stack.push(1);
    EXPECT_EQ(stack.empty(), false);
}

TEST(StackSizeTest, SizeTest) {
    ssuds::stack<int> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);
    EXPECT_EQ(stack.size(), 3);
}

/********************** Queue Tests **********************/
TEST(QueueEnqDeQTest, EnqueueAndDequeueTest) {
    ssuds::queue<int> queue;
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    queue.enqueue(4);
    queue.enqueue(5);
    EXPECT_EQ(queue.size(), 5);
    queue.dequeue();
    queue.dequeue();
    EXPECT_EQ(queue.size(), 3);
}

TEST(QueueHeadTest, HeadTest) {
    ssuds::queue<int> queue;
    queue.enqueue(100);
    queue.enqueue(2);
    queue.enqueue(3);
    queue.enqueue(4);
    EXPECT_EQ(queue.head(), 100);
}

TEST(QueueEmptyTest, EmptyTest) {
    ssuds::queue<int> queue;
    EXPECT_EQ(queue.empty(), true);
    queue.enqueue(1);
    EXPECT_EQ(queue.empty(), false);
}

TEST(QueueSizeTest, SizeTest) {
    ssuds::queue<int> queue;
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    EXPECT_EQ(queue.size(), 3);
}