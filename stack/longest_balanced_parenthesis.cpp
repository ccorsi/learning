/**
 * @file longest_balanced_parenthesis.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This file contains the solution to the problem https://www.techiedelight.com/?problem=LongestBalancedParenthesis
 * @version 0.1
 * @date 2025-02-07
 *
 * @copyright Copyright (c) 2025 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */


#include "longest_balanced_parenthesis.h"

#include <list>

namespace valhalla {

namespace stack {

namespace longest_balanced_parenthesis {

/*

Given a string consisting of opening and closing parenthesis,
find the length of the longest balanced parenthesis in it.

Input: "((()()"
Output: 4
Explanation: The longest balanced parenthesis is "()()"

Input: "(()())(()"
Output: 6
Explanation: The longest balanced parenthesis is "(()())"

Input: "(((()"
Output: 2
Explanation: The longest balanced parenthesis is "()"

Input: "(((("
Output: 0
Explanation: The longest balanced parenthesis is ""

Input: "()()"
Output: 4
Explanation: The longest balanced parenthesis is "()()"

*/

int attempt_two(std::string s) {
    int max = 0;

    std::list<std::size_t> starts;

    std::size_t start = 0;
    const std::size_t end = s.size();

    while (start < end) {
        if (s[start] == '(') {
            starts.push_back(start);
        } // if (s[start] == '(')
        start++;
    } // while (pos < end)

    while ( ! starts.empty() ) {
        // get the next starting position
        start = starts.front() + 1;
        // remove the next starting position from the starts
        starts.pop_front();

        int length = 1, current = -1;
        while (start < end && current < 1) {
            length++;
            if (s[start] == '(') {
                current--;
            } else if (++current == 0 && length > max) {
                max = length;
            } // if (s[start] == '(')
            start++;
        }
    } // while ( ! starts.empty() )

    return max;
}

int attempt_one(std::string s) {
    int max = 0;

    std::list<std::size_t> starts;

    std::size_t start = 0;
    const std::size_t end = s.size();

    while (start < end && s[start] == ')') {
        start++;
    } // while (pos < end && s[pos] == ')')

    if (start < end) {
        starts.push_back(start);
    } // if (pos < end)

    while ( ! starts.empty() ) {
        // get the next starting position
        start = starts.front() + 1;
        // remove the next starting position from the starts
        starts.pop_front();

        int length = 1, current = -1;
        while (start < end && current < 1) {
            length++;
            if (s[start] == '(') {
                current--;
                starts.push_back(start);
            } else if (++current == 0 && length > max) {
                max = length;
            } // if (s[start] == '(')
            start++;
        }
    } // while ( ! starts.empty() )

    return max;
}

int Solution::findLength(std::string s) {
    return attempt_two(s);
} // findLength

} // namespace longest_balanced_parenthesis

} // namespace stack

} // namespace valhalla
