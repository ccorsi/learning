/**
 * @file two_diff.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=2Diff
 * @version 0.1
 * @date 2023-03-20
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <cmath>

#include "two_diff.h"

namespace valhalla {
    namespace arrays {
        namespace two_diff {
            /*

            Given an unsorted integer array, find all pairs with a given difference `k`
            in it using constant space.

            Input : nums = [1, 5, 2, 2, 2, 5, 5, 4], k = 3
            Output: {(2, 5), (1, 4)}

            Note:

            • The solution should return the pair in sorted order. For instance,
              among pairs (5, 2) and (2, 5), only pair (2, 5) appeared in the output.

            • Since the input can contain multiple pairs with a given difference, the
              solution should return a set containing all the distinct pairs.
              For instance, the pair (2, 5) appeared only once in the output.

            */

            std::set<std::pair<int,int>> Solution::findPairs(std::vector<int> const & nums, int k) {
                std::set<std::pair<int,int>> results;
                const int size = nums.size(), k_pos = std::abs(k);

                for (int left = 0 ; left < size ; left++) {
                    for (int right = left + 1 ; right < size ; right++) {
                        if (std::abs(nums[right] - nums[left]) == k_pos) {
                            results.insert(std::pair(std::min(nums[left],nums[right]), std::max(nums[left],nums[right])));
                        } // if
                    } // for
                } // for

                return results;
            } // findPairs
        }
    }
}
