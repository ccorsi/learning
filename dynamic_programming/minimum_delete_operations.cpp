/**
 * @file minimum_delete_operations.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=MinimumDeleteOperations
 * @version 0.1
 * @date 2025-02-22
 *
 * @copyright Copyright (c) 2025 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "minimum_delete_operations.h"

#include <iostream>

namespace valhalla {

namespace dynamic_programming {

namespace minimum_delete_operations {

/*

Given a string, find the minimum number of deletions required to convert it into a palindrome.

Input: s = "ACBCDBAA"
Output: 3
Explanation: The minimum number of deletions required to convert "ACBCDBAA" into a palindrome string "ABCBA" is 3.

*/

int attempt_one(std::string & s, std::string::size_type start, std::string::size_type end, int count) {
    // std::cout << "s = " << s << ", start = " << start << ", end = " << end << ", substr = " << s.substr(start, end - start + 1) << ", count = " << count;
    // determine if the current range is a palindrome
    while (start < end && s[start] == s[end]) {
        start++; end--;
    } // while (start < end && s[start] == s[end])

    // std::cout << ", updated start = " << start << ", updated end = " << end << ", count = " << count << '\n';
    if (start >= end) {
        return count;
    } // if (start >= end)

    int left_count = attempt_one(s, start + 1, end, count + 1);

    int right_count = attempt_one(s, start, end - 1, count + 1);

    int both_count = attempt_one(s, start + 1, end - 1, count + 2);

    // std::cout << "left_count = " << left_count << ", right_count = " << right_count << ", both_count = " << both_count << '\n';

    if (left_count != -1) {
        if (right_count != -1) {
            int combined_count = std::min(left_count, right_count);
            if (both_count != -1) {
                return (combined_count < both_count) ? combined_count : both_count;
            } // if (both_count != -1)
            return combined_count;
        } // if (right_count != -1)
        return both_count == -1 ? left_count : std::min(left_count, both_count);
    } // if (left_count != -1)

    if (right_count != -1) {
        return both_count == -1 ? right_count : std::min(right_count, both_count);
    } // if (right_count != -1)

    return both_count != -1 ? both_count : -1;
} // attempt_one

int Solution::findMinimumDeletions(std::string s) {
    // std::cout << "Processing string: " << s << '\n';
    int count = s.empty() ? 0 : attempt_one(s, 0, s.size() - 1, 0);
    // std::cout << "count: " << count << '\n';
    return count;
} // findMinimumDeletions

} // namespace minimum_delete_operations

} // namespace dynamic_programming

} // namespace valhalla
