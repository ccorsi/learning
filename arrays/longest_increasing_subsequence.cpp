/**
 * @file longest_increasing_subsequence.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=LongestIncreasingSubsequence
 * @version 0.1
 * @date 2023-05-15
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */


#include "longest_increasing_subsequence.h"

namespace valhalla {
    namespace arrays {
        namespace longest_increasing_subsequence {
            /*

            Given a given sequence, find the length of the longest increasing subsequence (LIS) in it.

            The longest increasing subsequence is a subsequence of a given sequence in which the
            subsequence's elements are in sorted order, lowest to highest, and in which the subsequence
            is as long as possible.

            Input : [0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15]
            Output: 6
            Explanation: The longest increasing subsequence is [0, 2, 6, 9, 11, 15] having length 6;
            the input sequence has no 7–member increasing subsequences.

            The longest increasing subsequence is not necessarily unique. For instance,
            [0, 4, 6, 9, 11, 15] and [0, 4, 6, 9, 13, 15] are other increasing subsequences of equal
            length in the same input sequence.

            */

            int Solution::findLISLength(std::vector<int> const & nums) {
                int longest = 0;
                const int size = nums.size();

                for(int idx = 0 ; idx + longest < size ; idx++) {
                    findNextIncreasingValue(nums, nums[idx], 1, idx + 1, size, longest);
                }

                return longest;
            } // findLISLength

            void Solution::findNextIncreasingValue(std::vector<int> const & nums, int value, int currentLength, int idx, const int size, int & longest) {
                if (currentLength > longest) {
                    longest = currentLength;
                } // if

                while (idx < size) {
                    if (nums[idx] > value) {
                        findNextIncreasingValue(nums, nums[idx], currentLength + 1, idx + 1, size, longest);
                    } // if
                    idx++;
                } // while
            }
        }
    }
}
