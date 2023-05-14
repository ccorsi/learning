/**
 * @file coin_change_problem_two.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-05-03
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __COIN_CHANGE_PROBLEM_TWO_H__
#define __COIN_CHANGE_PROBLEM_TWO_H__

#include <vector>
#include <set>

namespace valhalla {
    namespace arrays {
        namespace coin_change_problem_two {
            class Solution {
                void findWay(std::vector<int> const &, int, int, int, int &);
            public:
                int findWays(std::vector<int> const &, int);
            };
        }
    }
}

#endif
