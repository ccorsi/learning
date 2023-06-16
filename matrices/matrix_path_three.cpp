/**
 * @file matrix_path_three.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=MatrixPathIII
 * @version 0.1
 * @date 2023-06-16
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "matrix_path_three.h"

namespace valhalla {
    namespace matrices {
        namespace matrix_path_three {
            /*

            Given a `N × N` binary matrix, find the total number of unique paths that a robot
            can take to reach a given destination from a given source.

            Positions in the matrix will either be open or blocked with an obstacle. The
            value 0 represents a blocked cell and 1 represents an open cell. The robot can
            only move to positions without obstacles, i.e., the solution should find paths
            that contain only open cells. Retracing the one or more cells back and forth is
            not considered a new path. The set of all cells covered in a single path should be
            unique from other paths. At any given moment, the robot can only move one step in
            either of the four directions (Top, Down, Left, Right).

            Input:

            matrix = [
                [1, 1, 1, 1],
                [1, 1, 0, 1],
                [0, 1, 0, 1],
                [1, 1, 1, 1]
            ]

            src  = (0, 0)
            dest = (3, 3)

            Output: 4

            Explanation: The above matrix contains 4 unique paths from source to destination
            (Marked with x).

            [x  x  x  x]	[x  x  1  1]	[x  1  1  1]	[x  x  x  x]
            [1  1  0  x]	[1  x  0  1]	[x  x  0  1]	[x  x  0  x]
            [0  1  0  x]	[0  x  0  1]	[0  x  0  1]	[0  1  0  x]
            [1  1  1  x]	[1  x  x  x]	[1  x  x  x]	[1  1  1  x]

            */

            int Solution::countPaths(std::vector<std::vector<int>> const & mat, std::pair<int,int> const & src, std::pair<int,int> const & dest) {
                int paths = -1;



                return paths;
            } // countPaths
        }
    }
}
