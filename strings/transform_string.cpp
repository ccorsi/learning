/**
 * @file transform_string.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=TransformString
 * @version 0.1
 * @date 2023-06-23
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "transform_string.h"

namespace valhalla {
    namespace strings {
        namespace transform_string {
            /*

            Given two strings, determine if the first string can be transformed into the
            second string. The only operation allowed is moving a character from the first
            string to the front. If the string can be transformed, find the minimum number
            of operations required for the transformation.

            Input: X = "ADCB", Y = "ABCD"
            Output: 3
            Explanation: The minimum number of operations required to convert the string
                         "ADCB" to string "ABCD" is 3.

            ADCB —> CADB (Move 'C' to the front)
            CADB —> BCAD (Move 'B' to the front)
            BCAD —> ABCD (Move 'A' to the front)

            The solution should return -1 if the string cannot be transformed.

            */

            int Solution::getMinimumOperations(std::string X, std::string Y) {
                int minOprs = -1;



                return minOprs;
            } // getMinimumOperations
        }
    }
}
