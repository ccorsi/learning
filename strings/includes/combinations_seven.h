/**
 * @file combinations_seven.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-03-03
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __COMBINATIONS_SEVEN_H__
#define __COMBINATIONS_SEVEN_H__

#include <unordered_set>
#include <vector>
#include <string>
#include <set>
#include <map>

namespace valhalla {
    namespace strings {
        namespace combinations_seven {
            class Solution {
                void findCombination(std::vector<std::vector<char>> const &, std::vector<int> const &, std::unordered_set<std::string> &,
	                                 std::string const &, int, std::map<int,char> &);
            public:
                std::unordered_set<std::string> findCombinations(std::vector<std::vector<char>> const &, std::vector<int> const &);
            };
        }
    }
}

#endif
