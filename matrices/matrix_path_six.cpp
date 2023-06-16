/**
 * @file matrix_path_six.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=MatrixPathVI
 * @version 0.1
 * @date 2023-06-16
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "matrix_path_six.h"

namespace valhalla {
    namespace matrices {
        namespace matrix_path_six {
            /*

            Given an `M × N` rectangular grid, efficiently count all paths starting from the
            first cell (0, 0) to the last cell (M-1, N-1). You can either move down or move
            towards right from a cell.

            Input : M = 3, N = 3

            Output: 6

            Explanation: Total number of paths are 6, as shown below:

            (0, 0) —> (0, 1) —> (0, 2) —> (1, 2) —> (2, 2)
            (0, 0) —> (0, 1) —> (1, 1) —> (1, 2) —> (2, 2)
            (0, 0) —> (0, 1) —> (1, 1) —> (2, 1) —> (2, 2)
            (0, 0) —> (1, 0) —> (2, 0) —> (2, 1) —> (2, 2)
            (0, 0) —> (1, 0) —> (1, 1) —> (1, 2) —> (2, 2)
            (0, 0) —> (1, 0) —> (1, 1) —> (2, 1) —> (2, 2)

            */

            long Solution::countPaths(int m, int n) {
                long paths = -1;



                return paths;
            } // countPaths
        }
    }
}
