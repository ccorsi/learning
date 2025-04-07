/**
 * @file power_set.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=PowerSet
 * @version 0.1
 * @date 2025-03-22
 *
 * @copyright Copyright (c) 2025 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "power_set.h"
#include <algorithm>
#include <queue>

namespace valhalla {

namespace backtracking {

namespace power_set {

/*

Given a set S, return all subsets of it, i.e., find the power set of S.
A power set of a set S is the set of all subsets of S, including the empty set and S itself.

Input : S[] = [1, 2, 3]
Output: [[3, 2, 1], [3, 2], [3, 1], [3], [2, 1], [2], [1], []]

Input : S[] = [1, 2, 1]
Output: [[1, 2, 1], [1, 2], [1, 1], [1], [2, 1], [2], [1], []]

Input : S[] = [1, 1]
Output: [[1, 1], [1], [1], []]

Input : S[] = []
Output: [[]]

Note: The solution can return elements of a subsets in any order.

*/
std::vector<std::vector<int>> nonrecursive_attempt_one(std::vector<int> const & S) {
    std::vector<std::vector<int>> power_set = {{}};

    class state {
        std::vector<int> m_vec;
        int m_current, m_len;

    public:
        state(int value, int current, int len) : m_current(current), m_len(len) {
            m_vec.push_back(value);
        }

        state(std::vector<int> & vec, int current, int len) : m_vec(vec),
            m_current(current), m_len(len) {}

        void update(int value) {
            m_vec.push_back(value);
            m_current++;
            m_len--;
        }

        void pop() {
            m_vec.pop_back();
            m_current--;
            m_len++;
        }

        int pos() { return m_current; }

        bool is_done() { return m_len == 0; }

        std::vector<int> const & operator()() const { return m_vec; }
    };

    std::queue<state> states;

    for (int len = static_cast<int>(S.size()) ; len-- > 0 ; ) {
        const int end = static_cast<int>(S.size()) - len;
        for (int start = 0 ; start < end ; ) {
            states.push(state(S[start++], start, len ));
        } // for (int start = 0 ; start < end ; )
    } // for (int len = static_cast<int>(S.size()) ; len-- > 0 ; )

    while ( ! states.empty() ) {
        state current = states.front();
        if (current.is_done()) {
            power_set.push_back(current());
            states.pop();
            continue;
        } // if (current.m_len == 0)

        std::vector<int> vec = current();
        current.update(S[current.pos()]);
        states.pop();
    } // while ( ! states.empty() )

    return power_set;
} // nonrecursive_attempt_one

/**
 * @brief This recursive attempt to generate the power set for a given set doesn't
 *      correctly produce the expected power set.  It successfully generates the
 *      power set for a small set but fails for a large set with 4 elements or more.
 *
 * @param power_set Pointer to the populating power set
 * @param S Pointer to the set used to generate the power set
 * @param vec Pointer to the currently generating set to populate the power set
 * @param start The start of the next element to be added to the vec instance
 * @param count The current number of entries that still need to be added to the vec
 */
void process(std::vector<std::vector<int>> & power_set, std::vector<int> const & S,
             std::vector<int> & vec, int start, int count) {
    if (count == 0) {
        std::sort(vec.begin(), vec.end());
        power_set.push_back(vec);
        return;
    } // if (count == 0)

    while (start < S.size()) {
        vec.push_back(S[start++]);
        process(power_set, S, vec, start, count - 1);
        vec.pop_back();
    } // while (start < S.size())
} // process

std::vector<std::vector<int>> recursive_attempt_one(std::vector<int> const & S) {
    std::vector<std::vector<int>> power_set = {{}};

    for (int count = static_cast<int>(S.size()) ; count-- > 0 ; ) {
        for (int start = 0 ; start < S.size() ; ) {
            std::vector<int> vec = { S[start++] };
            process(power_set, S, vec, start, count);
        } // for (int start = 0 ; start < S.size() ; )
    } // for (int count = static_cast<int>(S.size()) ; count-- > 0 ; )

    return power_set;
} // recursive_attempt_one

/**
 * @brief The recursive attempt to solve the generation of a power set given a set works
 *      as expected.  The generated power set is successfully generated using the passed
 *      set.
 *
 * @param power_set Pointer to the power set that is populated
 * @param vec Pointer to the vector that contains the current set of values
 * @param S Pointer to the vector that is used to generated the power set
 * @param start The start of the next entry in the vector S to be added to the vec
 * @param count Remaining number of entries that still need to be added to vec
 */
void process_next_entry(std::vector<std::vector<int>> & power_set, std::vector<int> & vec,
                        std::vector<int> const & S, int start, int count) {
    if (count == 0) {
        power_set.push_back(vec);
        return;
    } // if (count < 1)

    // Insure that we still have entries that need to be added to the passed vec
    if (count-- > 0) {
        const int last = static_cast<int>(S.size()) - count;
        // Make sure that we frivolously add entries to the vec when we don't have enough entries
        while (start < last) {
            vec.push_back(S[start]);
            process_next_entry(power_set, vec, S, ++start, count);
            vec.pop_back();
        } // while (start < last)
    } // if (count-- > 0)
} // process_next_entry

// This is a valid solution to this problem
std::vector<std::vector<int>> recursive_attempt_two(std::vector<int> const & S) {
    std::vector<std::vector<int>> power_set = {{}}; // initially set it to include the empty set.

    for (int count = static_cast<int>(S.size()) ; count-- > 0 ; ) {
        for (int start = 0 ; start < S.size() ; ) {
            std::vector<int> vec = { S[start++] };
            process_next_entry(power_set, vec, S, start, count);
        } // for (int start = 0 ; start < S.size() ; )
    } // for (int count = static_cast<int>(S.size()) ; count-- > 0 ; )

    return power_set;
} // recursive_attempt_two

// This is a valid solution to this problem.  The difference between the prior attempt is that it
// insures that the recursive call can generate a valid set since there is enough entries remaining
// that can fulfill the required number of entries in the set.
std::vector<std::vector<int>> recursive_attempt_three(std::vector<int> const & S) {
    std::vector<std::vector<int>> power_set = {{}}; // initially set it to include the empty set.

    for (int count = static_cast<int>(S.size()) ; count-- > 0 ; ) {
        const int end = static_cast<int>(S.size()) - count;
        for (int start = 0 ; start < end ; ) {
            std::vector<int> vec = { S[start++] };
            process_next_entry(power_set, vec, S, start, count);
        } // for (int start = 0 ; start < end ; )
    } // for (int count = static_cast<int>(S.size()) ; count-- > 0 ; )

    return power_set;
} // recursive_attempt_three

std::vector<std::vector<int>> Solution::findPowerSet(std::vector<int> const & S) {
    return recursive_attempt_three(S);
} // findPowerSet

} // namespace power_set

} // namespace backtracking

} // namespace valhalla
