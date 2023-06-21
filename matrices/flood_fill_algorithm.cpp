/**
 * @file flood_fill_algorithm.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=FloodFillAlgorithm
 * @version 0.1
 * @date 2023-06-20
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "flood_fill_algorithm.h"

namespace valhalla {
    namespace matrices {
        namespace flood_fill_algorithm {
            /*

            Flood fill is an algorithm that determines the area connected to a given node in a
            multi-dimensional array. It is used in the "bucket" fill tool of a paint program to
            fill connected, similarly colored areas with a different color and in games such as
            Go and Minesweeper for determining which pieces are cleared. When applied on an
            image to fill a particular bounded area with color, it is also known as boundary
            fill.

            The flood fill algorithm takes three parameters: a start node, a target color, and
            a replacement color. The algorithm looks for all nodes in the matrix that are
            connected to the start node by a path of the target color and changes them to the
            replacement color.

            Input:

            Matrix = [
                [Y, Y, Y, G, G, G, G, G, G, G],
                [Y, Y, Y, Y, Y, Y, G, V, V, V],
                [G, G, G, G, G, G, G, V, V, V],
                [W, W, W, W, W, G, G, G, G, V],
                [W, R, R, R, R, R, G, V, V, V],
                [W, W, W, R, R, G, G, V, V, V],
                [W, B, W, R, R, R, R, R, R, V],
                [W, B, B, B, B, R, R, V, V, V],
                [W, B, B, V, B, B, B, B, V, V],
                [W, B, B, V, V, V, V, V, V, V]
            ]

            (x, y) = (3, 9)				(Start node, having a target color `V`)
            Replacement Color = O

            Output:
            [
                [Y, Y, Y, G, G, G, G, G, G, G],
                [Y, Y, Y, Y, Y, Y, G, O, O, O],
                [G, G, G, G, G, G, G, O, O, O],
                [W, W, W, W, W, G, G, G, G, O],
                [W, R, R, R, R, R, G, O, O, O],
                [W, W, W, R, R, G, G, O, O, O],
                [W, B, W, R, R, R, R, R, R, O],
                [W, B, B, B, B, R, R, O, O, O],
                [W, B, B, O, B, B, B, B, O, O],
                [W, B, B, O, O, O, O, O, O, O]
            ]

            */

            void Solution::floodfill(std::vector<std::vector<char>> & mat, int x, int y, char replacement) {



            } // floodfile
        }
    }
}
