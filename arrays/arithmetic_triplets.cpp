/**
 * @file arithmetic_triplets.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=ArithmeticTriplets
 * @version 0.1
 * @date 2023-03-20
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */


#include "arithmetic_triplets.h"

namespace valhalla {
    namespace arrays {
        namespace arithmetic_triplets {
            /*

            Given a sorted array of distinct positive integers, return all triplets that forms
            an arithmetic progression with an integral common difference. An arithmetic
            progression is a sequence of numbers such that the difference between the consecutive
            terms is constant.

            Input : [5, 8, 9, 11, 12, 15]
            Output: {[5, 8, 11], [9, 12, 15]}

            Input : [1, 3, 5, 6, 8, 9, 15]
            Output: {[1, 3, 5], [1, 5, 9], [3, 6, 9], [1, 8, 15], [3, 9, 15]}

            */

            std::set<std::vector<int>> Solution::findTriplets(std::vector<int> const & nums) {
                std::set<std::vector<int>> results;
                const int size = nums.size();

                if (size > 0) {
                    for (int idx_1 = 0 ; idx_1 < size ; idx_1++) {
                        for (int idx_2 = idx_1 + 1 ; idx_2 < size ; idx_2++) {
                            const int diff = nums[idx_2] - nums[idx_1];
                            for (int idx_3 = idx_2 + 1 ; idx_3 < size ; idx_3++) {
                                if (nums[idx_3] - nums[idx_2] == diff) {
                                    std::vector<int> result = {
                                        nums[idx_1], nums[idx_2], nums[idx_3]
                                    };
                                    results.insert(result);
                                } // if
                            } // for
                        }
                    } // for
                } // if

                return results;
            } // findTriplets
        }
    }
}
