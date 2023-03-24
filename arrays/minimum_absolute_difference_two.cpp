/**
 * @file minimum_absolute_difference_two.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=MinimumAbsoluteDifferenceII
 * @version 0.1
 * @date 2023-03-22
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */


#include "minimum_absolute_difference_two.h"

#include <numeric>
#include <cmath>
#include <set>

namespace valhalla {
    namespace arrays {
        namespace minimum_absolute_difference_two {
            /*

            Given an integer array, find the maximum absolute difference between the
            sum of elements of two non-overlapping contiguous subarrays in linear time.

            Input : [-3, -2, 6, -3, 5, -9, 3, 4, -1, -8, 2]
            Output: 19
            Explanation: The two subarrays are [6, -3, 5] and [-9, 3, 4, -1, -8] whose
            sum of elements are 8 and -11, respectively. So, abs(8-(-11)) or abs(-11-8) = 19.

            Input : [6, 1, 3, 7]
            Output: 9
            Explanation: The two subarrays are [1] and [3, 7] whose sum of elements
            are 1 and 10, respectively. The maximum absolute difference is abs(10-1) = 9.

            Input : [2]
            Output: 2

            Input : []
            Output: 0

            */

            int Solution::findMaxAbsDiff(std::vector<int> & nums) {
                switch (nums.size()) {
                    case 0:
                        return 0;
                    case 1:
                        return nums.front();
                    case 2:
                        return std::abs(nums[0] - nums[1]);
                } // switch

                // Use the following for memoization purposes
                // The inner pair is the start and end of the sum of the entries in nums.
                // While the outer pair first entry is the sum of that range
                std::set<std::pair<int,std::pair<int,int>>, cmp> calculated;

                int max = 0, current = 0, total = std::accumulate(nums.begin(), nums.end(), 0);

                for (int num : nums) {
                    current += num;
                    total -= num;
                    int now = std::abs(total - current);
                    if (now > max) {
                        max = now;
                    } // if
                } // for

                return max;
            } // findMaxAbsDiff
        }
    }
}
