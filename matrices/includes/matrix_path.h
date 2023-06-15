/**
 * @file matrix_path.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-06-15
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */
#ifndef __MATRIX_PATH_H__
#define __MATRIX_PATH_H__

#include <set>
#include <vector>

namespace valhalla {
    namespace matrices {
        namespace matrix_path {
            class Solution {
            public:
                std::set<std::vector<int>> findAllPaths(std::vector<std::vector<int>> const &);
            };
        }
    }
}

#endif
