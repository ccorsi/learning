/**
 * @file matrix_path_four.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-06-16
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */
#ifndef __MATRIX_PATH_FOUR_H__
#define __MATRIX_PATH_FOUR_H__

#include <set>
#include <vector>

namespace valhalla {
    namespace matrices {
        namespace matrix_path_four {
            class Solution {
            public:
                std::set<std::vector<int>> findAllPaths(std::vector<std::vector<int>> const &);
            };
        }
    }
}

#endif
