/**
 * @file four_sum.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=4Sum
 * @version 0.1
 * @date 2023-03-20
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <algorithm>

#include "four_sum.h"

namespace valhalla {
    namespace arrays {
        namespace four_sum {
            /*

            Given an unsorted integer array, find all quadruplets (i.e., four elements tuple)
            having a given sum.

            Input : nums = [2, 7, 4, 0, 9, 5, 1, 3], target = 7
            Output: {[0, 1, 2, 4]}

            Since the input can contain multiple quadruplets that sum to a given target, the
            solution should return a set containing all the quadruplets.

            Input : nums = [2, 7, 4, 0, 9, 5, 1, 3], target = 20
            Output: {[0, 4, 7, 9], [1, 3, 7, 9], [2, 4, 5, 9]}

            Note: The order of elements doesn't matter in a quadruplet, and any permutation
            is allowed in the output. For example, the output set can contain quadruplets
            [9, 1, 7, 3] and [9, 3, 7, 1], but system treats them the same.

            */

            std::set<std::vector<int>> Solution::findQuadruplets(std::vector<int> const & nums, int target) {
                std::set<std::vector<int>> results;

                const int size = nums.size();

                if (size > 0) {
                    for (int idx_1 = 0 ; idx_1 < size ; idx_1++) {
                        int sum = nums[idx_1];
                        for (int idx_2 = idx_1 + 1 ; idx_2 < size ; idx_2++) {
                            sum += nums[idx_2];
                            for (int idx_3 = idx_2 + 1 ; idx_3 < size ; idx_3++) {
                                sum += nums[idx_3];
                                for (int idx_4 = idx_3 + 1 ; idx_4 < size ; idx_4++) {
                                    sum += nums[idx_4];
                                    if (sum == target) {
                                        std::vector<int> result = {
                                            nums[idx_1], nums[idx_2], nums[idx_3], nums[idx_4]
                                        };
                                        std::sort(result.begin(), result.end());
                                        results.insert(result);
                                    } // if
                                    sum -= nums[idx_4];
                                } // for
                                sum -= nums[idx_3];
                            } // for
                            sum -= nums[idx_2];
                        } // for
                    } // for
                } // if

                return results;
            } // findQuadruplets
        }
    }
}
