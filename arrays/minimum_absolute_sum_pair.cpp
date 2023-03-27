/**
 * @file minimum_absolute_sum_pair.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=MinimumAbsoluteSumPair
 * @version 0.1
 * @date 2023-03-27
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <cmath>
#include <limits>

#include "minimum_absolute_sum_pair.h"

namespace valhalla {
    namespace arrays {
        namespace minimum_absolute_sum_pair {
            /*

            Given a sorted integer array, find a pair in it having an absolute
            minimum sum.

            Input : [-6, -5, -3, 0, 2, 4, 9]
            Output: (-5, 4)
            Explanation: (-5, 4) = abs(-5 + 4) = abs(-1) = 1, which is minimum
            among all pairs.

            • Each input can have multiple solutions. The output should match
              with either one of them.

            Input : [-6, -2, 0, 1, 5]
            Output: (-6, 5) or (-2, 1) or (0, 1)

            • The solution can return pair in any order. If no pair exists,
              the solution should return the pair (-1, -1).

            Input : [1]
            Output: (-1, -1)

            */

            std::pair<int,int> Solution::findPair(std::vector<int> const & nums) {
                std::pair<int,int> min(-1,-1);

                if ( nums.size() > 1) {
                    const int size = nums.size();
                    int min_sum = INT_MAX;
                    for (int outter = 0 ; outter < size ; outter++) {
                        for (int inner = outter + 1 ; inner < size ; inner++) {
                            int sum = std::abs(nums[outter] + nums[inner]);
                            if (sum < min_sum) {
                                min_sum = sum;
                                min.first = nums[outter];
                                min.second = nums[inner];
                            } // if
                        } // for
                    } // for
                } // if

                return min;
            } // findPair
        }
    }
}
