/**
 * @file search_matrix_two.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-03-03
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __SEARCH_MATRIX_TWO_H__
#define __SEARCH_MATRIX_TWO_H__

#include <utility>
#include <set>
#include <vector>
#include <string>

namespace valhalla {
    namespace matrices {
        namespace search_matrix_two {
            class Solution {
                bool is_valid_move(std::vector<std::vector<char>> const &, std::vector<std::pair<int,int>> const &, char, std::pair<int,int> const &);
                bool contains(std::vector<std::pair<int,int>> const &, std::pair<int,int> const &);
            public:
                std::set<std::vector<std::pair<int,int>>> searchMatrix(std::vector<std::vector<char>> const &, std::string);
            };
        }
    }
}

#endif
