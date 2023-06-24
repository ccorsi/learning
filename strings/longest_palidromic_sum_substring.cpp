/**
 * @file longest_palidromic_sum_substring.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=LongestPalidromicSumSubstring
 * @version 0.1
 * @date 2023-06-23
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */


#include "longest_palidromic_sum_substring.h"

namespace valhalla {
    namespace strings {
        namespace longest_palidromic_sum_substring {
            /*

            Given a string, find the length of the longest contiguous substring, such that the length
            of the substring is `2×n` digits and the sum of the leftmost `n` digits is equal to the
            sum of the rightmost `n` digits. If there is no such substring, return 0.

            Input : 13267224
            Output: 6
            Explanation: 326722 = (3 + 2 + 6) = (7 + 2 + 2) = 11

            Input : 546374
            Output: 4
            Explanation: 4637 = (4 + 6) = (3 + 7) = 10

            */

            int Solution::findLongestPalindrome(std::string s) {
                int longest = -1;



                return longest;
            } // findLongestPalindrome
        }
    }
}
