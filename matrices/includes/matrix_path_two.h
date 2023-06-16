/**
 * @file matrix_path_two.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-06-16
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */
#ifndef __MATRIX_PATH_TWO_H__
#define __MATRIX_PATH_TWO_H__

#include <utility>
#include <vector>

namespace valhalla {
    namespace matrices {
        namespace matrix_path_two {
            class Solution {
            public:
                std::vector<std::pair<int,int>> findPath(std::vector<std::vector<int>> const &);
            };
        }
    }
}

#endif
