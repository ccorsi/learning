/**
 * @file matrix_path_three.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-06-16
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */
#ifndef __MATRIX_PATH_THREE_H__
#define __MATRIX_PATH_THREE_H__

#include <utility>
#include <vector>

namespace valhalla {
    namespace matrices {
        namespace matrix_path_three {
            class Solution {
            public:
                int countPaths(std::vector<std::vector<int>> const &, std::pair<int,int> const &, std::pair<int,int> const &);
            };
        }
    }
}

#endif