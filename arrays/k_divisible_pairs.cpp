/**
 * @file k_divisible_pairs.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=KDivisiblePairs
 * @version 0.1
 * @date 2023-04-04
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <set>

#include "k_divisible_pairs.h"

namespace valhalla {
    namespace arrays {
        namespace k_divisible_pairs {
            /*

            Given an integer array, determine whether it can be divided into pairs
            such that the sum of elements in each pair is divisible by a given
            positive integer `k`.

            Input: nums[] = [3, 1, 2, 6, 9, 4], k = 5
            Output: true
            Explanation: Array can be divided into pairs {(3, 2), (1, 9), (4, 6)},
            where the sum of elements in each pair is divisible by 5.

            Input: nums[] = [2, 9, 4, 1, 3, 5], k = 6
            Output: true
            Explanation: Array can be divided into pairs {(2, 4), (9, 3), (1, 5)},
            where the sum of elements in each pair is divisible by 6.

            Input: nums[] = [3, 1, 2, 6, 9, 4], k = 6
            Output: false
            Explanation: Array cannot be divided into pairs where the sum of elements
            in each pair is divisible by 6.

            */

            bool Solution::hasPairs(std::vector<int> const & nums, int k) {
                if (nums.size() % 2 == 1) return false;

                if (nums.empty()) return true;

                const int size = nums.size();
                std::set<int> processed;

                while (processed.size() != nums.size()) {
                    int idx = 0;

                    while (idx < size && processed.find(idx) != processed.end()) {
                        idx++;
                    }

                    if (idx == size) {
                        break;
                    }

                    processed.insert(idx);

                    int value = nums[idx];

                    idx = 0;

                    while (idx < size && (processed.find(idx) != processed.end() || (value + nums[idx]) % k != 0)) {
                        idx++;
                    } // while

                    if (idx == size) {
                        break;
                    }

                    processed.insert(idx);
                } // while

                return processed.size() == nums.size();

                /*
                    Version 1
                    The was not a correct solution since it doesn't consider pairs of values.
                    It only assumes the sum is divisible by k which is not correct.

                if (nums.size() % 2 == 1) return false;

                int sum = 0;

                for (int value : nums) {
                    sum += value;
                } // for

                return (sum % k) == 0;
                */
            } // hasPairs
        }
    }
}
