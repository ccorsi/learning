/**
 * @file k_palindrome_string.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is solution to the problem https://www.techiedelight.com/?problem=KPalindromeString
 * @version 0.1
 * @date 2025-02-22
 *
 * @copyright Copyright (c) 2025 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "k_palindrome_string.h"
#include <stdexcept>
#include <iostream>

namespace valhalla {

namespace dynamic_programming {

namespace k_palindrome_string {

/*

Given a string, check if it is k–palindrome or not. A string is k–palindrome if it becomes
a palindrome on removing at-most k characters from it.

Input: s = "ABCDBA", k = 1
Output: true
Explanation: The string becomes a palindrome by removing either C or D from it.

Input: s = "ABCDECA", k = 1
Output: false
Explanation: The string needs at least 2–removals from it to become a palindrome.

*/

bool validate(std::string s, int k, std::string::size_type start, std::string::size_type end) {
    // std::cout << "k = " << k << ", start = " << start << ", end = " << end << ", checking = " << s.substr(start, end - start + 1) << '\n';
    if (s.empty() || start == end) {
        // this is a palindrome
        return true;
    } // if (start == end)

    // Determine how many of the characters are part of the palindrome
    while (start < end && s[start] == s[end]) {
        // the characters are the same thus move to the next character from the beginning and end
        start++; end--;
    } // while (start < end && s[start] == s[end])

    if (start >= end) {
        // This is a palindrome already thus return true;
        return true;
    } // if (start == end)

    // Determine if we have any characters we can delete
    if (k == 0) {
        // This can not be made into a palindrome
        return false;
    } // if (k == 0)

    k--; // decrement a character that was removed
    // remove a single character from the begining
    if (validate(s, k, start + 1, end)) {
        // This is a palindrome
        return true;
    } // if (validate(s, k, start + 1, end))

    // remove a single character from the end
    if (validate(s, k, start, end - 1)) {
        // This is a palindrome
        return true;
    } // if (validate(s, k, start, end - 1))

    if (k > 0) {
        k--; // decrement a second character that was removed
        return validate(s, k, start + 1, end - 1);
    } // if (k > 0)

    // this is not a palindrome
    return false;
} // validate

bool attempt_one(std::string s, int k) {
    /*
     * This implementation assumes that the passed string contains a palindrome that
     * can be generared purging a total of k characters.  We then determine if the
     * string is odd or even and proceed from their.
     */
    if (s.empty()) {
        return true;
    } // if (s.empty()

    // std::cout << "s = " << s << ", k = " << k << '\n';
    return validate(s, k, 0, s.size() - 1);
} // attempt_one

bool Solution::isKPalindromeString(std::string s, int k) {
    return attempt_one(s,k);
} // isKPalindromeString

} // namespace k_palindrome_string

} // namespace dynamic_programming

} // namespace valhalla
