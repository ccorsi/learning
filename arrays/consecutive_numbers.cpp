/**
 * @file consecutive_numbers.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=ConsecutiveNumbers
 * @version 0.1
 * @date 2023-03-27
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <algorithm>

#include "consecutive_numbers.h"

namespace valhalla {
    namespace arrays {
        namespace consecutive_numbers {
            /*

            Given an integer array, check if only consecutive integers form the array.

            Input : [-1, 5, 4, 2, 0, 3, 1]
            Output: true
            Explanation: The array contains consecutive integers from -1 to 5.

            Input : [4, 2, 4, 3, 1]
            Output: false
            Explanation: The array does not contain consecutive integers as element 4 is repeated.

            Input : [2, 5, 3, 1]
            Output: false
            Explanation: The array does not contain consecutive integers as element 4 is missing.

            */

            bool Solution::isConsecutive(std::vector<int> const & nums) {
                std::vector<int> values(nums);
                std::sort(values.begin(), values.end());
                const int size = nums.size();

                for (int idx = 1 ; idx < size ; idx++) {
                    if (values[idx] - 1 != values[idx-1]) {
                        return false;
                    } // if
                } // for

                return true;
            } // isConsecutive
        }
    }
}
