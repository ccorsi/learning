/**
 * @file isomorphic_strings.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=IsomorphicStrings
 * @version 0.1
 * @date 2023-02-20
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <map>

#include "isomorphic_strings.h"

/*

Given two strings, check if they are isomorphic. Two strings, X and Y, are called isomorphic if all occurrences of each character in X can be replaced with another character to get Y and vice-versa.

Note that mapping from a character to itself is allowed, but the same character may not replace two characters.

Input: X = "ACAB", Y = "XCXY"
Output: true
Explanation: The strings "ACAB" and "XCXY" are isomorphic as we can map 'A' to 'X', 'B' to 'Y', and 'C' to 'C'.

Input: X = "xbxb", Y = "Ybyb"
Output: false

*/
bool valhalla::strings::isomorphic_strings::Solution::isIsomorphic(std::string X, std::string Y) {
    if (X == Y) return true;

    if (X.size() != Y.size()) return false;

    std::map<char,char> transpose;

    for (std::string::size_type pos = 0 ; pos < X.size() ; pos++) {
        if (transpose.find(X[pos]) != transpose.end() && transpose[X[pos]] != Y[pos]) return false;

        transpose[X[pos]] = Y[pos];
    } // for

    return true;
}
