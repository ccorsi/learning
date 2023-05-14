/**
 * @file coin_change_problem_two.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=CoinChangeProblemII
 * @version 0.1
 * @date 2023-05-03
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "coin_change_problem_two.h"

#include <algorithm>
#include <set>
#include <iostream>

namespace valhalla {
    namespace arrays {
        namespace coin_change_problem_two {
            /*

            Given an unlimited supply of coins of given denominations, find the total number of
            distinct ways to get the desired change.

            Input: S = [1, 3, 5, 7], target = 8
            Output: 6
            Explanation: The total number of ways is 6

            [1, 7]
            [3, 5]
            [1, 1, 3, 3]
            [1, 1, 1, 5]
            [1, 1, 1, 1, 1, 3]
            [1, 1, 1, 1, 1, 1, 1, 1]


            Input: S = [1, 2, 3], target = 4
            Output: 4
            Explanation: The total number of ways is 4

            [1, 3]
            [2, 2]
            [1, 1, 2]
            [1, 1, 1, 1]

            */

            int Solution::findWays(std::vector<int> const & S, int target) {
                int ways = 0;

                // Make a copy of the array
                std::vector<int> nums = S;

                // Sort the array in increasing order.
                std::sort(nums.rbegin(), nums.rend());

                const int size = nums.size();

                int idx = 0;

                // skip all values that are larger than the target
                while (idx < size && nums[idx] > target) idx++;

                while (idx < size) {
                    const int value = nums[idx++];
                    int sum = value;
                    while (sum <= target) {
                        findWay(nums, target, idx, sum, ways);
                        sum += value;
                    } // while
                } // while

                return ways;
            } // findWays

            void Solution::findWay(std::vector<int> const & nums, int target, int idx, int sum, int & ways) {
                if (target == sum) {
                    ways++;
                }

                const int size = nums.size();

                // skip all values that its sum is greater than target
                while (idx < size && sum + nums[idx] > target) idx++;

                while (idx < size) {
                    const int value = nums[idx++];
                    int total = sum + value;
                    while (total <= target) {
                        findWay(nums, target, idx, total, ways);
                        total += value;
                    } // while
                } // while
            }
        }
    }
}
