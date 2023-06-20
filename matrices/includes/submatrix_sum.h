/**
 * @file submatrix_sum.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-06-20
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */
#ifndef __SUBMATRIX_SUM_H__
#define __SUBMATRIX_SUM_H__

#include <vector>

namespace valhalla {
    namespace matrices {
        namespace submatrix_sum {
            class Solution {
            public:
                int findSubmatrixSum(std::vector<std::vector<int>> const &, int, int, int, int);
            };
        }
    }
}

#endif
