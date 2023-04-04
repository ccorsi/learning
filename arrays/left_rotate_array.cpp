/**
 * @file left_rotate_array.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=LeftRotateArray
 * @version 0.1
 * @date 2023-04-03
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <iostream>

#include "left_rotate_array.h"

namespace valhalla {
    namespace arrays {
        namespace left_rotate_array {
            /*

            Given an integer array, left-rotate it by `k` positions,
            where `k` is a postive integer.

            Input: nums[] = [1, 2, 3, 4, 5], k = 2
            Output: [3, 4, 5, 1, 2]

            Input: nums[] = [1, 2, 3, 4, 5], k = 6
            Output: [1, 2, 3, 4, 5]

            */

            void Solution::leftRotate(std::vector<int> & nums, int k) {
                const int size = nums.size();
                if ( size > 0 && k > 0 ) {
                    // We can only rotate left the minimum between k and size
                    k =  (k < size) ? k : size;
                    while (k-- > 0) {
                        int last = nums[0];

                        for (int idx = 1 ; idx < size ; idx++) {
                            nums[idx - 1] = nums[idx];
                        } // for

                        nums[size - 1] = last;
                    } // while
                } // if
            } // leftRotate
        }
    }
}
