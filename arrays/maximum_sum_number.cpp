/**
 * @file maximum_sum_number.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=MaximumSumNumber
 * @version 0.1
 * @date 2023-03-26
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <algorithm>

#include "maximum_sum_number.h"

namespace valhalla {
    namespace arrays {
        namespace maximum_sum_number {
            /*

            Given an integer array between 0 and 9, generate a pair using all the array digits
            that has the maximum sum. The difference in the number of digits of the two numbers
            should be ± 1.

            Input : [4, 6, 2, 7, 9, 8]
            Output: (974, 862)

            Input : [9, 2, 5, 6, 0, 4]
            Output: (952, 640)

            The solution can return pair in any order. If a pair cannot be formed, the solution
            should return the pair (0, 0).

            */

            std::pair<int,int> Solution::constructMaxSumNumber(std::vector<int> & nums) {
                std::pair<int,int> max_sum(0,0);

                if (nums.size() > 1) {
                    std::sort(nums.begin(), nums.end(), std::greater<int>());

                    std::vector<int>::const_iterator itr = nums.begin();

                    while (itr != nums.end()) {
                        max_sum.first *= 10;
                        max_sum.first += *itr;
                        itr++;
                        if (itr != nums.end()) {
                            max_sum.second *= 10;
                            max_sum.second += *itr;
                            itr++;
                        } // if
                    } // while
                } // if

                return max_sum;
            } // constructMaxSumNumber
        }
    }
}
