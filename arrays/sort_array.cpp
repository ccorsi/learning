/**
 * @file sort_array.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=SortArray
 * @version 0.1
 * @date 2023-04-05
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */


#include "sort_array.h"

namespace valhalla {
    namespace arrays {
        namespace sort_array {
            /*

            Given an integer array, in-place sort it without using any inbuilt functions.

            Input : [6, 3, 4, 8, 2, 9]
            Output: [2, 3, 4, 6, 8, 9]

            Input : [9, -3, 5, -2, -8, -6]
            Output: [-8, -6, -3, -2, 5, 9]

            */

            void Solution::sort(std::vector<int> & nums) {
                quicksort(nums, 0, nums.size() - 1);
            } // sort

            void Solution::quicksort(std::vector<int> & nums, int lo, int hi) {
                // Check for termination condition
                if (lo >= hi || lo < 0) {
                    return;
                } // if

                // Determine pivot entry
                int pivot = partition(nums, lo, hi);

                // Sort the two partition
                quicksort(nums, lo, pivot - 1);
                quicksort(nums, pivot + 1, hi);
            } // quicksort

            int Solution::partition(std::vector<int> & nums, int lo, int hi) {
                // Select a pivot value
                int value = nums[hi];

                // Temporary pivot index
                int pivot = lo - 1;

                for (int i = lo ; i < hi; i++) {
                    if (nums[i] < value) {
                        pivot++;
                        int temp = nums[i];
                        nums[i] = nums[pivot];
                        nums[pivot] = temp;
                    } // if
                } // for

                pivot++;
                nums[hi] = nums[pivot];
                nums[pivot] = value;

                return pivot;
            }
        }
    }
}
