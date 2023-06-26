/**
 * @file duplicate_parenthesis.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=DuplicateParenthesis
 * @version 0.1
 * @date 2023-06-26
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "duplicate_parenthesis.h"

namespace valhalla {
    namespace strings {
        namespace duplicate_parenthesis {
            /*

            Given a balanced expression that can contain opening and closing parenthesis,
            check if it contains any duplicate parenthesis or not.

            Input: "((x+y))+z"
            Output: true
            Explanation: Duplicate () found in subexpression ((x+y))

            Input: "(x+y)"
            Output: false
            Explanation: No duplicate () is found

            Input: "((x+y)+((z)))"
            Output: true
            Explanation: Duplicate () found in subexpression ((z))

            */

            bool Solution::hasDuplicateParenthesis(std::string s) {
                bool hasDuplicate = false;



                return hasDuplicate;
            } // hasDuplicateParenthesis
        }
    }
}
