/**
 * @file transform_string_three.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=TransformStringIII
 * @version 0.1
 * @date 2023-06-23
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "transform_string_three.h"

namespace valhalla {
    namespace strings {
        namespace transform_string_three {
            /*

            Given a string, remove all occurrences of "AB" and "C" in a single traversal of it.

            Input: "CBAABCAB"
            Output: "BA"

            The solution should remove of all adjacent, as well as non-adjacent occurrences of
            string "AB" and "C".

            Input: "ADAABCB"
            Output: "AD"
            Explanation: Removing the first adjacent occurrence of "AB" and "C" results in
            string "ADAB", which again needs to be processed for adjacent "AB". Therefore, the
            final output string will be "AD".

            Input: "AACBBC"
            Output: ""
            Explanation: AACBBC -> AABB -> AB -> ""

            */

            std::string Solution::remove(std::string s) {
                std::string updated;



                return updated;
            } // remove
        }
    }
}
