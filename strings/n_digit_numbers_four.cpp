/**
 * @file n_digit_numbers_four.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=NDigitNumbersIV
 * @version 0.1
 * @date 2025-02-20
 *
 * @copyright Copyright (c) 2025 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "n_digit_numbers_four.h"
#include <list>

namespace valhalla {

namespace strings {

namespace n_digit_numbers_four {

/*

Given a positive number n between 1 and 9, find all n–digit binary numbers with k–bits set where k ranges from 1 to n.

Input: n = 4

Output: {"0001", "0010", "0100", "1000", "0011", "0101", "0110", "1001", "1010", "1100", "0111", "1011", "1101", "1110", "1111"}

Explanation: 4–digit binary numbers are:

(k = 1) 0001 0010 0100 1000
(k = 2) 0011 0101 0110 1001 1010 1100
(k = 3) 0111 1011 1101 1110
(k = 4) 1111


Input: n = 5

Output: {"00001", "00010", "00100", "01000", "10000", "00011", "00101", "00110", "01001", "01010", "01100", "10001", "10010", "10100", "11000", "00111", "01011", "01101", "01110", "10011", "10101", "10110", "11001", "11010", "11100", "01111", "10111", "11011", "11101", "11110", "11111"}

Explanation: 5–digit binary numbers are:

(k = 1) 00001 00010 00100 01000 10000
(k = 2) 00011 00101 00110 01001 01010 01100 10001 10010 10100 11000
(k = 3) 00111 01011 01101 01110 10011 10101 10110 11001 11010 11100
(k = 4) 01111 10111 11011 11101 11110
(k = 5) 11111

*/

std::unordered_set<std::string> solution_one(int n) {
    std::unordered_set<std::string> results;
    std::list<std::string> queue = { "" };

    while ( ! queue.empty() ) {
        std::string str = queue.front(); queue.pop_front();

        if (str.length() == n) {
            // we are done then move to the next string
            results.insert(str);
            continue;
        }

        if (str.length() < n) {
            queue.push_back(str + '0');
            queue.push_back(str + '1');
        } // if (str.length() < n)
    } // while ( ! queue.empty() )

    // remove the all '0' added string
    results.erase(std::string(n, '0'));

    return results;
} // solution_one

std::unordered_set<std::string> Solution::findNDigitNumbers(int n) {
    return solution_one(n);
} // findNDigitNumbers

} // namespace n_digit_numbers_four

} // namespace strings

} // namespace valhalla
