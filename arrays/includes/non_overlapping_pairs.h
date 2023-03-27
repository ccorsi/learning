/**
 * @file non_overlapping_pairs.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-03-27
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __NON_OVERLAPPING_PAIRS_H__
#define __NON_OVERLAPPING_PAIRS_H__

#include <utility>
#include <set>
#include <vector>

namespace valhalla {
    namespace arrays {
        namespace non_overlapping_pairs {
            class Solution {
            public:
                std::set<std::set<std::pair<int,int>>> findPairs(std::vector<int> const &);
            };
        }
    }
}

#endif
