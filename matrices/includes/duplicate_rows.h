/**
 * @file duplicate_rows.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-06-20
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */
#ifndef __DUPLICATE_ROWS_H__
#define __DUPLICATE_ROWS_H__

#include <vector>
#include <unordered_set>

namespace valhalla {
    namespace matrices {
        namespace duplicate_rows {
            class Solution {
            public:
                std::unordered_set<int> findDuplicateRows(std::vector<std::vector<int>> const &);
            };
        }
    }
}

#endif
