/**
 * @file shift_matrix.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief 
 * @version 0.1
 * @date 2023-01-01
 * 
 * @copyright Copyright (c) 2023 Claudio Corsi
 * 
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */
#ifndef __SHIFT_MATRIX_H__
#define __SHIFT_MATRIX_H__

#include <vector>

namespace valhalla {
    namespace matrices {
        namespace shift_matrix {
            class Solution {
            public:
                void shift_matrix(std::vector<std::vector<int>> &);
            };
        }
    }
}

#endif
