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
        void add_node(const N& node) {
            if (!contains_node(node)) {
                mData[node] = std::vector<std::pair<N, E>>();
            }
        }

        bool contains_node(const N& node) {
            return mData.find(node) != mData.end()
        }

        void add_edge(const N& start, const N& dest, const E& val) {
            if (contains_node(start) || !contains_node(dest)) {
                throw std::invalid_argument("One or both nodes do not exist in the graph");
            }
            mData[start].push_back(std::make_pair(dest,val));
        }

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

        void remove_node(const N& node) {
            if (!contains_node(node)) {
                return;
            }
            mData.erase(node);

            for (auto& pair : mData) {
                auto& edge = pair.second;
                edges.erase(std::remove_if(edges.begin(), edges.end(), [node](const std::pair<N, E>& edge) {
                    return edge.first == node;
                }), edges.end());
            }
        }

        void remove_edge(const N& start, const N& dest) {
            if (contains_node(start)) {
                auto& edges = mData[start];
                edges.erase(std::remove_if(edges.begin(), edges.end(), [dest](const std::pair<N, E>& pair) {
                    return pair.first == dest;
                }), edges.end());
            }
        }

        E get_edge(const N& start, const N& dest) {
            if (!contains_edge(start, dest)) {
                throw std::invalid_argument("Edge does not exist");
            }

            for (const auto& pair : mData[start]) {
                if (pair.first == dest) {
                    return pair.second;
                }
            }
        }

        friend std::ostream& operator<<(std::ostream& os, const Graph& graph) {
            for (const auto& pair : graph.mData) {
                os << node.first << " |";
                for (const auto& edge : node.second) {
                    os << " )" << edge.first << ":" << edge.second << ")"
                }
                os << std::endl
            }
            return os;
        }
    
    };
}