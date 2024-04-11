#pragma once

#include <iostream>
#include <unordered_map>
#include <vector>

namespace ssuds
{
    template <class N, class E>
    class Graph
    {
    private:
        std::unordered_map<N, std::vector<std::pair<N, E>>> mData;

    public:
        /// @brief adds new node to the graph
        /// @param node the node to be added
        void add_node(const N& node) {
            if (!contains_node(node)) {
                mData[node] = std::vector<std::pair<N, E>>();
            }
        }

        /// @brief checks if a node exists in the graph
        /// @param node the node to be searched
        /// @return true if found, false if not
        bool contains_node(const N& node) {
            return mData.find(node) != mData.end();
        }

        /// @brief adds new edge between nodes in the graph
        /// @param start the starting node of the edge
        /// @param dest the destination node of the edge
        /// @param val he value of the edge
        void add_edge(const N& start, const N& dest, const E& val) {
            if (!contains_node(start) || !contains_node(dest)) {
                throw std::invalid_argument("One or both nodes do not exist in the graph");
            }
            mData[start].push_back(std::make_pair(dest, val));
        }

        /// @brief checks if an edge exists between nodes
        /// @param start the start node of edge
        /// @param dest the destination node of edge
        /// @return is true if an edge exists between the start and destination nodes, false otherwise
        bool contains_edge(const N& start, const N& dest) {
            if (contains_node(start)) {
                for (const auto& pair : mData[start]) {
                    if (pair.first == dest) {
                        return true;
                    }
                }
            }
            return false;
        }

        /// @brief removes node from the graph
        /// @param node the node to be removed
        void remove_node(const N& node) {
            if (!contains_node(node)) return;

            mData.erase(node);

            for (auto& pair : mData) {
                auto it = pair.second.begin();
                while (it != pair.second.end()) {
                    if (it->first == node) {
                        it = pair.second.erase(it);
                    } else {
                        ++it;
                    }
                }
            }
        }

        /// @brief removes an edge from the graph
        /// @param start the start of the edge to be removedd
        /// @param dest the destination of the edge to be removed
        void remove_edge(const N& start, const N& dest) {
            if (contains_node(start)) {
                auto& edges = mData[start];
                auto it = edges.begin();
                while (it != edges.end()) {
                    if (it->first == dest) {
                        it = edges.erase(it);
                    } 
                    else {
                        ++it;
                    }
                }
            }
        }

        /// @brief gets the value of an edge
        /// @param start the starting node of edge
        /// @param dest the destination node of edge
        /// @return the value of the edge, throws error if edge does not exist
        E get_edge(const N& start, const N& dest) {
            if (!contains_edge(start, dest)) {
                throw std::invalid_argument("Edge does not exist");
            }

            for (const auto& pair : mData[start]) {
                if (pair.first == dest) {
                    return pair.second;
                }
            }
            throw std::runtime_error("Edge does not exist");
        }

        /// @brief overloads graph to out put in a readable way
        /// @param os the ostream where he graph will be printed
        /// @param graph the object being outputted
        /// @return reference to the input (os)
        friend std::ostream& operator<<(std::ostream& os, const Graph& graph) {
            for (const auto& pair : graph.mData) {
                os << pair.first << " |";
                for (const auto& edge : pair.second) {
                    os << " (" << edge.first << ":" << edge.second << ")";
                }
                os << std::endl;
            }
            return os;
        }
    
    };
}