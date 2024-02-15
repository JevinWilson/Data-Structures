#pragma once
#include <Utility>
#include <random>
#include <iostream>
#include <array_list.h>

namespace ssuds {
    enum class sortOrder {
        Ascending,
        Descending 
    };

    class ArrayListUtility {
    public:
        template <class T>
        static int quicksort(ArrayList<T>& list, int left_index, int right_index, sortOrder order) {
            int swap_count = 0;
            if (left_index >= right_index) {
                // just one element -- nothing to do
                return swap_count;
            }

            int pivot_index = partition(list, left_index, right_index, order, swap_count);

            // pivot is in proper place. Sort halves on either side
            swap_count += quicksort(list, left_index, pivot_index -1, order);
            swap_count += quicksort(list, pivot_index + 1, right_index, order);
            
            return swap_count;
        }

        template <class T>
        static int binary_search(const ArrayList<T>& list, const T& value, sortOrder order) {
            // make sure list is always sorted before search
            if (!is_sorted(list, order)) {
                quicksort(list, order);
            }

            int left = 0;
            int right = list.size() - 1;

            while (left <= right) {
                // mid = halfway between left and right
                int mid = (left + right) / 2;
                // the value is at mid
                if (list[mid] == value) {
                    return mid;
                }
                // focus on left-side
                else if (list[mid] > value) {
                    right = mid - 1;
                }
                // focus on right-side
                else {
                    left = mid + 1;
                }
            }
            return -1;
        }

        template <class T>
        static int bubble_sort(ArrayList<T>& list, sortOrder order) {
            // number of elements
            int n = list.size();

            int swap_count = 0;
            // we need to do at most n passes to sort
            for (int i = 0; i < n; i++) {
                bool is_sorted = true;
                // check for out of place neighbors
                for (int j = 0; j < n - i - 1; j++) {
                    bool swap = (order == sortOrder::Ascending) ? (list[j] > list[j + 1]) : (list[j] < list[j + 1]);
                    if (swap) {
                        std::swap(list[j], list[j + 1]);
                        swap_count++;
                        is_sorted = false;
                    }
                }
                if (is_sorted) {
                    break;
                }
            }
            return swap_count;
        }

        template <class T>
        static void shuffle(ArrayList<T>& list) {
            std::random_device rd;
            std::mt19937 eng(rd());
            int n = list.size();

            // "backwards" indicies stops at 1
            for (int i = n -1; i > 0; --i) {
                std::uniform_int_distribution<> distr(0, i);
                // pick a random j (0…i)
                int j = distr(eng);
                // swap element i and j in my_list
                std::swap(list[i], list[j]);
            }
        }

        // random list generator for #4
        ArrayList<float> generate_random_list(int size) {
            std::random_device rd;
            std::mt19937 eng(rd());
            std::uniform_real_distribution<> distr(0.0, 10.0);

            ArrayList<float> list;
            for (int i = 0; i < size; i++) {
                list.append(distr(eng));
            }
            return list;
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
                // choose between ascending and descending sort https://www.geeksforgeeks.org/bool-in-c/
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

        template <class T>
        static bool is_sorted(const ArrayList<T>& list, sortOrder order) {
            if (list.size() <= 1) {
                return true;
            }

            for (size_t i = 0; i < list.size(); i++) {
                if ((order == sortOrder::Ascending && list[i - 1] > list[i]) || (order == sortOrder::Descending && list[i - 1] < list[i])) {
                    return false;
                }
            }
            return true;
        }
    };
}