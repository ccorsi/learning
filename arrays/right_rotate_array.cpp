/**
 * @file right_rotate_array.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=RightRotateArray
 * @version 0.1
 * @date 2023-04-03
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */


#include "right_rotate_array.h"

namespace valhalla {
    namespace arrays {
        namespace right_rotate_array {
            /*

            Given an integer array, right-rotate it by `k` positions, where `k`
            is a postive integer.

            Input: nums[] = [1, 2, 3, 4, 5], k = 2
            Output: [4, 5, 1, 2, 3]

            Input: nums[] = [1, 2, 3, 4, 5, 6, 7], k = 3
            Output: [5, 6, 7, 1, 2, 3, 4]

            Input: nums[] = [1, 2, 3, 4, 5], k = 6
            Output: [1, 2, 3, 4, 5]

            */

            void Solution::rightRotate(std::vector<int> & nums, int k) {
                const int size = nums.size();

                if (size > 0 && k > 0 && k < size) {
                    while (k-- > 0) {
                        int first = nums[size - 1];

                        for (int idx = size - 1 ; idx > 0 ; idx--) {
                            nums[idx] = nums[idx - 1];
                        } // for

                        nums[0] = first;
                    } // while
                } // if
            } // rightRotate
        }
    }
}
