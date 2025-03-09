/**
 * @file n_digit_numbers_six.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains the solution to the problem https://www.techiedelight.com/?problem=NDigitNumbersVI
 * @version 0.1
 * @date 2025-02-20
 *
 * @copyright Copyright (c) 2025 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "n_digit_numbers_six.h"

#include <list>
#include <cassert>
#include <cstdlib>

namespace valhalla {

namespace backtracking {

namespace n_digit_numbers_six {

/*

Given a positive number n between 2 and 9, find all n–digit numbers with an equal sum of digits at even and odd indices.

Input: n = 3
Output: {110, 121, 132, 143, 154, 165, 176, 187, 198, 220, 231, 242, 253, 264, 275, 286, 297, 330, 341, 352, 363, 374,
         385, 396, 440, 451, 462, 473, 484, 495, 550, 561, 572, 583, 594, 660, 671, 682, 693, 770, 781, 792, 880, 891,
         990}

Input: n = 5
Output: {10010, 10021, 10032, 10043, 10054, 10065, 10076, 10087, 10098, 10120, 10131, 10142, 10153, 10164, 10175, 10186,
         10197, 10230, 10241, 10252, 10263, 10274, 10285, 10296, 10340, 10351, 10362, 10373, 10384, 10395, 10450, 10461,
         10472, 10483, 10494, 10560, 10571, 10582, 10593, 10670, 10681, 10692, 10780, 10791, 10890, 11000, 11011, 11022,
         11033, 11044, 11055, 11066, 11077, 11088, 11099, 11110, 11121, 11132, 11143, 11154, 11165, 11176, 11187, 11198,
         11220}

*/

std::unordered_set<int> attempt_one(int n) {
    std::unordered_set<int> results;

    struct state {
        int m_odds, m_evens;
        int m_value, m_len;
        state(int value, int len, int odds, int evens = 0) : m_value(value), m_len(len), m_odds(odds), m_evens(evens) {}
    };

    std::list<state> queue;

    for (int value = 1 ; value < 10 ; value++) {
        queue.push_back(state(value,1,value));
    } // for (int value = 1 ; value < 10 ; value++)

    while ( ! queue.empty() ) {
        auto current = queue.front(); queue.pop_front();
        bool is_odd = ++current.m_len % 2;
        current.m_value *= 10;
        if (current.m_len == n) {
            int diff = std::abs(current.m_evens - current.m_odds);
            if (diff > 9) {
                // we can't create a valid number
                continue;
            } // if (diff > 9)
            if (is_odd) {
                if (current.m_evens == current.m_odds + diff)
                    results.insert(current.m_value + diff);
            } else {
                if (current.m_evens + diff == current.m_odds)
                    results.insert(current.m_value + diff);
            }
        } else {
            for (int value = 0 ; value < 10 ; value++) {
                if (is_odd) {
                    queue.push_back(state(current.m_value + value, current.m_len, current.m_odds + value, current.m_evens));
                } else {
                    queue.push_back(state(current.m_value + value, current.m_len, current.m_odds, current.m_evens + value));
                } // else of if (is_odd)
            } // for (int value = 0 ; value < 10 ; value++)
        } // else of if (current.m_len == n)
    } // while ( ! queue.empty() )

    return results;
} // attempt_one

std::unordered_set<int> Solution::findNDigitNumbers(int n) {
    return attempt_one(n);
} // findNDigitNumbers

} // namespace n_digit_numbers_six

} // namespace backtracking

} // namespace valhalla
