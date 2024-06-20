/**
 * @file transform_string_two.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=TransformStringII
 * @version 0.1
 * @date 2023-06-23
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "transform_string_two.h"

namespace valhalla {
    namespace strings {
        namespace transform_string_two {
            /*

            Given two strings, determine whether the first string can be transformed into the
            second string with a single edit operation. An edit operation can insert, remove,
            or replace a character in the first string.

            Input : X = "xyz", Y = "xz"
            Output: true
            Explanation: The total number of edits required is 1 (remove 'y' from the first string)

            Input : X = "xyz", Y = "xyyz"
            Output: true
            Explanation: The total number of edits required is 1 (add 'y' in the first string)

            Input : X = "xyz", Y = "xyx"
            Output: true
            Explanation: The total number of edits required is 1 (replace 'z' in the first string by 'x')

            Input : X = "xyz", Y = "xxx"
            Output: false
            Explanation: The total number of edits required are 2 (replace 'y' and 'z' in the first string by 'x')

            Input : X = "xyz", Y = "xyz"
            Output: false
            Explanation: The total number of edits required is 0 (both strings are the same)

            */

            bool Solution::isTransformable(std::string X, std::string Y) {

                if (X.size() == Y.size()) {
                    // We need to find a single character that is different
                    if (X == Y) {
                        // No transformation since the two strings are the same
                        return false;
                    } // if (X == Y)

                    int cnt = 0;

                    for (auto idx = 0 ; cnt < 2 && idx < X.size() ; idx++) {
                        if (X[idx] != Y[idx]) cnt++;
                    } // for (auto idx = 0 ; idx < X.size() ; idx++)

                    return cnt == 1;
                } // if (X.size() == Y.size())

                if (X.size() + 1 != Y.size() && X.size() != Y.size() + 1) {
                    // The strings differ by at least 2 so it is not possible to change a single character.
                    return false;
                } // if (X.size() + 1 != Y.size() && X.size() != Y.size() + 1)

                auto cnt = 0;
                if (X.size() > Y.size()) {
                    for (auto idx = 0 ; cnt < 2 && idx < Y.size() ; idx++) {
                        if (Y[idx] != X[idx + cnt]) cnt++;
                    } // for (auto idx = 0 ; cnt < 2 && idx < Y.size() ; idx++)
                } else {
                    for (auto idx = 0 ; cnt < 2 && idx < X.size() ; idx++) {
                        if (X[idx] != Y[idx + cnt]) cnt++;
                    } // for (auto idx = 0 ; cnt < 2 && idx < Y.size() ; idx++)
                } // if (X.size() > Y.size())

                return cnt < 2;
            } // isTransformable
        }
    }
}
