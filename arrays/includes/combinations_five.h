/**
 * @file combinations_five.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-03-03
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __COMBINATIONS_FIVE_H__
#define __COMBINATIONS_FIVE_H__

#include <set>
#include <vector>
#include <map>

namespace valhalla {
    namespace arrays {
        namespace combinations_five {
            class Solution {
                void findCombination(std::set<std::vector<int>> &, std::vector<int> const &,
                                     std::set<std::map<int,int>> &, std::map<int,int> const &,
                                     const int, const int);
            public:
                std::set<std::vector<int>> findCombinations(int);
            };
        }
    }
}

#endif
