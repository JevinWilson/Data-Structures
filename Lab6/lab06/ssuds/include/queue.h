#pragma once

#pragma once

#include <linked_list.h>

namespace ssuds 
{
    template <class T>
    class queue : private LinkedList<T> {
        void enqueue(const T& new_val) {
            this->append(new_val);
            LinkedList<T>::append(new_val)
        }
    public:
        using LinkedList<T>::begin;
    };
}

