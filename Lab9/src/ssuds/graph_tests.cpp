#include <gtest/gtest.h>
#include <graph.h>

TEST(GraphTests, AddAndContainsNodeTest) {
    ssuds::Graph<std::string, float> graph;

    graph.add_node("A");
    graph.add_node("B");
    graph.add_node("C");

    EXPECT_EQ(graph.contains_node("A"), true);
    EXPECT_EQ(graph.contains_node("B"), true);
    EXPECT_EQ(graph.contains_node("C"), true);
}

TEST(GraphTest, AddAndContainsEdgeTest) {
    ssuds::Graph<std::string, float> graph;

    graph.add_node("A");
    graph.add_node("B");
    graph.add_node("C");

    graph.add_edge("A", "B", 1.1);
    graph.add_edge("B", "C", 2.2);
    graph.add_edge("A", "C", 3.3);

    EXPECT_EQ(graph.contains_edge("A", "B"), true);
    EXPECT_EQ(graph.contains_edge("B", "C"), true);
    EXPECT_EQ(graph.contains_edge("A", "C"), true);
}

TEST(GraphTests, RemoveNodeTest) {
    ssuds::Graph<std::string, float> graph;

    graph.add_node("A");
    graph.add_node("B");
    graph.add_node("C");
    graph.remove_node("A");

    EXPECT_EQ(graph.contains_node("A"), false);
}

TEST(GraphTests, RemoveEdgeTest) {
    ssuds::Graph<std::string, float> graph;

    graph.add_node("A");
    graph.add_node("B");
    graph.add_node("C");
    graph.add_edge("A", "B", 1.1);
    graph.add_edge("B", "C", 2.2);
    graph.add_edge("A", "C", 3.3);
    graph.remove_edge("A", "B");

    EXPECT_EQ(graph.contains_edge("A", "B"), false);
}

TEST(GraphTests, GetEdgeTest) {
    ssuds::Graph<std::string, float> graph;

    graph.add_node("A");
    graph.add_node("B");
    graph.add_node("C");
    graph.add_edge("A", "B", 1.1);
    graph.add_edge("B", "C", 2.2);
    graph.add_edge("A", "C", 3.3);

    EXPECT_FLOAT_EQ(graph.get_edge("A", "B"), 1.1);
}