/**
 * @file maximum_sub_submatrix.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-06-20
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */
#ifndef __MAXIMUM_SUB_SUBMATRIX_H__
#define __MAXIMUM_SUB_SUBMATRIX_H__

#include <vector>

namespace valhalla {
    namespace matrices {
        namespace maximum_sub_submatrix {
            class Solution {
            public:
                std::vector<std::vector<int>> findMaxSubSubmatrix(std::vector<std::vector<int>> const &, int);
            };
        }
    }
}

#endif
