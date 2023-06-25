/**
 * @file anagram_substring.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=AnagramSubstring
 * @version 0.1
 * @date 2023-06-24
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "anagram_substring.h"

namespace valhalla {
    namespace strings {
        namespace anagram_substring {
/*

Given two strings, find all substrings of the first string that are anagrams of the second string and return the list of their indices.

Two words, X and Y, are anagrams if by rearranging the letters of X, we can get Y using all the original letters of X exactly once.

Input: X = "XYYZXZYZXXYZ", Y = "XYZ"
Output: [2, 4, 6, 9]

Explanation:

Anagram "YZX" present at index 2
Anagram "XZY" present at index 4
Anagram "YZX" present at index 6
Anagram "XYZ" present at index 9

Note: The solution should return the indices in ascending order.

*/

            std::vector<int> Solution::findAllAnagrams(std::string X, std::string Y) {
                std::vector<int> anagrams;



                return anagrams;
            } // findAllAnagrams
        }
    }
}
