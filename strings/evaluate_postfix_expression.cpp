/**
 * @file evaluate_postfix_expression.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=EvaluatePostfixExpression
 * @version 0.1
 * @date 2023-06-26
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "evaluate_postfix_expression.h"

namespace valhalla {
    namespace strings {
        namespace evaluate_postfix_expression {
            /*

            Given a postfix expression, efficiently evaluate it. Assume that the postfix
            expression contains only single-digit numeric operands, without any whitespace.

            Input: "82/"
            Output: 4
            Explanation: 82/ will evaluate to 4 (8/2)

            Input: "138*+"
            Output: 4
            Explanation: 138*+ will evaluate to 25 (1+8*3)

            Input: "545*+5/"
            Output: 5
            Explanation: 545*+5/ will evaluate to 5 ((5+4*5)/5)


            Assume valid postfix expression.

            */

            int Solution::evalPostfix(std::string s) {
                int value = -1;



                return value;
            } // evalPostfix
        }
    }
}
