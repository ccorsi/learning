/**
 * @file check_min_heap.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=CheckMinHeap
 * @version 0.1
 * @date 2025-04-12
 *
 * @copyright Copyright (c) 2025 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "check_min_heap.h"

namespace valhalla {

namespace heap {

namespace check_min_heap {

/*

Given an integer array, check if it represents min-heap or not.

Input : [2, 3, 4, 5, 10, 15]
Output: true
Explanation: The input represents a min-heap.

		   2
		 /   \
		/	  \
	   3	   4
	  / \	  /
	 /   \   /
	5	 10 15

Input : [2, 10, 4, 5, 3, 15]
Output: false
Explanation: The input is not a min-heap, as it violate the heap property.

		   2
		 /   \
		/	  \
	   10	   4
	  / \	  /
	 /   \   /
	5	  3 15

*/

bool Solution::checkMinHeap(std::vector<int> const & nums) {
    if (nums.empty() == false) {
        const int size = static_cast<int>(nums.size());

        /* check the order of the array to determine if the entries are properly inserted */

        /*
            A heap is sorted depending on the index we are looking at.  For index i, we have
            the following condition:
                - entry i is less or equal than entry 2i + 2
                - entry i is less or equal than entry 2i + 1
        */
        for (int idx = 0 ; idx < size ; idx++) {
            // check the left entry
            if ((2 * idx + 1) < size && (nums[idx] > nums[2 * idx + 1]))
                return false;
            // check the right entry
            if ((2 * idx + 2) < size && (nums[idx] > nums[2 * idx + 2]))
                return false;
        } // for (int idx = 0 ; idx < size ; idx++)
    } // if (nums.empty() == false)

    return true;
} // checkMinHeap

} // namespace check_min_heap

} // namespace heap

} // namespace valhalla
