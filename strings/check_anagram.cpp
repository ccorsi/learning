/**
 * @file check_anagram.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution for the problem https://www.techiedelight.com/?problem=CheckAnagram
 * @version 0.1
 * @date 2023-02-13
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <map>

#include "check_anagram.h"

/*

Given two strings, determine whether they are anagrams.

Any word that exactly reproduces the letters in another order is an anagram. In other words, X and Y are anagrams if by rearranging the letters of X, we can get Y using all the original letters of X exactly once.

Input: X = "silent", Y = "listen"
Output: true

Input: X = "incest", Y = "insect"
Output: true

*/

bool valhalla::strings::check_anagram::Solution::isAnagram(std::string X, std::string Y) {
    if (X.length() != Y.length()) return false;
    
    std::map<char,int> x_count, y_count;
    
    for (char c : X) x_count[c]++;
        
    for (char c : Y) y_count[c]++;
        
    return x_count == y_count;
}
