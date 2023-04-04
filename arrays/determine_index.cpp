/**
 * @file determine_index.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=DetermineIndex
 * @version 0.1
 * @date 2023-04-03
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */


#include "determine_index.h"

namespace valhalla {
    namespace arrays {
        namespace determine_index {
            /*

            Given an integer array, determine the index of an element before
            which all elements are smaller and after which all are greater.

            Input: [4, 2, 3, 5, 1, 6, 9, 7]
            Output: 5
            Explanation: All elements before index 5 are smaller, and all
            elements after index 5 are greater.

            • In case multiple indices satisfies the problem constraints,
              the solution should return the minimum index.

            Input: [1, 2, 3, 4, 5]
            Output: 1
            Explanation: Index 1, 2, and 3 satisfies the problem constraints.
            The solution should return the minimum index, i.e., 1.

            • For invalid inputs, the solution should return -1.

            Input: [] or [1] or [1, 2] or [5, 4, 3, 2, 1]
            Output: -1

            */

            int Solution::findIndex(std::vector<int> const & nums) {
                const int size = nums.size();
                int index = -1;

                if (size > 2) {
                    // find first entry satisfying the condition
                    int max = std::max(nums[0], nums[1]), max_idx = -1;

                    int idx = 1;

                    while (idx < size && nums[idx] < max) idx++;

                    if (idx < size) {

                    } // if

                    // if (max_idx > 0) {
                    //     index = max_idx;
                    // } // if
                } // if

                return index;
            } // findIndex
        }
    }
}
