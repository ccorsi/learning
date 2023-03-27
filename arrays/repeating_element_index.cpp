/**
 * @file repeating_element_index.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=RepeatingElementIndex
 * @version 0.1
 * @date 2023-03-26
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <map>

#include "repeating_element_index.h"

namespace valhalla {
    namespace arrays {
        namespace repeating_element_index {
            /*

            Given an integer array, find the minimum index of a repeating element
            in linear time and doing just a single traversal of the array.

            Input : [5, 6, 3, 4, 3, 6, 4]
            Output: 1
            Explanation: The minimum index of the repeating element is 1

            Input : [1, 2, 3, 4, 5, 6]
            Output: -1
            Explanation: Input doesn't contain any repeating element

            */

            int Solution::findMinIndex(std::vector<int> const & nums) {
                int min = -1;

                if ( ! nums.empty() ) {
                    const int size = nums.size();
                    std::map<int,int> processed;

                    for (int idx = 0 ; idx < size ; idx++) {
                        int value = nums[idx];
                        if (processed.find(value) != processed.end()) {
                            if (min == -1 || processed[value] < min) {
                                min = processed[value];
                            } // if
                            continue;
                        } // if
                        processed[value] = idx;
                    } // for
                } // for

                return min;
            } // findMinIndex
        }
    }
}
