/**
 * @file reverse_consecutive_elements.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=ReverseConsecutiveElements
 * @version 0.1
 * @date 2023-03-20
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <iostream>

#include "reverse_consecutive_elements.h"

namespace valhalla {
    namespace arrays {
        namespace reverse_consecutive_elements {
            /*

            Given an integer array `nums` and non-negative integers i, j, and m,
            reverse every group of consecutive `m` elements in subarray `[i, j]`.

            Input : nums[] = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10], m = 3, i = 1, j = 7
            Output: [1, 4, 3, 2, 7, 6, 5, 8, 9, 10]

            Input : nums[] = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10], m = 3, i = 1, j = 9
            Output: [1, 4, 3, 2, 7, 6, 5, 10, 9, 8]

            Input : nums[] = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10], m = 3, i = 3, j = 5
            Output: [1, 2, 3, 6, 5, 4, 7, 8, 9, 10]

            Input : nums[] = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10], m = 3, i = 3, j = 4
            Output: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]

            */

            void Solution::reverseInGroup(std::vector<int> & nums, int m, int i, int j) {
                if (m > 0 && i > -1 && i < j) {
                    for( ; i < j ; i += m) {
                        if (i + m - 1 <= j) {
                            for(int start = i, end = i + m - 1 ; start < end ; start++, end--) {
                                int temp = nums[start];
                                nums[start] = nums[end];
                                nums[end] = temp;
                            } // for
                        } // if
                    } // for
                } // if
            } // reverseInGroup
        }
    }
}
