/**
 * @file remove_adjacent_duplicates.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=RemoveAdjacentDuplicates
 * @version 0.1
 * @date 2023-06-29
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "remove_adjacent_duplicates.h"

namespace valhalla {
    namespace strings {
        namespace remove_adjacent_duplicates {
            /*

            Given a string, remove adjacent duplicates characters from it. In other words,
            remove all consecutive same characters except one.

            Input : "AABBBCDDD"
            Output: "ABCD"

            */

            void Solution::removeAdjacentDuplicates(std::string & s) {

                for (std::string::iterator itr = s.begin() ; itr != s.end() ; itr++) {
                    int count = 0;
                    while ( (itr + count + 1) != s.end() && *itr == *(itr + count + 1)) count++;

                    if (count > 0) {
                        itr = s.erase(itr, (itr + count));
                    }
                }


            } // removeAdjacentDuplicates
        }
    }
}
