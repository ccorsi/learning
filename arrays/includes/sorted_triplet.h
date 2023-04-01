/**
 * @file sorted_triplet.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-03-28
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __SORTED_TRIPLET_H__
#define __SORTED_TRIPLET_H__

#include <vector>
#include <tuple>

namespace valhalla {
    namespace arrays {
        namespace sorted_triplet {
            class Solution {
            public:
                std::tuple<int,int,int> findSortedTriplet(std::vector<int> const &);
            };
        }
    }
}

#endif
