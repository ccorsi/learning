/**
 * @file three_sum_three.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=3SumIII
 * @version 0.1
 * @date 2023-03-19
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <algorithm>

#include "three_sum_three.h"

/*

Given an unsorted integer array, find all triplets in it with sum less than or equal to
a given number.

Input : nums[] = [2, 7, 4, 9, 5, 1, 3], target = 10
Output: {[1, 2, 3], [1, 2, 4], [1, 2, 5], [1, 2, 7], [1, 3, 4], [1, 3, 5], [1, 4, 5], [2, 3, 4], [2, 3, 5]}

Input : nums[] = [3, 5, 7, 3, 2, 1], target = 5
Output: {}

Since the input can have multiple triplets with sum less than or equal to the target, the
solution should return a set containing all the distinct triplets in any order.

*/

namespace valhalla {
    namespace arrays {
        namespace three_sum_three {
            std::set<std::vector<int>> Solution::getTriplets(std::vector<int> & nums, int target) {
                std::set<std::vector<int>> results;

                const int last = nums.size() - 2;

                std::vector<int> result;

                for (int idx = 0 ; idx < last ; idx++) {
                    result.push_back(nums[idx]);
                    isTriplets(nums, target, results, idx + 1, result, nums[idx], 1);
                    result.pop_back();
                } // for

                return results;
            } // getTriplets

            void Solution::isTriplets(std::vector<int> & nums, const int target, std::set<std::vector<int>> & results, const int start, std::vector<int> & result, const int sum, const int count) {
                if (count == 3) {
                    if (sum <= target) {
                        std::vector<int> expected(result);
                        std::sort(expected.begin(), expected.end());
                        results.insert(expected);
                    }
                    return;
                } // if

                const int last = nums.size() - 2 + count;

                for (int idx = start ; idx < last ; idx++) {
                    result.push_back(nums[idx]);
                    isTriplets(nums, target, results, idx + 1, result, sum + nums[idx], count + 1);
                    result.pop_back();
                } // for
            }

        }
    }
}
