/**
 * @file wildcard_pattern_matching.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2025-02-03
 *
 * @copyright Copyright (c) 2025 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */
#ifndef __WILDCARD_PATTERN_MATCHING_H__
#define __WILDCARD_PATTERN_MATCHING_H__

#include <string>
#include <unordered_set>

namespace valhalla {

namespace backtracking {

namespace wildcard_pattern_matching {

class Solution {
public:
    std::unordered_set<std::string> findCombinations(std::string s);
};

} // namespace wildcard_pattern_matching

} // namespace backtracking

} // namespace valhalla

#endif
