/**
 * @file combinations_six.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-03-03
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __COMBINATIONS_SIX_H__
#define __COMBINATIONS_SIX_H__

#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <string>

namespace valhalla {
    namespace strings {
        namespace combinations_six {
            class Solution {
                void findCombination(std::unordered_set<std::string> &, std::unordered_map<int,std::vector<char>> &, std::string const &,
	                                 const int, std::vector<int> const &);
            public:
                std::unordered_set<std::string> findCombinations(std::unordered_map<int,std::vector<char>> &, std::vector<int> &);
            };
        }
    }
}

#endif
