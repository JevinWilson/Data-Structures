#pragma once
#include <iostream>

// Note: in C++, a general tempate (like this one) must be defined inline
// entirely in the .h file (no .cpp files).  So, in this lab, array_list.cpp
// contents are moved here

namespace ssuds
{
	template <class T>
	class LinkedList {
	protected:
		struct Node {
			T mData;
			Node* mNext;
			Node* mPrev;

			Node(const T& data, Node* prev = nullptr, Node* next = nullptr) : mData(data), mPrev(prev), mNext(next) {
				// constructor for node
			}
		};
		Node* mHead;
		Node* mTail;

	public:
		LinkedList() : mHead(nullptr), mTail(nullptr) {
			// default constructor
		}

		// destructor, deletes all nodes
		~LinkedList() {
			Node* current = mHead;
			while (current != nullptr) {
				Node* next = current -> mNext;
				delete current;
				current = next;
			}
		}

		unsigned int size() const {
			unsigned int count = 0;
			Node* current = mHead;
			while (current != nullptr) {
				count++;
				current = current -> mNext;
			}
			return count;
		}

		T& operator[](unsigned int index) const {
			if (index >= size())
				throw std::out_of_range("Out of range");

			Node* current = nullptr;
			if (index < size() / 2) {
				current = mHead;
				for (unsigned int i = 0; i < index; i++)
					current = current -> mNext;
			}
			else {
				current = mTail;
				for (unsigned int i = size() - 1; i > index; i--)
					current = current -> mPrev;
			}
			return current -> mData;
		}

		void append(const T& data) {
			// allocate memory
			Node* newNode = new Node(data);
			// if empty, make newNode the head and tail
			if (mHead == nullptr) {
				mHead = newNode;
				mTail = newNode;
			}
			else {
				// list is not empty, so add newNode to end(tail)
				mTail -> mNext = newNode;
				// set newNode's previous pointer to the tail
				newNode -> mPrev = mTail;
				// set the tail to newNode
				mTail = newNode;
			}
		}

		void prepend(const T& data) {
			// allocte memory
			Node* newNode = new Node(data, nullptr, mHead);
			// if empty, make newNode the head and tail
			if (mHead == nullptr) {
				mTail = newNode;
			}
			else {
				mHead -> mPrev = newNode;
			}
			// set newNode's next pointer to the head
			mHead = newNode;
		}

		friend std::ostream& operator<<(std::ostream& os, const LinkedList<T>& list) {
			os << "AL: [";
			Node* current = list.mHead;
			while (current != nullptr) {
				os << current -> mData;
				current = current -> mNext;
				if (current != nullptr) {
					os << ", ";
				}
			}
			os << "]";
			return os;
		}

		void clear() {
			Node* current = mHead;
			while (current != nullptr) {
				Node* next = current -> mNext;
				delete current;
				current = next;
			}
			mHead = nullptr;
			mTail = nullptr;
		}
		
	};
}
