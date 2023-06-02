/**
 * @file sort_k_sorted_array.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=SortKSortedArray
 * @version 0.1
 * @date 2023-05-29
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */


#include "sort_k_sorted_array.h"

namespace valhalla {
    namespace arrays {
        namespace sort_k_sorted_array {
            /*

            Given an integer array whose elements may be misplaced by no more than `k` positions
            from the correct sorted order, efficiently sort it in linear time and constant space.

            Input: nums[] = [1, 4, 5, 2, 3, 7, 8, 6, 10, 9], k = 2
            Output: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]

            */

            void Solution::sortKSortedArray(std::vector<int> & nums, int k) {
                const std::vector<int>::size_type size = nums.size();

                // Sort the first k + 1 entries
                // Using efficient implementation initially
                for (std::vector<int>::size_type i = 0 ; i < k ; i++) {
                    for (std::vector<int>::size_type j = i + 1;  j < k ; j++) {
                        if (nums[i] > nums[j]) {
                            int tmp = nums[i];
                            nums[i] = nums[j];
                            nums[i] = tmp;
                        }
                    }
                }

                const std::vector<int>::size_type last = size - k;
                // Check the next entry against the kth entry.
                for (std::vector<int>::size_type idx = 1 ; idx < last ; ) {
                    if (nums[idx] > nums[idx + k]) {
                        int last = nums[idx];
                        nums[idx] = nums[idx + k];
                    } // if
                    break;
                } // for

            } // sortKSortedArray
        }
    }
}
