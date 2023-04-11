/**
 * @file two_sum_two.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=TwoSumII
 * @version 0.1
 * @date 2023-04-05
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <iostream>

#include "two_sum_two.h"

namespace valhalla {
    namespace arrays {
        namespace two_sum_two {
            /*

            Given a circularly sorted integer array, find a pair with a given sum.
            Assume there are no duplicates in the array, and the rotation is in an
            anti-clockwise direction around an unknown pivot.

            • The solution can return pair in any order.

            Input : nums[] = [10, 12, 15, 3, 6, 8, 9], target = 18
            Output: (3, 15) or (15, 3)

            Input : nums[] = [5, 8, 3, 2, 4], target = 12
            Output: (4, 8) or (8, 4)

            • If no pair with the given sum exists, the solution should return the
              pair (-1, -1).

            Input : nums[] = [9, 15, 2, 3, 7], target = 20
            Output: (-1, -1)

            */

            std::pair<int,int> Solution::findPair(std::vector<int> const & nums, int target) {
                const int size =  nums.size();

                if (size > 0) {
                    const int increment = size - 1;
                    int start = 0;

                    for ( ; start < size && nums[start] < nums[(start + 1) % size] ; start = (start + 1) % size) ;

                    // std::cout << "start: " << start << std::endl;

                    for (int i = 0 ; i < size ; i++) {
                        int index = start - i;
                        if (index < 0) {
                            index += size;
                        }
                        int value = nums[index];
                        for (int j = (index + increment) % size ; j != start ; j = (j + increment) % size) {
                            if (value + nums[j] == target) {
                                return std::pair<int,int>(nums[index], nums[j]);
                            } // if
                        } // for
                    } // for
                } // if

                return std::pair<int,int>(-1,-1);

                /*
                    Version 1
                    This is an incomplete version that doesn't find the expected pair.  It doesn
                    correctly find a pair that satisfies the target but it isn't producing the
                    expected pair.

                const int size =  nums.size();

                for (int start = 0 ; start < size ; start++) {
                    int value = nums[start];
                    for (int idx =  start + 1 ; idx < size ; idx++) {
                        if (value + nums[idx] == target) {
                            return std::pair<int,int>(value, nums[idx]);
                        }
                    } // for
                } // for

                return std::pair<int,int>(-1,-1);
                */
            } // findPair
        }
    }
}
