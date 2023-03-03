/**
 * @file combinations.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-03-03
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __COMBINATIONS_H__
#define __COMBINATIONS_H__

#include <set>
#include <vector>

namespace valhalla {
    namespace arrays {
        namespace combinations {
            class Solution {
                static void findCombination(std::set<std::vector<int>> &, std::vector<int> const &, int, std::vector<int> const &, const int);
            public:
                std::set<std::vector<int>> findCombinations(std::vector<int> const &, int);
            };
        }
    }
}

#endif
