/**
 * @file maximum_ones_row.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-03-01
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __MAXIMUM_ONES_ROW_H__
#define __MAXIMUM_ONES_ROW_H__

#include <vector>

namespace valhalla {
    namespace matrices {
        namespace maximum_ones_row {
            class Solution {
            public:
                int findRow(std::vector<std::vector<int>> const &);
            };
        }
    }
}

#endif
