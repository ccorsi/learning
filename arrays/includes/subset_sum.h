/**
 * @file subset_sum.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-03-08
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __SUBSET_SUM_H__
#define __SUBSET_SUM_H__

#include <vector>
#include <set>

namespace valhalla {
    namespace arrays {
        namespace subset_sum {
            class Solution {
                void processInput(std::set<std::vector<int>> &, std::vector<int> &, int, int);
                void countWay(std::set<std::vector<int>> &, std::vector<int> &, std::vector<int> const &, int, const int, int);
            public:
                int countWays(std::vector<int> const &, int);
            };
        }
    }
}

#endif
