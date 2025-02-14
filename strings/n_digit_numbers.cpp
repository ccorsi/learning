/**
 * @file n_digit_numbers.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=NDigitNumbers
 * @version 0.1
 * @date 2025-02-07
 *
 * @copyright Copyright (c) 2025 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */


#include "n_digit_numbers.h"

#include <list>
#include <memory>
#include <iostream>

namespace valhalla {

namespace strings {

namespace n_digit_numbers {

/*

Given a positive number n between 1 and 9, find all n–digit strictly increasing numbers.
A number is strictly increasing if every digit is greater than its preceding digit.

Input: n = 8
Output: {12345678, 12345679, 12345689, 12345789, 12346789, 12356789, 12456789, 13456789, 23456789}

Input: n = 7
Output: {1234567, 1234568, 1234569, 1234578, 1234579, 1234589, 1234678, 1234679, 1234689, 1234789,
        1235678, 1235679, 1235689, 1235789, 1236789, 1245678, 1245679, 1245689, 1245789, 1246789,
        1256789, 1345678, 1345679, 1345689, 1345789, 1346789, 1356789, 1456789, 2345678, 2345679,
        2345689, 2345789, 2346789, 2356789, 2456789, 3456789}

*/

struct status
{
    int m_value, m_next, m_idx;
    status() = default;
    status(int value, int next, int idx) : m_value(value), m_next(next), m_idx(idx) {}

    friend std::ostream& operator<<(std::ostream&, const status&);
};

std::ostream& operator<<(std::ostream& out, const status & current) {
    return out << "status[ value=" << current.m_value << ", next=" << current.m_next << ", idx=" << current.m_idx << " ]";
}

/**
 * @brief This recursive method will be used to determine all of the value sums that satisfy the condition n.
 *
 * @param results this contains a set of valid results of size n
 * @param sum this contains the current sum of the current step
 * @param value this contains the value that was last added to sum
 * @param step this speficies which step we are current in
 * @param n this specifies the total steps
 */
void recurse(std::unordered_set<int> & results, const int sum, const int value, const int step, const int n) {
    if (step == n) {
        results.insert(sum);
        return;
    }

    int base = sum * 10;
    for (int next = value + 1 ; next < 10 ; next++) {
        if (next + n - step < 10) {
            recurse(results, base + next, next + 1, step + 1, n);
        }
    }
}

std::unordered_set<int> attempt_three(int n) {
    std::unordered_set<int> results;

    if (n < 1) {
        return results;
    }

    for (int value = 1 ; value < 10 ; value++) {
        if (value + n - 1 < 10) {
            // recurse using value
            recurse(results, value, value + 1, 1, n);
        }
    }

    return results;
}

std::unordered_set<int> solution_two(int n) {
    std::unordered_set<int> results;

    if (n < 1) {
        return results;
    } // if (n < 1)

    struct status {
        int m_sum, m_last, m_step;
        status() = default;
        status(int sum, int last, int step) : m_sum(sum), m_last(last), m_step(step) {}
    };

    std::list<status> queue;

    queue.push_back(status(0, 0, 0));

    while ( ! queue.empty() ) {
        // get the next entry
        status current = queue.front(); queue.pop_front();
        // increment the step
        current.m_step++;
        // update the sum
        current.m_sum *= 10;

        if (current.m_step == n) {
            for (int value = current.m_last ; value++ < 9 ; ) {
                results.insert(current.m_sum + value);
            }
            continue;
        }

        for (int value = current.m_last ; value++ < 9 ; ) {
            queue.push_back(status(current.m_sum + value, value, current.m_step));
        }
    }

    return results;
}

std::unordered_set<int> attempt_one(int n) {
    std::unordered_set<int> results;

    if (n < 1) {
        return results;
    } // if (n < 1)

    std::list<status> queue;

    for (int value = 0 ; value++ < 9 ; ) {
        queue.push_back(status(value, value + 1, 1));
    } // for (int value = 0 ; value++ < 9 ; )

    while ( ! queue.empty() ) {
        status & current = queue.front();
        // std::cout << current << '\n';

        if (current.m_idx == n) {
            if (current.m_next < 11) {
                // we are done
                results.insert(current.m_value * 10 + current.m_next);
            }
            // pop the front since we are done....
            queue.pop_front();
            continue;
        } // if (current.m_idx == n)

        current.m_value *= 10;
        current.m_value += current.m_next;
        current.m_idx++; current.m_next++;

        for (int next = current.m_next ; next++ < 9 ; ) {
            status next_status(current.m_value, next, current.m_idx);
            queue.push_back(next_status);
        } // for (int next = current.m_next ; next++ < 9 ; )
    } // while ( ! queue.empty() )

    return results;
}

std::unordered_set<int> Solution::findStrictlyIncreasingNumbers(int n) {
    return solution_two(n);
} // findStrictlyIncreasingNumbers

} // namespace n_digit_numbers

} // namespace strings

} // namespace valhalla
