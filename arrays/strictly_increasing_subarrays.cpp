/**
 * @file strictly_increasing_subarrays.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=StrictlyIncreasingSubarrays
 * @version 0.1
 * @date 2023-03-31
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */


#include "strictly_increasing_subarrays.h"

namespace valhalla {
    namespace arrays {
        namespace strictly_increasing_subarrays {
            /*

            Given an integer array, count the total number of strictly
            increasing contiguous subarrays in it.

            Input: [1, 2, 4, 4, 5]
            Output: 4
            Explanation: The total number of strictly increasing subarrays
            are [1, 2], [1, 2, 4], [2, 4], [4, 5]

            Input: [1, 3, 2]
            Output: 1
            Explanation: The total number of strictly increasing subarrays
            is [1, 3]

            Input: [5, 4, 3, 2, 1]
            Output: 0
            Explanation: The total number of strictly increasing subarrays
            is 0

            */

            int Solution::getCount(std::vector<int> const & nums) {
                int count = 0;

                if ( ! nums.empty() ) {
                    const int size = nums.size();
                    int last = nums[0];
                    int in_a_row = 0;

                    for (int idx = 1 ; idx < size ; idx++) {
                        if (last < nums[idx]) {
                            count++;
                            count += in_a_row;
                            in_a_row++;
                        } else {
                            in_a_row = 0;
                        } // else
                        last = nums[idx];
                    } // for
                } // if

                return count;
            } // getCount
        }
    }
}
