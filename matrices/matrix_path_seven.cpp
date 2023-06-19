/**
 * @file matrix_path_seven.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=MatrixPathVII
 * @version 0.1
 * @date 2023-06-17
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "matrix_path_seven.h"

namespace valhalla {
    namespace matrices {
        namespace matrix_path_seven {
            /*

            Given an `M × N` integer matrix where each cell has a non-negative cost associated
            with it, count the number of paths to reach the last cell (M-1, N-1) of the matrix
            from its first cell (0, 0) such that the path has given cost. You can only move one
            unit right or one unit down from any cell, i.e., from cell (i, j), you can move to
            (i, j+1) or (i+1, j).

            Input:

            mat = [
                [4, 7, 1, 6],
                [5, 7, 3, 9],
                [3, 2, 1, 2],
                [7, 1, 6, 3]
            ]

            cost: 25

            Output: 2

            Explanation: The following two paths have a cost of 25.


                4 — 7 — 1   6				4   7   1   6
                        |					|
                5   7   3   9				5 — 7 — 3   9
                        |							|
                3   2   1   2				3   2   1 — 2
                        |								|
                7   1   6 — 3				7   1   6   3

            */

            int Solution::countPaths(std::vector<std::vector<int>> const & mat, int cost) {
                int paths = -1;



                return paths;
            } // countPaths
        }
    }
}
