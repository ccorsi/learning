/**
 * @file spiral_matrix.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-02-11
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __SPIRAL_MATRIX_H__
#define __SPIRAL_MATRIX_H__

#include <vector>

namespace valhalla {
    namespace matrices {
        namespace spiral_matrix {
            class Solution {
            public:
                std::vector<int> spiralTraversal(std::vector<std::vector<int>> const &);
            };
        }
    }
}

#endif
