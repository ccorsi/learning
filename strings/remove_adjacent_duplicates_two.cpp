/**
 * @file remove_adjacent_duplicates_two.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=RemoveAdjacentDuplicatesII
 * @version 0.1
 * @date 2023-06-29
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "remove_adjacent_duplicates_two.h"

namespace valhalla {
    namespace strings {
        namespace remove_adjacent_duplicates_two {
            /*

            Given a string, remove all adjacent duplicates from it. The solution should
            continue removing adjacent duplicates from the string till no duplicate is
            present in the result.

            Input : "DBAABDAB"
            Output: "AB"
            Explanation: "DBAABDAB" —> "DBBDAB" —> "DDAB" —> "AB"

            Input : "ABDAADBDAABB"
            Output: "AD"
            Explanation: "ABDAADBDAABB" —> "ABDDBD" —> "ABBD" —> "AD"

            Input : "ABADB"
            Output: "ABADB"

            */

            std::string Solution::removeAdjacentDuplicates(std::string s) {
                bool reduced = true;

                while (reduced) {
                    reduced = false;
                    for(std::string::iterator itr = s.begin(); itr != s.end() ; ) {
                        int count = 0;
                        while ( (itr + count + 1) != s.end() && *itr == *(itr + count + 1)) count++;
                        if ( count > 0) {
                            reduced = true;
                            itr = s.erase(itr, (itr + count + 1));
                            continue;
                        } // if
                        itr++;
                    } // for
                } // while

                return s;
            } // removeAdjacentDuplicates
        }
    }
}
