/**
 * @file matrix_path_four.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=MatrixPathIV
 * @version 0.1
 * @date 2023-06-16
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "matrix_path_four.h"

namespace valhalla {
    namespace matrices {
        namespace matrix_path_four {
            /*

            Given an `M × N` integer matrix, find all paths from the first cell to the last cell. You are only allowed to move down or to the right from the current cell.

            Input:

            [
                [1, 2, 3],
                [4, 5, 6],
                [7, 8, 9]
            ]

            Output:

            {
                [1, 2, 3, 6, 9],
                [1, 2, 5, 6, 9],
                [1, 2, 5, 8, 9],
                [1, 4, 5, 6, 9],
                [1, 4, 5, 8, 9],
                [1, 4, 7, 8, 9]
            }

            */

            std::set<std::vector<int>> Solution::findAllPaths(std::vector<std::vector<int>> const & mat) {
                std::set<std::vector<int>> paths;



                return paths;
            } // findAllPaths
        }
    }
}
