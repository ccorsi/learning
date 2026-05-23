/**
 * @file longest_common_subsequence_three.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=LongestCommonSubsequenceIII
 * @version 0.1
 * @date 2026-05-21
 *
 * @copyright Copyright (c) 2026 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <iostream>

#include "longest_common_subsequence_three.h"

namespace valhalla {

namespace dynamic_programming {

namespace longest_common_subsequence_three {

int attempt_one(std::string X, std::string Y, std::string Z) {
    struct finder {
        std::string & m_x, & m_y, & m_z, m_lcs;
        std::string::size_type x_size, y_size, z_size;

        finder(std::string & X, std::string & Y, std::string & Z) : m_x(X), m_y(Y), m_z(Z) {
            x_size = m_x.size();
            y_size = m_y.size();
            z_size = m_z.size();
        }

        std::string process() {
            for (std::string::size_type x_idx = 0 ; x_idx < x_size ; x_idx++) {
                std::string::size_type y_idx = m_y.find(m_x[x_idx]);
                if (y_idx != std::string::npos) {
                    std::string::size_type z_idx = m_z.find(m_x[x_idx]);
                    if (z_idx != std::string::npos) {
                        // this is where it all happens
                        find_next(x_idx, y_idx, z_idx, std::string() + m_x[x_idx]);
                    } // if (z_idx != std::string::npos)
                } // if (y_idx != std::string::npos)
            } // for (std::string::size_type x_idx = 0 ; x_idx < x_size ; x_idx++)

            return m_lcs;
        }

        void find_next(std::string::size_type x_idx, std::string::size_type y_idx, std::string::size_type z_idx, std::string cur) {
            if (cur.size() > m_lcs.size()) {
                m_lcs = cur;
            } // if (cur.size() < m_lcs.size())

            y_idx++; // increment the y_size to be able to compare with
            std::string::size_type diff = m_lcs.size() - cur.size();

            // determine if we have enough characters to be able to find a lcs longer than the current one
            if (y_idx + diff >= m_y.size()) {
                return;
            } // if (y_idx + diff >= m_y.size())

            z_idx++;

            // determine if we have enough characters to be able to find a lcs longer than the current one
            if (z_idx + diff >= m_z.size()) {
                return;
            } // if (z_idx + diff >= m_z.size())

            for (x_idx++ ; x_idx + diff < x_size ; x_idx++) {
                const char str = m_x[x_idx];
                std::string::size_type next_y_idx = m_y.find(str, y_idx);
                if (next_y_idx != std::string::npos) {
                    std::string::size_type next_z_idx = m_z.find(str, z_idx);
                    if (next_z_idx != std::string::npos) {
                        find_next(x_idx, next_y_idx, next_z_idx, cur + str);
                    } // if (next_z_idx != std::string::npos)
                } // if (next_y_idx != std::string::npos)
                diff = m_lcs.size() - cur.size();
            } // for (x_idx++ ; x_idx + diff < x_size ) ; x_idx++)
        }
    };

    return static_cast<int>(finder(X, Y, Z).process().size());
} // int attempt_one(std::string X, std::string Y, std::string Z)

/*

Given three sequences, find the length of the longest common subsequence (LCS) present
in it. The LCS is the longest subsequence that can be obtained from each of the given
sequences by deleting zero or more characters.

Input: X = "ABCBDAB", Y = "BDCABA", Z = "BADACB"
Output: 4
Explanation: The longest subsequence present in the given sequences in the same order
is "BDAB", having length 4.

*/
int Solution::findLCS(std::string X, std::string Y, std::string Z) {
    return attempt_one(X, Y, Z);
} // findLCS

} // namespace longest_common_subsequence_three

} // namespace dynamic_programming

} // namespace valhalla
