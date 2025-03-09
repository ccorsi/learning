/**
 * @file minimum_cut_palindromic_partition.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=MinimumCutPalindromicPartition
 * @version 0.1
 * @date 2025-02-23
 *
 * @copyright Copyright (c) 2025 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "minimum_cut_palindromic_partition.h"

#include <iostream>

namespace valhalla {

namespace dynamic_programming {

namespace minimum_cut_palindromic_partition {

/*

Given a string, find the minimum cuts needed to partition it such that each partition is a palindrome.

Input: s = "BABABCBADCD"
Output: 2
Explanation: The minimum cuts required are 2 as "BAB|ABCBA|DCD".

Input: s = "ABCBA"
Output: 0
Explanation: The minimum cuts required are 0 as "ABCBA" is already a palindrome.

Input: s = "ABCD"
Output: 3
Explanation: The minimum cuts required are 3 as "A|B|C|D".

*/

int attempt_one(std::string & s, std::string::size_type start, int cuts) {
    // std::cout << "s: " << s << ", start = " << start << ", cuts = " << cuts << '\n';
    /*
    We need to assume that we can separate the string into sections that we expect are palindrome
    */

    // Find the next character of type from start
    std::string::size_type next = s.size();

    int cur_cuts = -1;

    while (next > start) {
        next--;
        // Find the next position where this character is found
        while (start < next && s[start] != s[next]) next--;

        if (next > start) {
            // Determine if this range of characters is a palindrome
            std::string::size_type left = start + 1, right = next - 1;

            while (left < right && s[left] == s[right]) {
                left++; right--;
            } // while (left > right && s[left] == s[right])

            if (left >= right) {
                // we found a palindrome
                if (next + 1 == s.size()) {
                    // we are done thus return the current cuts
                    return cuts;
                } // if (next + 1 == s.size())

                // we need to cut the string into more palindromes
                int tmp_cuts = attempt_one(s, next + 1, cuts + 1);

                if (cur_cuts == -1 || tmp_cuts < cur_cuts) {
                    cur_cuts = tmp_cuts;
                } // if (cur_cuts == -1 || tmp_cuts < cur_cuts)
            }
        } // if (next > start)
    } // while (next > start)

    if (start + 1 == s.size()) {
        return cuts;
    } // (start + 1 == s.size())

    int tmp_cuts = attempt_one(s, start + 1, cuts + 1);

    if (cur_cuts == -1 || tmp_cuts < cur_cuts) {
        cur_cuts = tmp_cuts;
    } // if (cur_cuts == -1 || tmp_cuts < cur_cuts)

    return cur_cuts;
} // attempt_one

int Solution::findMinimumCuts(std::string s) {
    return s.empty() ? 0 : attempt_one(s, 0, 0);
} // findMinimumCuts

} // namespace minimum_cut_palindromic_partition

} // namespace dynamic_programming

} // namespace valhalla
