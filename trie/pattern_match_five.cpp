/**
 * @file pattern_match_five.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=PatternMatchV
 * @version 0.1
 * @date 2023-07-05
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "pattern_match_five.h"

namespace valhalla {

namespace trie {

namespace pattern_match_five {

/*

Given a set of words where each word follows a CamelCase notation and a pattern
containing all uppercase characters, find all words that matches the pattern.

CamelCase Notation is the practice of writing compound words or phrases joined
without spaces, where each word's first letter is capitalized. For example,
PowerPoint, LibreOffice, CinemaScope, etc., are in CamelCase.

Input: words = {Hi, HiTech, HiTechCity, Hello, HelloWorld, HiTechLab}, pattern = HT
Output: {HiTech, HiTechCity, HiTechLab}

Input: words = {Hi, HiTech, HiTechCity, Hello, HelloWorld, HiTechLab}, pattern = HTC
Output: {HiTechCity}

Input: words = {Hi, HiTech, HiTechCity, Hello, HelloWorld, HiTechLab}, pattern = H
Output: {Hi, HiTech, HiTechCity, Hello, HelloWorld, HiTechLab}

*/

std::unordered_set<std::string> Solution::patternMatch(std::unordered_set<std::string> const & words, std::string pattern) {
    std::unordered_set<std::string> matches;


    return matches;
} // patternMatch

} // namespace pattern_match_five

} // namespace trie

} // namespace valhalla
