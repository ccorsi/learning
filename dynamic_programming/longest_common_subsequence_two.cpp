/**
 * @file longest_common_subsequence_two.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=LongestCommonSubsequenceII
 * @version 0.1
 * @date 2026-05-19
 *
 * @copyright Copyright (c) 2026 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */
#include <iostream>

#include "longest_common_subsequence_two.h"

namespace valhalla {

namespace dynamic_programming {

namespace longest_common_subsequence_two {

std::string attempt_one(std::string X, std::string Y) {

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

    return finder(X, Y).process();
} // std::string attempt_one(std::string X, std::string Y)

/*

Given two sequences, return the longest common subsequence (LCS) present in it.
The LCS is the longest sequence which can be obtained from the first sequence
by deleting some items and from the second sequence by deleting other items.

Input: X = "XMJYAUZ", Y = "MZJAWXU"
Output: "MJAU"

The longest common subsequence is not guaranteed to be unique. If multiple
longest common subsequence exists, the solution should return any one of them.

Input: X = "ABCBDAB", Y = "BDCABA"
Output: "BDAB" or "BCAB" or "BCBA"

*/

std::string Solution::findLCS(std::string X, std::string Y) {
    return attempt_one(X, Y);
} // findLCS

} // namespace longest_common_subsequence_two

} // namespace dynamic_programming

} // namespace valhalla
