/**
 * @file balanced_parentheses.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=BalancedParentheses
 * @version 0.1
 * @date 2023-06-26
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "balanced_parentheses.h"

namespace valhalla {
    namespace strings {
        namespace balanced_parentheses {
            /*

            Given a positive number n, find all strings of length n containing balanced parentheses.

            Input : n = 4
            Output: {"(())", "()()"}

            Input : n = 6
            Output: {"((()))", "(()())", "(())()", "()(())", "()()()"}

            Input : n = 5
            Output: {}
            Explanation: Since n is odd, balanced parentheses cannot be formed.

            */

            std::unordered_set<std::string> Solution::findPalindromicPermutations(int n) {
                std::unordered_set<std::string> permutations;



                return permutations;
            } // findPalindromicPermutations
        }
    }
}
