/**
 * @file matrix_path_two.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=MatrixPathII
 * @version 0.1
 * @date 2023-06-16
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "matrix_path_two.h"

namespace valhalla {
    namespace matrices {
        namespace matrix_path_two {
            /*

            Given an `N × N` matrix of positive integers, find a path from the first cell of the
            matrix to its last.

            You are allowed to move exactly `k` steps from any cell in the matrix where `k` is
            the cell's value, i.e., from a cell (i, j) having value `k` in a matrix `M`, you can
            move to (i+k, j), (i-k, j), (i, j+k), or (i, j-k). The diagonal moves are not allowed.

            In case multiple paths exists, the solution can return any one of them.

            Input:

            M = [
                [7, 1, 3, 5, 3, 6, 1, 1, 7, 5],
                [2, 3, 6, 1, 1, 6, 6, 6, 1, 2],
                [6, 1, 7, 2, 1, 4, 7, 6, 6, 2],
                [6, 6, 7, 1, 3, 3, 5, 1, 3, 4],
                [5, 5, 6, 1, 5, 4, 6, 1, 7, 4],
                [3, 5, 5, 2, 7, 5, 3, 4, 3, 6],
                [4, 1, 4, 3, 6, 4, 5, 3, 2, 6],
                [4, 4, 1, 7, 4, 3, 3, 1, 4, 2],
                [4, 4, 5, 1, 5, 2, 3, 5, 3, 5],
                [3, 6, 3, 5, 2, 2, 6, 4, 2, 1]
            ]

            Output: [(0, 0) (7, 0) (3, 0) (9, 0) (6, 0) (2, 0) (8, 0) (4, 0) (4, 5) (0, 5) (6, 5) (2, 5)
                     (2, 1) (1, 1) (4, 1) (9, 1) (3, 1) (3, 7) (2, 7) (8, 7) (8, 2) (3, 2) (3, 9) (7, 9)
                     (9, 9)]

            or

            [(0, 0) (7, 0) (3, 0) (9, 0) (6, 0) (2, 0) (8, 0) (4, 0) (4, 5) (8, 5) (6, 5) (2, 5) (2, 9)
             (4, 9) (8, 9) (3, 9) (7, 9) (9, 9)]

            or any other valid path from first cell to last cell.

            */

            std::vector<std::pair<int,int>> Solution::findPath(std::vector<std::vector<int>> const & mat) {
                std::vector<std::pair<int,int>> paths;



                return paths;
            } // findPath
        }
    }
}
