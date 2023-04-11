/**
 * @file minimum_removals.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=MinimumRemovals
 * @version 0.1
 * @date 2023-04-05
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <iostream>

#include "minimum_removals.h"

namespace valhalla {
    namespace arrays {
        namespace minimum_removals {
            /*

            Given an integer array, trim it such that its maximum element becomes less
            than twice the minimum, return the minimum number of removals required for
            the conversion.

            Input : [4, 6, 1, 7, 5, 9, 2]
            Output: 4
            Explanation: The trimmed array is [7, 5, 9] where 9 < 2 × 5.

            Input : [4, 2, 6, 4, 9]
            Output: 3
            Explanation: The trimmed array is [6, 4] where 6 < 2 × 4.

            */

            int Solution::findMin(std::vector<int> & nums) {
                int min = -1;
                const int size = nums.size();

                for (int start = 0 ; start < size ; start++) {
                    int max_value = nums[start];
                    int min_value = nums[start];
                    // std::cout << "start: " << start << std::endl;
                    for (int idx = start + 1 ; idx < size ; idx++) {
                        int value = nums[idx];
                        if (value < min_value) {
                            min_value = value;
                        } // if
                        if (value > max_value) {
                            max_value = value;
                        } // if

                        // std::cout << "max_value: " << max_value << ", min_value: " << min_value << ", (min_value * 2): " << (min_value * 2) << std::endl;
                        if (max_value < (min_value * 2) && (min == -1 || (size - idx + start - 1) < min)) {
                            min = size - idx + start - 1;
                            // std::cout << "[";
                            // for (int i = start ; i <= idx ; i++)
                            //     std::cout << " " << nums[i];
                            // std::cout << " ] min=" << min << std::endl;
                        } // if
                    } // for
                } // for

                return (min == -1) ? 0 : min;
            } // findMin
        }
    }
}
