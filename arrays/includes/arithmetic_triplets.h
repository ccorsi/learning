/**
 * @file arithmetic_triplets.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-03-20
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __ARITHMETIC_TRIPLETS_H__
#define __ARITHMETIC_TRIPLETS_H__

#include <set>
#include <vector>

namespace valhalla {
    namespace arrays {
        namespace arithmetic_triplets {
            class Solution {
            public:
                std::set<std::vector<int>> findTriplets(std::vector<int> const &);
            };
        }
    }
}

#endif
