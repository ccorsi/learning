/**
 * @file check_circular_moves.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=CheckCircularMoves
 * @version 0.1
 * @date 2023-06-22
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "check_circular_moves.h"

namespace valhalla {
    namespace strings {
        namespace check_circular_moves {
            /*

            Check if a given set of moves is circular or not. A move is circular if its starting
            and ending coordinates are the same. The moves can contain instructions to move one
            unit in the same direction (M), to change direction to the left of current direction (L),
            and to change direction to the right of current direction (R).

            Input: "MRMRMRM"
            Output: true

            Input: "MRMLMRMRMMRMM"
            Output: true

            Assume that the initial direction is North.

            */

            bool Solution::isCircularMove(std::string s) {
                bool result = false;



                return result;
            } // isCircularMove
        }
    }
}
