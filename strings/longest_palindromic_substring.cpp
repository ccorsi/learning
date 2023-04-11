/**
 * @file longest_palindromic_substring.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=LongestPalindromicSubstring
 * @version 0.2
 * @date 2023-02-13
 * 
 * @copyright Copyright (c) 2023 Claudio Corsi
 * 
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

/*

Given a string, find the maximum length contiguous substring of it that is also a palindrome.

Input: "bananas"
Output: "anana"

Input: "abdcbcdbdcbbc"
Output: "bdcbcdb"

The longest palindromic substring is not guaranteed to be unique. If multiple longest palindromic
substring exists, the solution should return the one which appear first in the string.

Input: "abracadabra"
Output: "aca"
Explanation: There is no palindromic substring in a string "abracadabra" with a length greater
than 3. There are two palindromic substrings with length 3, namely, "aca" and "ada". The solution
returns "aca" as it appears before "ada" in the string.

Input: "dcabc"
Output: "d"

*/

#include <iostream>
#include <list>
#include <set>

#include "longest_palindromic_substring.h"

std::string valhalla::strings::longest_palindromic_substring::Solution::longestPalindromicSubstring(std::string s) {
    // std::cout << "Input: " << s << std::endl;
    std::string result;

    if (s.empty()) return result;

    const int size = s.length();
    result = s[0];

    for (int len = 2 ; len <= size ; len++) {
        const int end = size - len + 1;
        bool found = false;
        for (int idx = 0 ; found == false && idx < end ; idx++) {
            int front = idx, back = idx + len - 1;
            while (front < back && s[front] == s[back]) {
                front++; back--;
            } // while
            if (front >= back) {
                found = true;
                result = s.substr(idx, len);
            } // if
        } // for
    } // for

    /*
        Version 1:
        The following solution does correctly find different palindromic substrings within the passed string but
        it doesn't return the *first* longest palindromic substring.  It thus doesn't properly implement the required
        solution to this question
    std::list<std::string::size_type> next;
    std::set<std::string::size_type> checked;

    const std::string::size_type size = s.length();
    const std::string::size_type end = size - 1;

    next.push_back(size / 2);

    std::string::size_type total = size + size;
    std::string::size_type cnt = 0;

    while (! next.empty()) {
        // get the next pivot entry
        std::string::size_type pivot = next.front();
        // determine if the next pivot entry can produce a larger palindrome that the current largest
        std::string::size_type width = std::min(pivot, end - pivot);
        // std::cout << "width: " << width << ", pivot: " << pivot << ", result: " << result << std::endl;
        if (width + width + 1 < result.length()) {
            // unable to produce a longer palindrome
            break;
        }
        // pop the current pivot from the list
        next.pop_front();

        checked.insert(pivot);

        // check for even length palindrome
        std::string::size_type left = pivot, right = pivot + 1;
        // std::cout << "Start even left: " << left << ", right: " << right << ", pivot: " << pivot << std::endl;
        while (left >= 0 && right < size && s[left] == s[right]) {
            // std::cout << "Even left: " << left << ", right: " << right << std::endl;
            if (right - left + 1 > result.length()) {
                // update the resulting string
                result = s.substr(left, right - left + 1);
            } // if
            // check boundaries
            if (right == end) break;
            if (left == 0) break;
            // update indexes
            right++; left--;
        } // while

        // check for odd length palindrome
        left = right = pivot;
        // std::cout << "Start odd left: " << left << ", right: " << right << ", pivot: " << pivot << std::endl;
        while (left >= 0 && right < size && s[left] == s[right]) {
            // std::cout << "Odd left: " << left << ", right: " << right << std::endl;
            if (right - left + 1 > result.length()) {
                // update the resulting string
                result = s.substr(left, right - left + 1);
            } // if
            // check boundaries
            if (right == end) break;
            if (left == 0) break;
            // update indexes
            right++; left--;
        } // while

        // add the next left side pivot entry
        if (pivot > 0) {
            if (checked.find(pivot - 1) == checked.end())
                next.push_back(pivot - 1);
        } // if
        // add the next right side pivot entry
        if (pivot < end) {
            if (checked.find(pivot + 1) == checked.end())
                next.push_back(pivot + 1);
        } // if

        if (++cnt > total) {
            std::cout << "Breaking out of while loop" << std::endl;
            std::cout << "next [";
            for (std::string::size_type v : next)
                std::cout << " " << v;
            std::cout << " ]" << std::endl; 
            break;
        } // if
    } // while
    */

    return result;
}
