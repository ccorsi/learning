/**
 * @file two_diff.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-03-20
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __TWO_DIFF_H__
#define __TWO_DIFF_H__

#include <utility>
#include <set>
#include <vector>

namespace valhalla {
    namespace arrays {
        namespace two_diff {
            class Solution {
            public:
                std::set<std::pair<int,int>> findPairs(std::vector<int> const &, int);
            };
        }
    }
}

#endif
