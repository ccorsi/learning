/**
 * @file derive_string.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief 
 * @version 0.1
 * @date 2023-01-01
 * 
 * @copyright Copyright (c) 2023 Claudio Corsi
 * 
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

// #include <map>
// #include <vector>

#include "derive_string.h"

/*

Check if a given string can be derived from another string by circularly rotating it. The rotation can be in a clockwise or anti-clockwise rotation.

Input: X = "ABCD", Y = "DABC"
Output: true
Explanation: "DABC" can be derived from "ABCD" by right-rotating it by 1 unit

*/

bool valhalla::strings::derive_string::Solution::exists(std::string& left, std::string& right) {
    // check if the strings are the same length
    if (left.length() != right.length()) {
        return false;
    }

    // check if they are the same string
    if (left == right) {
        return true;
    }

    // std::map<char,std::vector<size_t>> chars;

    // Okay so now we have two strings that are the same length and that they are not the same
    std::string::size_type lidx, ridx, prior = 0;
    const std::string::size_type size = left.size();

    while (prior < size) {
        lidx = 0;
        ridx = prior = right.find(left[0], prior);

        if (ridx == right.npos) {
            return false;
        }

        bool same = true;

        // check for similarity
        for(std::string::size_type cnt = 0 ; cnt < size ; cnt++) {
            if (left[lidx] != right[ridx]) {
                same = false;
            }
            lidx = (lidx + 1) % size;
            ridx = (ridx + 1) % size;
        } // for

        if (same) {
            return true;
        } // if

        // increment start of character search
        prior++;
    } // while

    // strings are not derivable
    return false;
}