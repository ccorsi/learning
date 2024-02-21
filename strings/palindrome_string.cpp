/**
 * @file palindrome_string.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=PalindromeString
 * @version 0.1
 * @date 2023-06-28
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "palindrome_string.h"

namespace valhalla {
    namespace strings {
        namespace palindrome_string {
            /*

            Given a string, check if it is a palindrome. A palindromic string is a string that
            remains the same with its characters reversed.

            Input : "ABCBA"
            Output: true

            Input : "ABCA"
            Output: false

            */

            bool Solution::isPalindrome(std::string s) {
                if (s.empty()) return true;

                std::string::size_type left = 0, right = s.size() - 1;

                while (left < right) {
                    if (s[left] != s[right]) {
                        return false;
                    }
                    left++; right--;
                } // while

                return true;
            } // isPalindrome
        }
    }
}