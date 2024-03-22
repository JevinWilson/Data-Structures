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

            Node(const T& val) : value(val), left(nullptr), right(nullptr) {}
        };

        Node* root;

        Node* insertRec(Node* node, const T& val) {
            if (node == nullptr) {
                return new Node(val);
            }
            if (val < node->value) {
                node->left = insertRec(node->left, val);
            }
            else if (val > node->value) {
                node->right = insertRec(node->right, val);
            }
            return node;
        }

        void traversalRec(Node* node, std::vector<T>& vec) const {
            if (node != nullptr) {
                traversalRec(node->left, vec);
                vec.push_back(node->value);
                traversalRec(node->right, vec);
            }
        }

        Node* rebalanceRec(Node* node) {
            std::vector<T> values;
            traversalRec(node, values);
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

        void clearRec(Node* &node) {
            if (node != nullptr) {
                clearRec(node->left);
                clearRec(node->right);
                delete node;
                node = nullptr;
            }
        }

        int get_heightRec(Node* node) const {
            if (node == nullptr) {
                return 0;
            }
            return 1 + std::max(get_heightRec(node->left), get_heightRec(node->right));
        }

        size_t sizeRec(Node* node) const {
            if (node == nullptr) {
                return 0;
            }
            return 1 + sizeRec(node->left) + sizeRec(node->right);
        }

        bool containsRec(Node* node, const T& val) const {
            if (node == nullptr) {
                return false;
            }
            if (val == node->value) {
                return true;
            }
            else if (val < node->value) {
                return containsRec(node->left, val);
            }
            else {
                return containsRec(node->right, val);
            }
        }

        Node* findMinimum(Node* node) const {
            Node* current = node;
            while (current && current->left != nullptr) {
                current = current->left;
            }
            return current;
        }
        Node* removeRec(Node* node, const T& val, bool &removed) {
            if (node == nullptr) {
                return nullptr;
            }
            
            if (val < node->value) {
                node->left = removeRec(node->left, val, removed);
            }
            else if (val > node->value) {
                node->right = removeRec(node->right, val, removed);
            }
            else {
                if (node->left == nullptr) {
                    Node* temp = node->right;
                    delete node;
                    removed = true;
                    return temp;
                }
                else if (node->right == nullptr) {
                    Node* temp = node->left;
                    delete node;
                    removed = true;
                    return temp;
                }

                Node* temp = findMinimum(node->right);
                node->value = temp->value;
                node->right = removeRec(node->right, temp->value, removed);
            }
            return node;
        }
    
    public:
        OrderedSet() : root(nullptr) {
            // constructor
        }

        ~OrderedSet() {
            clearRec(root);
        }

        void insert(const T& val) {
            root = insertRec(root, val);
        }

        std::vector<T> traversal() const {
            std::vector<T> vec;
            traversalRec(root, vec);
            return vec;
        }

        void rebalance() {
            root = rebalanceRec(root);
        }

        void clear() {
            clearRec(root);
        }

        size_t size() const {
            return sizeRec(root);
        }

        bool contains(const T& val) const {
            return containsRec(root, val);
        }

        int get_height() const {
            return get_heightRec(root);
        }

        bool erase(const T& val) {
            bool removed = false;
            root = removeRec(root, val, removed);
            return removed;
        }
    };
}
