/**
 * @file spiral_matrix_three.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-02-11
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __SPIRAL_MATRIX_THREE_H__
#define __SPIRAL_MATRIX_THREE_H__

#include <vector>

namespace valhalla {
    namespace matrices {
        namespace spiral_matrix_three {
            class Solution {
            public:
                std::vector<std::vector<int>> createSpiralMatrix(std::vector<int> const &);
            };
        }
    }
}

#endif
