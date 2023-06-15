/**
 * @file shortest_path_two.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=ShortestPathII
 * @version 0.1
 * @date 2023-06-14
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "shortest_path_two.h"

namespace valhalla {
    namespace matrices {
        namespace shortest_path_two {
            /*

            Given a rectangular field with few sensors present, cross it by taking the shortest
            safe route without activating the sensors.

            The rectangular field is in the form of an `M × N` matrix, find the shortest path
            from any cell in the first column to any cell in the last column of the matrix.
            The sensors are marked by the value 0 in the matrix, and all its eight adjacent
            cells can also activate the sensors. The path can only be constructed out of cells
            having value 1, and at any given moment, you are only allowed to move one step in
            either of the 4 directions - Up, Left, Down, Right.

            Input:

            mat = [
                [0, 1, 1, 1, 0, 1, 1, 1, 1, 1],
                [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
                [1, 1, 1, 1, 1, 1, 1, 1, 0, 1],
                [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
                [1, 1, 1, 1, 1, 0, 1, 1, 1, 1],
                [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
                [1, 0, 1, 1, 1, 1, 1, 1, 1, 1],
                [1, 1, 1, 1, 1, 1, 1, 1, 1, 0],
                [1, 1, 1, 1, 1, 0, 1, 1, 1, 1],
                [1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
            ]

            Output: 11

            The shortest safe path has a length of 11, and the route is marked in green below.

            https://techiedelight.com/practice/images/Shortest-Path.png

            The solution should return -1 if there is no safe route to reach the destination.

            */

            int Solution::findShortestDistance(std::vector<std::vector<int>> & mat ) {
                int shortest = -1;



                return shortest;
            } // findShortestDistance
        }
    }
}
