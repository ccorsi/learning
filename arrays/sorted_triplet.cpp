/**
 * @file sorted_triplet.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=SortedTriplet
 * @version 0.1
 * @date 2023-03-28
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */


#include "sorted_triplet.h"

namespace valhalla {
    namespace arrays {
        namespace sorted_triplet {
            /*

            Given an integer array `nums`, efficiently find a sorted triplet such that
            `nums[i] < nums[j] < nums[k]` where `i < j < k`.

            Input : [7, 3, 4, 2, 6]
            Output: (3, 4, 6)

            • If the input contains several sorted triplets, the solution can return any
              one of them.

            Input : [5, 4, 3, 7, 6, 1, 9]
            Output: (5, 7, 9) or (4, 7, 9) or (3, 7, 9) or (5, 6, 9) or (4, 6, 9) or (3, 6, 9)

            • If no triplet exists, return tuple (0, 0, 0).

            Input : [5, 4, 3]
            Output: (0, 0, 0)

            */

            std::tuple<int,int,int> Solution::findSortedTriplet(std::vector<int> const & nums) {
                std::tuple<int,int,int> triplet = std::make_tuple(0,0,0);
                const int size = nums.size();

                for (int idx_one = 0 ; idx_one < size ; idx_one++) {
                    for (int idx_two = idx_one + 1 ; idx_two < size ; idx_two++) {
                        if (nums[idx_one] >= nums[idx_two]) continue;
                        for (int idx_three = idx_two + 1 ; idx_three < size ; idx_three++) {
                            if (nums[idx_three] > nums[idx_two]) {
                                triplet = std::make_tuple(nums[idx_one], nums[idx_two], nums[idx_three]);
                                break;
                            } // if
                        } // for idx_one
                    } // for idx_two
                } // for idx_three

                return triplet;
            } // findSortedTriplet
        }
    }
}
