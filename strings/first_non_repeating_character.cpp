/**
 * @file first_non_repeating_character.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=FirstNonRepeatingCharacter
 * @version 0.1
 * @date 2023-07-02
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "first_non_repeating_character.h"

#include <iostream>
#include <map>
#include <vector>

namespace valhalla {
    namespace strings {
        namespace first_non_repeating_character {
            /*

            Given a string, find the index of the first non-repeating character in it by doing only
            a single traversal of the string.

            Input : "ABCDBAGHC"
            Output: 3

            The solution should return -1 if the string has all characters repeating.

            Input : "AAA"
            Output: -1

            */

            int Solution::findFirstNonRepeating(std::string s) {
                int index = 0;
                std::map<char,int> counts;
                std::vector<std::pair<char,int>> count_refs;

                for(char chr : s) {
                    int count = ++counts[chr];
                    if (count == 1) {
                        count_refs.push_back(std::pair<char,int>(chr, index));
                    } // for
                    index++;
                } // for

                for (std::pair<char,int> count : count_refs) {
                    if (counts[count.first] == 1) return count.second;
                } // for

                return -1;
            } // findFirstNonRepeating
        }
    }
}
