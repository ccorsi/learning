/**
 * @file toeplitz_matrix.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-02-27
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __TOEPLITZ_MATRIX_H__
#define __TOEPLITZ_MATRIX_H__

#include <vector>

namespace valhalla {
    namespace matrices {
        namespace toeplitz_matrix {
            class Solution {
            public:
                bool checkToeplitz(std::vector<std::vector<int>> const &);
            };
        }
    }
}

#endif
