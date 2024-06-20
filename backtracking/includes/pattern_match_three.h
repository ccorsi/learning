/**
 * @file pattern_match_three.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-07-04
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */
#ifndef __PATTERN_MATCH_THREE_H__
#define __PATTERN_MATCH_THREE_H__

#include <string>
#include <cstddef>
#include <map>

namespace valhalla {

namespace backtracking {

namespace pattern_match_three {

class Solution {
    void compare(std::string &, std::string &, const std::size_t,
                 const std::size_t, std::map<char,std::string> &, bool &);
public:
    bool checkPattern(std::string, std::string);
};

} // namespace pattern_match_three

} // namespace backtracking

} // namespace valhalla

#endif
