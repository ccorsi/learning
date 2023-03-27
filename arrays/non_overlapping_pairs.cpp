/**
 * @file non_overlapping_pairs.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=NonOverlappingPairs
 * @version 0.1
 * @date 2023-03-27
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <map>

#include "non_overlapping_pairs.h"

namespace valhalla {
    namespace arrays {
        namespace non_overlapping_pairs {
            /*

            Given an unsorted integer array, find all non-overlapping pairs in it having
            the same sum.

            Input : [3, 7, 6, 2]
            Output: {{(7, 2), (3, 6)}}
            Explanation: The pairs (7, 2) and (3, 6) are non-overlapping (having different indices)
            and have the same sum.

            Input : [3, 4, 7, 4]
            Output: {}
            Explanation: No non-overlapping pairs are present in the array. The pairs (3, 4) and
            (3, 4) are overlapping as the index of 3 is the same in both pairs.

            • The input can contain multiple non-overlapping pairs with the same sum, the
              solution should return a set containing all the distinct pairs.

            Input : [3, 4, 7, 6, 1]
            Output: {{(6, 1), (3, 4)}, {(4, 6), (3, 7)}}

            Input : [3, 7, 6, 2, 4, 5]
            Output: {{(7, 2), (3, 6)}, {(6, 2), (3, 5)}, {(6, 4), (3, 7)}, {(6, 5), (7, 4)}, {(2, 5), (3, 4)}, {(4, 5), (3, 6)}, {(4, 5), (7, 2)}}

            Note: The solution should return all pairs in the same order as they appear in the array.

            */

            std::set<std::set<std::pair<int,int>>> Solution::findPairs(std::vector<int> const & nums) {
                std::set<std::set<std::pair<int,int>>> result;

                if ( nums.size() > 1 ) {
                    std::map<int,std::vector<std::pair<int,int>>> combos;
                    std::set<std::pair<int,int>> processed;

                    const int size = nums.size();

                    for (int outter = 0 ; outter < size ; outter++) {
                        for (int inner = 0 ; inner < size ; inner++) {
                            if (outter == inner) continue;

                            if (outter < inner) {
                                if ( ! processed.insert(std::pair(outter,inner)).second ) continue;
                            } else {
                                if ( ! processed.insert(std::pair(inner,outter)).second ) continue;
                            } // else

                            int key = nums[outter] + nums[inner];
                            combos[key].push_back(std::pair(outter, inner));
                        } // for inner
                    } // for outter

                    for (std::pair<const int, std::vector<std::pair<int,int>>> entry : combos) {
                        if (entry.second.size() < 2) continue;

                        for (std::pair<int,int> outter : entry.second) {
                            for (std::pair<int,int> inner : entry.second) {
                                if (outter == inner || outter.first == inner.first
                                    || outter.second == inner.second || outter.first == inner.second
                                    || outter.second == inner.first ) continue;

                                std::set<std::pair<int,int>> pairs = {
                                    std::pair(nums[outter.first],nums[outter.second]),
                                    std::pair(nums[inner.first], nums[inner.second]) };
                                result.insert(pairs);
                            } // for
                        } // for
                    } // for
                } // if

                return result;
            } // findPairs
        }
    }
}
