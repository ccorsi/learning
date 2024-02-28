/**
 * @file maximum_sum_submatrix_two.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-06-20
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */
#ifndef __MAXIMUM_SUM_SUBMATRIX_TWO_H__
#define __MAXIMUM_SUM_SUBMATRIX_TWO_H__

#include <vector>

namespace valhalla {
    namespace matrices {
        namespace maximum_sum_submatrix_two {
            class Solution {
                void check(std::vector<std::vector<int>> const &, const int, const int,
                           int & max_sum, std::pair<int,int> &, std::pair<int,int> &);
            public:
                std::vector<std::vector<int>> findMaxSumSubmatrix(std::vector<std::vector<int>> const &);
            };
        }
    }
}

#endif
