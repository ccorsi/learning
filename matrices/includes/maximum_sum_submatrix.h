/**
 * @file maximum_sum_submatrix.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-06-20
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */
#ifndef __MAXIMUM_SUM_SUBMATRIX_H__
#define __MAXIMUM_SUM_SUBMATRIX_H__

#include <vector>

namespace valhalla {
    namespace matrices {
        namespace maximum_sum_submatrix {
            class Solution {
            public:
                std::vector<std::vector<int>> findMaxSumSubmatrix(std::vector<std::vector<int>> const &, int);
            };
        }
    }
}

#endif
