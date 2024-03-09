#pragma once

#include <linked_list.h>

namespace ssuds 
{
    template <class T>
    // has-a 
    class stack 
    {
    protected:
        LinkedList<T> mList;
    public:
        void push(const T& val) {
            mList.prepend(val);
        }

        T pop() {
            if (mList.size() == 0)
                throw std::out_of_range("Out of range");
            T val = mList[0];
            mList.remove(0);
            return val;
        }

        T top() const {
            if (mList.size() == 0) 
                throw std::out_of_range("out of range");
            return mList[0];
        }

        bool empty() const {
            return mList.size() == 0;
        }

        size_t size() const {
            return mList.size();
        }
    };
}
