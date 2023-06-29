/**
 * @file infix_to_postfix.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=InfixToPostfix
 * @version 0.1
 * @date 2023-06-28
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "infix_to_postfix.h"

namespace valhalla {
    namespace strings {
        namespace infix_to_postfix {
            /*

            Given an infix expression, convert it to the postfix expression. Assume
            that the infix expression is a string of tokens without any whitespace.

            Input: "A*B+C"
            Output: "AB*C+"

            Input: "(A+B)*(C/D)"
            Output: "AB+CD/*"

            Input: "A*(B*C+D*E)+F"
            Output: "ABC*DE*+*F+"

            Input: "(A+B)*C+(D-E)/F+G"
            Output: "AB+C*DE-F/+G+"

            */

            std::string Solution::infixToPostfix(std::string infix) {
                std::string postfix;



                return postfix;
            } // infixToPostfix
        }
    }
}
