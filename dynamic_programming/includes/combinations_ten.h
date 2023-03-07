/**
 * @file combinations_ten.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-03-06
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __COMBINATIONS_TEN_H__
#define __COMBINATIONS_TEN_H__

#include <vector>
#include <set>
#include <utility>

namespace valhalla {
    namespace dynamic_programming {
        namespace combinations_ten {
            class Solution {
                void findCombination(std::set<std::vector<char>> & visited, std::set<std::vector<char>> &,
                                     std::vector<char> const &, std::vector<std::vector<char>> const &,
                                     int, int, std::pair<int,int> const &);
                bool is_valid_move(std::vector<std::vector<char>> const &, std::pair<int,int> const &);
            public:
                int findCombinations(std::vector<std::vector<char>> const &, int);
            };
        }
    }
}

#endif
