#pragma once

#include <linked_list.h>

namespace ssuds 
{
    template <class T>
    // is-a 
    class queue : private LinkedList<T> 
    {
    public:
        void enqueue(const T& val) {
            this->append(val);
        }

        T dequeue() {
            if (this -> size() == 0)
                throw std::out_of_range("out of range");
            T val = (*this)[0];
            this -> remove(0);
            return val;
        }

        T head() const {
            if (this -> size() == 0)
                throw std::out_of_range("out of range");
            return (*this)[0];
        }

        bool empty() {
            return this -> size() == 0;
        }

        size_t size() const {
            return LinkedList<T>::size();
        }

        using LinkedList<T>::begin;
        using LinkedList<T>::end;
    };
}

