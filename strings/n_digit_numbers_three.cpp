/**
 * @file n_digit_numbers_three.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=NDigitNumbersIII
 * @version 0.1
 * @date 2025-02-19
 *
 * @copyright Copyright (c) 2025 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */


#include "n_digit_numbers_three.h"

#include <list>

namespace valhalla {

namespace strings {

namespace n_digit_numbers_three {
/*

Given a positive number n between 1 and 9, find all n–digit numbers with a given sum where
sum <= 81 (Maximum possible sum in a 9–digit number).

Input: n = 3, target = 6

Output: {105, 114, 123, 132, 141, 150, 204, 213, 222, 231, 240, 303, 312, 321, 330, 402, 411, 420,
501, 510, 600}


Input: n = 5, target = 42

Output: {69999, 78999, 79899, 79989, 79998, 87999, 88899, 88989, 88998, 89799, 89889, 89898, 89979,
    89988, 89997, 96999, 97899, 97989, 97998, 98799, 98889, 98898, 98979, 98988, 98997, 99699, 99789,
    99798, 99879, 99888, 99897, 99969, 99978, 99987, 99996}

*/

std::unordered_set<int> solution_one(int n, int target) {
    std::unordered_set<int> results;

    struct state {
        // current target
        int m_current_target;
        // current value
        int m_value;
        // current length of the value
        int m_len;

        state(int value, int len, int current_target) : m_value(value),
            m_len(len), m_current_target(current_target) {
            }
    };

    std::list<state> queue;

    for (int value = 0 ; value++ < 9 ; ) {
        queue.push_back(state(value, 1, value));
    } // for (int value = 0 ; value++ < 9 ; )

    while ( ! queue.empty() ) {
        state current = queue.front(); queue.pop_front();
        if (current.m_len == n) {
            if (current.m_current_target == target) {
                results.insert(current.m_value);
            }
            // we are done then move on to the next one.
            continue;
        } // if (current.m_len == n)

        current.m_len++;
        if (current.m_len > n) {
            // we are done then move on to the next one.
            continue;
        } // if (current.m_len > n)

        current.m_value *= 10;
        for (int value = 0 ; value < 10 ; value++) {
            if (current.m_current_target + value <= target) {
                queue.push_back(state(current.m_value + value, current.m_len, current.m_current_target + value));
            } // if (current.m_current_target + value <= target)
        } // for (int value = 0 ; value < 10 ; value++)

    } // while ( ! queue.empty() )
    return results;
} // solution_one

std::unordered_set<int> Solution::findNDigitNumbers(int n, int target) {
    return solution_one(n, target);
} // findNDigitNumbers

} // namespace n_digit_numbers_three

} // namespace strings

} // namespace valhalla
