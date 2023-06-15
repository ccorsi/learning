/**
 * @file matrix_path.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=MatrixPath
 * @version 0.1
 * @date 2023-06-15
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "matrix_path.h"

namespace valhalla {
    namespace matrices {
        namespace matrix_path {
            /*

            Given an `M × N` integer matrix, find all paths that start at the first cell (0, 0)
            and ends at the last cell (M-1, N-1). You are allowed to move down, right, or diagonally
            (down-right), but not up or left.

            Input:
            [
                [1, 2, 3],
                [4, 5, 6],
                [7, 8, 9]
            ]

            Output:

            {
                [1, 4, 7, 8, 9],
                [1, 4, 5, 8, 9],
                [1, 4, 5, 6, 9],
                [1, 4, 5, 9],
                [1, 4, 8, 9],
                [1, 2, 5, 8, 9],
                [1, 2, 5, 6, 9],
                [1, 2, 5, 9],
                [1, 2, 3, 6, 9],
                [1, 2, 6, 9],
                [1, 5, 8, 9],
                [1, 5, 6, 9],
                [1, 5, 9]
            }

            */

            std::set<std::vector<int>> Solution::findAllPaths(std::vector<std::vector<int>> const & mat) {
                std::set<std::vector<int>> paths;



                return paths;
            } // findAllPaths
        }
    }
}
