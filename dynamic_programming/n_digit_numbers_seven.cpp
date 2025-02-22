/**
 * @file n_digit_numbers_seven.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=NDigitNumbersVII
 * @version 0.1
 * @date 2025-02-22
 *
 * @copyright Copyright (c) 2025 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "n_digit_numbers_seven.h"
#include <list>

namespace valhalla {

namespace dynamic_programming {

namespace n_digit_numbers_seven {

/*

Given a positive integer n, return all n–digit binary numbers without any consecutive 1's.

Input: n = 5
Output: {
    "00000", "00001", "00010", "00100", "00101", "01000", "01001", "01010", "10000",
    "10001", "10010", "10100", "10101"
}

*/

std::unordered_set<std::string> solution_two(int n) {
    std::unordered_set<std::string> results;

    if (n > 0) {
        std::list<std::string> queue = { "0", "1" };

        while ( ! queue.empty() ) {
            std::string & str = queue.front();

            if (str.length() == n) {
                results.insert(str);
                queue.pop_front();
                continue;
            } else {
                if ( *(str.rbegin()) == '0' ) {
                    queue.push_back(str + '1');
                } // if ( *(str.rbegin()) == '0' )
                str += '0';
            } // if (str.length() == n)
        } // while ( ! queue.empty() )
    } // if (n > 0)

    return results;
} // solution_two

std::unordered_set<std::string> solution_one(int n) {
    std::unordered_set<std::string> results;

    if (n > 0) {
        std::list<std::string> queue = { "0", "1" };

        while ( ! queue.empty() ) {
            std::string str = queue.front(); queue.pop_front();

            if (str.length() == n) {
                results.insert(str);
                continue;
            }

            queue.push_back(str + '0');

            if (*(str.rbegin()) == '0') {
                queue.push_back(str + '1');
            } // if (*(str.rbegin()) == '0')
        } // while ( ! queue.empty() )

    } // if (n > 0)

    return results;
} // solution_one

std::unordered_set<std::string> Solution::findNDigitNumbers(int n) {
    return solution_one(n);
} // findNDigitNumbers

} // namespace n_digit_numbers_seven

} // namespace dynamic_programming

} // namespace valhalla
