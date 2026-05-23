/**
 * @file longest_common_subsequence.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=LongestCommonSubsequence
 * @version 0.1
 * @date 2026-05-03
 *
 * @copyright Copyright (c) 2026 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <iostream>
#include <queue>

#include "longest_common_subsequence.h"

namespace valhalla {

namespace dynamic_programming {

namespace longest_common_subsequence {

/*

Given two sequences, find the length of the longest common subsequence (LCS)
present in it. The LCS is the longest sequence which can be obtained from
the first sequence by deleting some items and from the second sequence by
deleting other items.

Input: X = "ABCBDAB", Y = "BDCABA"
Output: 4
Explanation: The LCS are "BDAB", "BCAB", and "BCBA", having length 4.

*/

int attempt_one(std::string X, std::string Y) {
    struct lcs {
        lcs() = default;
        int execute(std::string X, std::string Y) {
            // iterate through X until we've exhausted each entry
            int len = 0;

            std::cout << "Process X=\"" << X << "\" Y=\"" << Y << "\"\n";
            for (auto x_idx = 0 ; x_idx < X.length() ; x_idx++) {
                auto y_idx = Y.find(X[x_idx]);
                if (std::string::npos != y_idx) {
                    std::cout << "Found character: " << X[x_idx] << " at index " << x_idx << " in at Y index " << y_idx << "\n";
                    find_next(X, x_idx, Y, y_idx, len, 1);
                } // if (std::string::npos != y_idx)
            } // for (auto x_idx = 0 ; x_idx < X.length() ; x_idx++)

            std::cout << "LCS " << len << "\n";
            return len;
        }

        void find_next(std::string & X, std::string::size_type x_idx, std::string & Y, std::string::size_type y_idx, int & len, int cur) {
            if (cur > len) {
                len = cur;
            } // if (cur > len)

            std::cout << "x_idx " << x_idx << " y_idx " << y_idx << " len " << len << " cur " << cur << "\n";
            // look for the next entry of x_idx in Y after y_idx
            auto idx = y_idx + 1;
            while (idx < Y.length() && (idx = Y.find(X[x_idx], idx)) != std::string::npos) {
                find_next(X, x_idx, Y, idx, len, cur); // check the next similar entry
                idx++; // increment the index
            } // while (idx < Y.length() && (idx = Y.find(X[x_idx], idx)) != std::string::npos)

            // let us find the next entry in the X string from x_idx + 1 within Y from y_idx + 1
            idx = y_idx + 1;
            x_idx++;
            if (x_idx < X.length() && y_idx < Y.length()) {
                while (idx < Y.length() && (idx = Y.find(X[x_idx], idx) != std::string::npos)) {
                    find_next(X, x_idx, Y, idx, len, cur + 1);
                    idx++;
                } // while (idx < Y.length() && (idx = Y.find(X[x_idx], y_idx) != std::string::npos))
            } // if (x_idx < X.length() && y_idx < Y.length())
        }
    };

    return lcs().execute(X,Y);
} // int attempt_one(std::string X, std::string Y)

int solution_too_long_two(std::string X, std::string Y) {
    // This attempt takes too long to solve the problem but it is correct
    using type = std::string::size_type;

    struct data {
        type m_x_idx, m_y_idx;
        int m_len;
        data() = default;
        data(type x_idx, type y_idx, int len) : m_x_idx(x_idx), m_y_idx(y_idx), m_len(len) {}
    };

    std::queue<struct data> states;
    int lcs = 0;

    for ( type x_idx = 0 ; x_idx < X.size() ; x_idx++) {
        type y_idx = Y.find(X[x_idx]);
        if (y_idx != std::string::npos) {
            states.push(data(x_idx, y_idx, 1));
        } // if (y_idx != std::string::npos)
    } // for ( type x_idx = 0 ; x_idx < X.size() ; x_idx++)

    while (states.empty() == false) {
        struct data state = states.front(); states.pop();

        if (state.m_len > lcs) {
            lcs = state.m_len;
        } // if (state.m_len > lcs)

        for (type x_idx = state.m_x_idx + 1 ; x_idx < X.size() ; x_idx++) {
            type y_idx;
            if ((y_idx = Y.find(X[x_idx], state.m_y_idx + 1)) != std::string::npos) {
                states.push(data(x_idx, y_idx, state.m_len + 1));
            } // if ((y_idx = Y.find(X[x_idx], state.m_y_idx + 1)) != std::string::npos)
        } // for (type x_idx = state.m_x_idx + 1 ; x_idx < X.size() ; x_idx++)

    } // while (states.empty() == false)

    return lcs;
} // int solution_too_long_two(std::string X, std::string Y)

int attempt_three(std::string X, std::string Y) {
    // This attempt takes too long to solve the problem but it is correct
    using type = std::string::size_type;

    struct data {
        type m_x_idx, m_y_idx;
        int m_len;
        data() = default;
        data(type x_idx, type y_idx, int len) : m_x_idx(x_idx), m_y_idx(y_idx), m_len(len) {}
    };

    std::queue<struct data> states;
    int lcs = 0;

    for ( type x_idx = 0 ; x_idx < X.size() ; x_idx++) {
        type y_idx = Y.find(X[x_idx]);
        if (y_idx != std::string::npos) {
            states.push(data(x_idx, y_idx, 1));
        } // if (y_idx != std::string::npos)
    } // for ( type x_idx = 0 ; x_idx < X.size() ; x_idx++)

    while (states.empty() == false) {
        struct data state = states.front(); states.pop();

        if (state.m_len + Y.size() - state.m_y_idx <= lcs) {
            // purge all states that will not be able to produce a better result
            continue;
        } // if (state.m_len + Y.size() - state.m_y_idx <= lcs)

        if (state.m_len > lcs) {
            lcs = state.m_len;
        } // if (state.m_len > lcs)

        for (type x_idx = state.m_x_idx + 1 ; x_idx < X.size() ; x_idx++) {
            type y_idx;
            if ((y_idx = Y.find(X[x_idx], state.m_y_idx + 1)) != std::string::npos) {
                states.push(data(x_idx, y_idx, state.m_len + 1));
            } // if ((y_idx = Y.find(X[x_idx], state.m_y_idx + 1)) != std::string::npos)
        } // for (type x_idx = state.m_x_idx + 1 ; x_idx < X.size() ; x_idx++)

    } // while (states.empty() == false)

    return lcs;
} // int attempt_three(std::string X, std::string Y)

int attempt_four(std::string X, std::string Y) {
    int lcs = 0;
    using size_type = std::string::size_type;
    const size_type size = X.size();

    struct finder {
        std::string & m_x, & m_y;
        int & m_lcs;
        size_type m_x_size, m_y_size;

        finder(std::string & X, std::string & Y, int & lcs) : m_x(X), m_y(Y), m_lcs(lcs) {
            m_x_size = X.size();
            m_y_size = Y.size();
        }

        int execute() {
            for (size_type idx = 0 ; idx < m_x_size ; idx++) {
                size_type y_idx = m_y.find(m_x[idx]);
                if (y_idx + 1 < m_y_size) {
                    next(idx, y_idx, 1);
                } // if (y_idx + 1 < Y.size())
            } // for (size_type idx = 0 ; idx < X.size() ; idx++)

            return m_lcs;
        }

        void next(size_type x_idx, size_type y_idx, int cur) {
            if (cur > m_lcs) {
                m_lcs = cur;
            } // if (cur > lcs)

            for ( y_idx++, x_idx++ ; x_idx < m_x_size ; x_idx++) {
                size_type idx = m_y.find(m_x[x_idx], y_idx);
                if (idx + cur + 1 < m_y_size - m_lcs) {
                    next(x_idx, idx, cur + 1);
                } // if (idx + cur + 1 < Y.size() - lcs)
            } // for ( y_idx++, x_idx++ ; x_idx < X.size() ; x_idx++)
        }
    };

    return finder(X, Y, lcs).execute();
} // int attempt_four(std::string X, std::string Y)

int solution_five(std::string X, std::string Y) {

    struct finder {
        std::string & m_x, & m_y, m_lcs;
        std::string::size_type x_size, y_size;

        finder(std::string & X, std::string & Y) : m_x(X), m_y(Y) {
            x_size = m_x.size();
            y_size = m_y.size();
        }

        std::string process() {
            for (std::string::size_type idx = 0 ; idx < x_size ; idx++) {
                std::string::size_type y_idx = m_y.find(m_x[idx]);
                if (y_idx != std::string::npos) {
                    // this is where it all happens
                    find_next(idx, y_idx, std::string() + m_x[idx]);
                } // if (y_idx != std::string::npos)
            } // for (std::string::size_type idx = 0 ; idx < x_size ; idx++)

            return m_lcs;
        }

        void find_next(std::string::size_type x_idx, std::string::size_type y_idx, std::string cur) {
            if (cur.size() > m_lcs.size()) {
                m_lcs = cur;
            } // if (cur.size() < m_lcs.size())

            y_idx++; // increment the y_size to be able to compare with
            std::string::size_type diff = m_lcs.size() - cur.size();

            // determine if we have enough characters to be able to find a lcs longer than the current one
            if (y_idx + diff >= m_y.size()) {
                return;
            } // if (y_idx + diff >= m_y.size())

            for (x_idx++ ; x_idx + diff < x_size ; x_idx++) {
                std::string::size_type idx = m_y.find(m_x[x_idx], y_idx);
                if (idx != std::string::npos) {
                    find_next(x_idx, idx, cur + m_x[x_idx]);
                } // if (idx != std::string::npos)
                diff = m_lcs.size() - cur.size();
            } // for (x_idx++ ; x_idx + diff < x_size ) ; x_idx++)
        }
    };

    return static_cast<int>(finder(X, Y).process().size());
} // int solution_five(std::string X, std::string Y)


int Solution::findLCSLength(std::string X, std::string Y) {
    return solution_five(X, Y);
} // findLCSLength

} // namespace longest_common_subsequence

} // namespace dynamic_programming

} // namespace valhalla
