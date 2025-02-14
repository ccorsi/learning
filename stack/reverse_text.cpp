/**
 * @file reverse_text.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=ReverseText
 * @version 0.1
 * @date 2025-02-07
 *
 * @copyright Copyright (c) 2025 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "reverse_text.h"

#include <list>

namespace valhalla {

namespace stack {

namespace reverse_text {

/*

Given a line of text, reverse the text without reversing the individual words.

Input : "Technical Interview Preparation"
Output: "Preparation Interview Technical"

*/

void solution_two(std::string& s) {
    if (s.empty()) return;

    // Write your code here...
    std::list<std::string> words;

    std::size_t start = 0, end = s.size();

    while (start < end) {
        while (start < end && s[start] == ' ') start++;

        if (start < end) {
            std::string word;
            while (start < end && s[start] != ' ') word += s[start++];
            words.push_back(word);
        }
    }

    auto itr = words.rbegin();

    if (itr != words.rend()) {
        s = *itr;
        while (++itr != words.rend()) {
            s += ' ';
            s += *itr;
        }
    }
}

void solution_one(std::string& s) {
    if (s.empty()) return;

    // Write your code here...
    std::list<std::string> words;

    std::size_t start = 0, end = s.size();

    while (start < end) {
        while (start < end && s[start] == ' ') start++;

        if (start < end) {
            std::string word;
            while (start < end && s[start] != ' ') word += s[start++];
            words.push_back(word);
        }
    }

    s = "";
    while ( words.size() > 1) {
        s += words.back();
        s += ' ';
        words.pop_back();
    }

    if (words.empty() == false) s += words.back();
}

void Solution::reverseText(std::string & s) {
    solution_two(s);
} // reverseText

} // namespace reverse_text

} // namespace stack

} // namespace valhalla

