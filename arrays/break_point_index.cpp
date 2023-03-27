/**
 * @file break_point_index.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=BreakPointIndex
 * @version 0.1
 * @date 2023-03-27
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */


#include "break_point_index.h"

namespace valhalla {
    namespace arrays {
        namespace break_point_index {
            /*

            Given an integer array, find an index that divides it into two non-empty
            contiguous subarrays having an equal sum.

            Input : [-1, 6, 3, 1, -2, 3, 3]
            Output: 2
            Explanation: The element 3 at index 2 divides the array into two non-empty
            subarrays `[-1, 6]` and `[1, -2, 3, 3]` having the same sum.

            • The solution should return -1 if no partition is possible.

            Input : [6, -5, 2, -4, 1]
            Output: -1
            Explanation: No equal sum partition possible.

            • In case multiple partitions is possible, return the index of the first
              partition.

            Input : [-1, -2, 2, -3]
            Output: 1
            Explanation: The index 1 and 2 divides the array into two equal sum
            subarrays. The solution should return index 1.

            Input : [4, 2, -3, 4, -1, 0, 4]
            Output: 1
            Explanation: The index 1 and 3 divides the array into two equal sum
            subarrays. The solution should return index 1.

            */

            int Solution::findBreakPoint(std::vector<int> const & nums) {
                int breakpoint = -1;
                const int size = nums.size();

                if (size > 2) {
                    int sum = 0;

                    for (int value : nums) {
                        sum += value;
                    } // for

                    const int last = size - 1;
                    int current = nums[0];
                    sum -= current;

                    for (int idx = 1 ; idx < last ; idx++) {
                        sum -= nums[idx];
                        if (sum == current) {
                            breakpoint = idx;
                            break;
                        } // if
                        current += nums[idx];
                    } // for
                } // if

                return breakpoint;
            } // findBreakPoint
        }
    }
}
