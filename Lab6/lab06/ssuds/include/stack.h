#pragma once

#include <linked_list.h>

namespace ssuds 
{
    template <class T>
    class stack
    {
    protected:
        LinkedList<T> mList;
    private:
        void push(const T& val) {
            mList.prepend(val);
        }
    };
}
