/**
 * @file longest_increasing_subsequence_two.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=LongestIncreasingSubsequenceII
 * @version 0.1
 * @date 2023-05-15
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */


#include "longest_increasing_subsequence_two.h"

namespace valhalla {
    namespace arrays {
        namespace longest_increasing_subsequence_two {
            /*

            Given a given sequence, find the longest increasing subsequence (LIS) in it.

            The longest increasing subsequence is a subsequence of a given sequence in which the
            subsequence's elements are in sorted order, lowest to highest, and in which the
            subsequence is as long as possible.

            The longest increasing subsequence is not necessarily unique, the solution can
            return any valid subsequence.

            Input : [0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15]
            Output: [0, 2, 6, 9, 11, 15] or [0, 4, 6, 9, 11, 15] or [0, 4, 6, 9, 13, 15]

            */

            std::vector<int> Solution::findLIS(std::vector<int> const & nums) {
                std::vector<int> longest;
                int idx = nums.size(), longest_length = 0;

                while (idx-- > 0) {
                    findNextValue(nums, idx, 1, idx - 1, longest, longest_length);
                } // while

                return longest;
            } // findLIS

            bool Solution::findNextValue(std::vector<int> const & nums, int value_idx, int currentLength, int idx,
                                         std::vector<int> & longest, int & longest_length) {
                bool is_longest = false;
                const int value = nums[value_idx];

                // Compare the current length with the current longest length
                if (currentLength > longest_length) {
                    longest.clear();
                    longest_length = currentLength;
                    is_longest = true;
                } // if

                while (idx > -1) {
                    if (value > nums[idx]) {
                        is_longest |= findNextValue(nums, idx, currentLength + 1, idx - 1, longest, longest_length);
                    }
                    idx--;
                } // while

                if (is_longest) longest.push_back(value);

                return is_longest;
            }
        }
    }
}
