/**
 * @file rotated_palindrome.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=RotatedPalindrome
 * @version 0.1
 * @date 2023-01-02
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "rotated_palindrome.h"

/*

Given a string, check if it is a rotated palindrome or not.

Input: "CBAABCD"
Output: true
Explanation: "CBAABCD" is a rotation of the palindrome "ABCDCBA"

Input: "BAABCC"
Output: true
Explanation: "BAABCC" is a rotation of the palindrome "ABCCBA"

Input: "DCABC"
Output: false

*/

#include <map>
#include <iostream>

bool valhalla::strings::rotated_palindrome::Solution::exists(std::string& str) {
    if (str.size() < 2) {
        return true;
    }

    std::cout << "Checking for rotated palindrome for string: " << str << std::endl;
    std::string::size_type left, right, size = str.length();
    // const std::string::size_type test = size / 2 + ( size % 2 );
    const std::string::size_type oneless = size - 1;
    const std::string::size_type shift = ( ( size % 2 ) == 0 ) ? 0 : oneless;
    
    for(std::string::size_type idx = 0 ; idx < size ; idx++) {
        std::cout << "Starting at index: " << idx << std::endl;
        left = ( idx + shift ) % size;
        right = ( idx + 1 ) % size;

        std::string::size_type cnt = 0;

        std::cout << "Start: [left.right]: [" << left << "," << right << "] [str[left],str[right]]: [" << str[left] << "," << str[right] << "]" << std::endl;
        while (cnt < size && str[left] == str[right]) {
            std::cout << "[left.right]: [" << left << "," << right << "] [str[left],str[right]]: [" << str[left] << "," << str[right] << "]" << std::endl;
            left = ( left + oneless ) % size;
            right = ( right + 1 ) % size;
            cnt++;
        }

        if (cnt == size) {
            std::cout << "Found Rotated Palindrome centered at " << idx << std::endl;
            // we found a rotated palindrome
            return true;
        }

        std::cout << "Not a Rotated Palindrome centered at " << idx <<  std::endl;
    }

    std::cout << "The string " << str << " does not contained a rotated palindrome" << std::endl;
    return false;
}
