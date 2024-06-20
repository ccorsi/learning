/**
 * @file balanced_expression.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=BalancedExpression
 * @version 0.1
 * @date 2023-06-23
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "balanced_expression.h"

#include <stack>
#include <stdexcept>
#include <map>

namespace valhalla {
    namespace strings {
        namespace balanced_expression {
            /*

            Given a string containing opening and closing braces, determine if it represents
            a balanced expression or not.

            Input: "{[{}{}]}[()]"
            Output: true

            Input: "{{}{}}"
            Output: true

            Input: "[]{}()"
            Output: true

            Input: "{()}[)"
            Output: false

            Input: "{(})"
            Output: false

            */

            bool Solution::isBalanced(std::string s) {
                std::stack<char> letters;
                static std::map<char,char> validate = {
                    { ']', '[' },
                    { ')', '(' },
                    { '}', '{' },
                };

                for (char chr : s) {
                    switch (chr) {
                        case '[': case '{': case '(':
                            letters.push(chr);
                            break;
                        case ')': case '}': case ']':
                            if (letters.empty() || validate[chr] != letters.top()) {
                                return false;
                            } // if (letters.empty() || validate[chr] != letters.top())
                            letters.pop();
                            break;
                        default:
                            throw std::runtime_error("unknown input character");
                    } // switch (chr)
                } // for (char chr : s)

                return letters.empty();
            } // isBalanced
        }
    }
}
