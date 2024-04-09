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
            return mData.find(node) != mData.end();
        }

        void add_edge(const N& start, const N& dest, const E& val) {
            if (!contains_node(start) || !contains_node(dest)) {
                throw std::invalid_argument("One or both nodes do not exist in the graph");
            }
            mData[start].push_back(std::make_pair(dest, val));
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