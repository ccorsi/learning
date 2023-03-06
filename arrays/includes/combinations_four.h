/**
 * @file combinations_four.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-03-03
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __COMBINATIONS_FOUR_H__
#define __COMBINATIONS_FOUR_H__

#include <set>
#include <vector>
#include <map>

namespace valhalla {
    namespace arrays {
        namespace combinations_four {
            class Solution {
                void findCombination(std::set<std::vector<int>> &, std::vector<int> const &, const int, const int,
                                     std::set<std::map<int,int>> &, std::map<int,int>, std::vector<int> const &,
                                     const int);
            public:
                std::set<std::vector<int>> findCombinations(std::vector<int> &, int);
            };
        }
    }
}

#endif
