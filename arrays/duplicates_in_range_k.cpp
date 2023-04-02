/**
 * @file duplicates_in_range_k.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=DuplicatesInRangeK
 * @version 0.1
 * @date 2023-04-01
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <map>

#include "duplicates_in_range_k.h"

namespace valhalla {
    namespace arrays {
        namespace duplicates_in_range_k {
            /*

            Given an integer array and a positive number `k`, check whether the
            array contains any duplicate elements within the range `k`. If `k`
            is more than the array’s size, the solution should check for
            duplicates in the complete array.

            Input: nums[] = [5, 6, 8, 2, 4, 6, 9], k = 4
            Output: true
            Explanation: Element 6 repeats at distance 4 which is <= k

            Input: nums[] = [5, 6, 8, 2, 4, 6, 9], k = 2
            Output: false
            Explanation: Element 6 repeats at distance 4 which is > k

            Input: nums[] = [1, 2, 3, 2, 1], k = 7
            Output: true
            Explanation: Element 1 and 2 repeats at distance 4 and 2,
            respectively which are both <= k

            */

            bool Solution::hasDuplicate(std::vector<int> const & nums, int k) {
                const int size = nums.size();
                std::map<int,int> counts;

                int idx = 0;
                for ( ; idx  < k && idx < size ; idx++) {
                    int key = nums[idx];
                    counts[key]++;
                    if (counts[key] > 1) {
                        return true;
                    } // if
                } // for

                for ( ; idx < size ; idx++) {
                    int key = nums[idx];
                    counts[key]++;
                    if (counts[key] > 1) {
                        return true;
                    } // if
                    key = nums[idx - k];
                    counts[key]--;
                } // for

                return false;
            } // hasDuplicate
        }
    }
}
