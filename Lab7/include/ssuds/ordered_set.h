#pragma once

#include <iostream>
#include <vector>

namespace ssuds 
{
    template<typename T>
    class OrderedSet
    {
    private: 
        class Node
        {
        public:
            T value;
            Node* left;
            Node* right;

            Node(const T& value) : value(val), left(nullptr), right(nullptr) {}
        };

        Node* root;

        Node* insert(Node* node, const T& val) {
            if (node == nullptr) {
                return new Node(val);
            }
            if (val < node->value) {
                node->left = insert(node->left, val);
            }
            else if (val > node->value) {
                node->right = insert(node->right, val);
            }
            return node;
        }

        void traversal(Node* node, std::vector<T>& vec) const {
            if (node != nullptr) {
                traversal(node->left, vec);
                vec.push_back(node->value);
                traversal(node->right, vec);
            }
        }

        Node* rebalance(Node* node) {
            std::vector<T> values;
            traversal(node, values);
            return rebalanceRecursion(values, 0, values.size() - 1);
        }
        Node* rebalanceRecursion(const std::vector<T>& values, int start, int end) {
            if (start > end) {
                return nullptr;
            }

            int mid = (start + end) / 2;
            Node* node = new Node(values[mid]);
            node->left = rebalanceRecursion(values, start, mid - 1);
            node->right = rebalanceRecursion(values, mid + 1, end);
            return node;
        }

        void clear(Node* &node) {
            if (node != nullptr) {
                clear(node->left);
                clear(node->right);
                delete node;
                node = nullptr;
            }
        }

        int get_height(Node* node) const {
            if (node == nullptr) {
                return 0;
            }
            return 1 + std::max(get_height(node->left), get_height(node->right));
        }

        size_t size(Node* node) const {
            if (node == nullptr) {
                return 0;
            }
            return 1 + size(node->left) + size(node->right);
        }

        bool contains(Node* node, const T& val) const {
            if (node == nullptr) {
                return false;
            }
            if (val == node->value) {
                return true;
            }
            else if (val < node->value) {
                return contains(node->left, val);
            }
            else {
                return contains(node->right, val);
            }
        }
    
    public:
        OrderedSet() : root(nullptr) {
            // constructor
        }

        ~OrderedSet() {
            clear(root);
        }

        void insert(const T& val) {
            root = insert(root, val);
        }

        std::vector<T> traversal() const {
            std::vector<T> vec;
            traversal(root, vec);
            return vec;
        }

        void rebalance() {
            root = rebalance(root);
        }

        void clear() {
            clear(root);
        }

        size_t size() const {
            return size(root);
        }

        bool contains(const T& val) const {
            return contains(root, val);
        }

        int get_height() const {
            return get_height(root);
        }
    };
}
