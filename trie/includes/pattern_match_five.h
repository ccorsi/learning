/**
 * @file pattern_match_five.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-07-05
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */
#ifndef __PATTERN_MATCH_FIVE_H__
#define __PATTERN_MATCH_FIVE_H__

#include <string>
#include <unordered_set>

namespace valhalla {

namespace trie {

namespace pattern_match_five {

class Solution {
public:
    std::unordered_set<std::string> patternMatch(std::unordered_set<std::string> const &, std::string);
};

} // namespace pattern_match_five

} // namespace trie

} // namespace valhalla

#endif
