/**
 * @file longest_common_prefix.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=LongestCommonPrefix
 * @version 0.1
 * @date 2023-02-22
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "longest_common_prefix.h"

/*

Given a set of strings, find their longest common prefix (LCP).

Input: ["technique", "technician", "technology", "technical"]
Output: "techn"

Input: ["techie delight", "tech", "techie", "technology", "technical"]
Output: "tech"

*/

std::string valhalla::strings::longest_common_prefix::Solution::findLCP(std::vector<std::string> const & words) {
    std::string common;

    if (words.empty()) return common;

    std::vector<std::string>::const_iterator itr = words.begin();

    common = *itr;

    for ( ; itr != words.end() ; itr++) {
        std::string word = *itr;
        std::string::size_type last = std::min(word.length(), common.length());
        std::string::size_type pos = 0;

        while (pos < last && word[pos] == common[pos]) pos++;

        common = word.substr(0,pos);
    } // for

    return common;
}
