/**
 * @file n_digit_numbers_five.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=NDigitNumbersV
 * @version 0.1
 * @date 2025-02-20
 *
 * @copyright Copyright (c) 2025 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "n_digit_numbers_five.h"
#include <list>
#include <unordered_map>

namespace valhalla {

namespace strings {

namespace n_digit_numbers_five {

/*

Given a positive number n between 1 and 9, find all n–digit binary numbers with an equal sum of left and right half.
The binary number should not start with 0 and for odd numbers, the middle element can be 0 or 1.

Input: n = 6
Output: {"100001", "100010", "101011", "110011", "100100", "101101", "101110", "110101", "110110", "111111"}

Input: n = 7
Output: {"1000001", "1001001", "1000010", "1001010", "1010011", "1011011", "1100011", "1101011", "1000100",
         "1001100", "1010101", "1011101", "1010110", "1011110", "1100101", "1101101", "1100110", "1101110",
         "1110111", "1111111"}

*/

std::unordered_set<std::string> solution_one(int n) {
    std::unordered_set<std::string> results;

    // This is not necessary since n is between 1 and 9 but it is a good habit to have
    if (n > 0) {
        if (n == 1) {
            // we are done
            results = { "0", "1" };
        } else {
            const int len = n / 2;

            struct state {
                std::string m_value;
                int m_ones;
                state(std::string value, int ones) : m_value(value), m_ones(ones) {}
            };

            std::list<state> queue = { state("1", 1) };

            // Populate all combinations of n prefixes or length len
            for(int count = 1 ; count < len ; count++) {
                for (state current = queue.front() ; current.m_value.size() == count ; current = queue.front()) {
                    queue.pop_front();
                    queue.push_back(state(current.m_value + '0', current.m_ones));
                    current.m_value += '1';
                    current.m_ones++;
                    queue.push_back(current);
                } // for (state current = queue.front() ; current.m_value.size() == count ; current = queue.front())
            } // for(int count = 1 ; count < len ; count++)

            // Cache the combinations for performance
            std::unordered_map<int,std::list<std::string>> cached;

            for (auto & current : queue) {
                cached[current.m_ones].push_back(current.m_value);
            } // for (auto & current : queue)

            std::list<state> ones = { state("0", 0) };
            // Populate all combinations of n prefixes or length len
            for(int count = 1 ; count < len ; count++) {
                for (state next = ones.front() ; next.m_value.size() == count ; next = ones.front()) {
                    ones.pop_front();
                    ones.push_back(state(next.m_value + '0', next.m_ones));
                    next.m_value += '1';
                    next.m_ones++;
                    ones.push_back(next);
                } // for (state next = ones.front() ; next.m_value.size() == count ; next = ones.front())
            } // for(int count = 1 ; count < len ; count++)

            for (auto & current : ones) {
                cached[current.m_ones].push_back(current.m_value);
            } // for (auto & current : ones)

            // is n odd?
            const bool is_odd = n % 2 == 1;

            for (auto & current : queue) {
                for (auto & suffix : cached[current.m_ones]) {
                    if (is_odd) {
                        results.insert(current.m_value + '0' + suffix);
                        results.insert(current.m_value + '1' + suffix);
                    } else {
                        results.insert(current.m_value + suffix);
                    }
                } // for (auto & suffix : cached[current.m_ones])
            } // for (auto & current : queue)
        } // else of if (n == 1)
    } // if (n > 0)

    return results;
} // solution_one

std::unordered_set<std::string> Solution::findNDigitNumbers(int n) {
    return solution_one(n);
} // findNDigitNumbers

} // namespace n_digit_numbers_five

} // namespace strings

} // namespace valhalla
