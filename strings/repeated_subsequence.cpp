/**
 * @file repeated_subsequence.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=RepeatedSubsequence
 * @version 0.1
 * @date 2023-02-13
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

#include "repeated_subsequence.h"

/*

Given a string, check if a repeated subsequence is present in it or not. The repeated subsequence should have a length of 2 or more.

Input: "XYBAXB"
Output: true
Explanation: String "XYBAXB" has XB(XBXB) as a repeated subsequence

Input: "XBXAXB"
Output: true
Explanation: String "XBXAXB" has XX(XXX) as a repeated subsequence

Input: "XYBYAXBY"
Output: true
Explanation: String "XYBYAXBY" has XB(XBXB), XY(XYXY), YY(YYY), YB(YBYB), and YBY(YBYBY) as repeated subsequences.

Input: "ABCA"
Output: false
Explanation: String "ABCA" doesn’t have any repeated subsequence

*/

bool valhalla::strings::repeated_subsequence::Solution::hasRepeatedSubsequence(std::string s) {
    std::map<char,std::vector<std::string::size_type>> letters;

    for (std::string::size_type idx = 0 ; idx < s.length() ; idx++) {
        char key = s[idx];
        letters[key].push_back(idx);
        if (letters[key].size() > 2) {
            // we are done return true
            return true;
        } // if
    } // for

    if (letters.size() < s.length() - 1) {
        // we might contain a sequence that will work
        // so look for all sequences of more than one index
        std::vector<std::vector<std::string::size_type>> entries;

        for (std::map<char,std::vector<std::string::size_type>>::value_type value : letters) {
            if (value.second.size() > 1)
                entries.push_back(value.second);
        } // for

        // std::cout << "Before entries: [";
        // for (std::vector<std::string::size_type> entry : entries) {
        //     std::cout << " [";
        //     for (std::string::size_type v : entry)
        //         std::cout << " " << v;
        //     std::cout << " ]";  
        // } // for
        // std::cout << " ]" << std::endl;
        std::stable_sort(entries.begin(), entries.end());
        // std::cout << "After entries: [";
        // for (std::vector<size_t> entry : entries) {
        //     std::cout << " [";
        //     for (std::string::size_type v : entry)
        //         std::cout << " " << v;
        //     std::cout << " ]";  
        // } // for
        // std::cout << " ]" << std::endl;

        // determine if we have a sequence but we only need to find two entries
        for (std::string::size_type outter = 0 ; outter < entries.size() ; outter++) {
            for (std::string::size_type inner = outter + 1 ; inner < entries.size() ; inner++) {
                if (entries[outter][1] < entries[inner][1]) {
                    // we are done
                    return true;
                } // if
            } // for inner
        } // for outter
    } // if

    return false;
}