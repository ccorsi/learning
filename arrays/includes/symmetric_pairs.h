/**
 * @file symmetric_pairs.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-03-23
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __SYMMETRIC_PAIRS_H__
#define __SYMMETRIC_PAIRS_H__

#include <utility>
#include <set>

namespace valhalla {
    namespace arrays {
        namespace symmetric_pairs {
            class Solution {
            public:
                std::set<std::set<std::pair<int,int>>> findSymmetricPairs(std::set<std::pair<int,int>> const &);
            };
        }
    }
}

#endif
