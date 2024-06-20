/**
 * @file largest_square_submatrix_two.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-06-01
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */
#ifndef __LARGEST_SQUARE_SUBMATRIX_TWO_H__
#define __LARGEST_SQUARE_SUBMATRIX_TWO_H__

#include <vector>

namespace valhalla {
    namespace matrices {
        namespace largest_square_submatrix_two {
            class Solution {
            public:
                int findLargestSquareSubmatrix(std::vector<std::vector<int>> const &);
            };
        }
    }
}

#endif