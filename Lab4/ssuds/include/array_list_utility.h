#pragma once
#include <Utility>
#include <array_list.h>

namespace ssuds {
    enum class sortOrder {
        Ascending,
        Descending 
    };

    class ArrayListUtility {
    public:
        template <class T>
        static int quicksort(ArrayList<T>& list, int left_index, int right_index , sortOrder order) {
            int swap_count = 0;
            if (left_index >= right_index) {
                // just one element -- nothing to do
                return swap_count;
            }

            int pivot_index = partition(list, left_index, right_index, order, swap_count);

            swap_count += quicksort(list, left_index, pivot_index -1, order);
            swap_count += quicksort(list, pivot_index + 1, right_index, order);
            
            return swap_count;
        }

    private:
        template <class T>
        static int partition(ArrayList<T>& list, int left_index, int right_index, sortOrder order, int& swap_count) {
            // get index of pivot
            int mid_index = (left_index + right_index) / 2;
            T pivot_value = list[mid_index];

            // swap last element with pivot
            std::swap(list[mid_index], list[right_index]);
            swap_count++;

            // put elements on "right" side of pivot
            int swap_index = left_index;
            for (int i = left_index; i < right_index; i++) {
                // choose between ascending and descending sort https://www.w3schools.com/cpp/cpp_booleans_expressions.asp
                bool ASCorDesc = (order == sortOrder::Ascending) ? (list[i] < pivot_value) : (list[i] > pivot_value);
                if (ASCorDesc) {
                    std::swap(list[i], list[swap_index]);
                    swap_index++;
                    swap_count++;
                }
            }

            // swap pivot to its correct position
            std::swap(list[swap_index], list[right_index]);
            swap_count++;

            // return  index of pivot value
            return swap_index;
        }
    };
}