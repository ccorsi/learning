/**
 * @file lexicographic_rank.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=LexicographicRank
 * @version 0.1
 * @date 2023-07-03
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "lexicographic_rank.h"

namespace valhalla {
    namespace strings {
        namespace lexicographic_rank {
            /*

            Given a string, calculate its rank among all its lexicographically sorted permutations.

            Input : "CBA"
            Output: 6
            Explanation: The rank of string "DCBA" in the lexicographically sorted permutations
                ["ABC", "ACB", "BAC", "BCA", "CAB", "CBA"] is 6.

            Input : "AABA"
            Output: 2
            Explanation: The rank of string "AABA" in the lexicographically sorted permutations
                ["AAAB", "AABA", "ABAA", "BAAA"] is 2.

            Input : "DCBA"
            Output: 24

            */

            long Solution::findLexicographicRank(std::string s) {
                long rank = -2;



                return rank;
            } // findLexicographicRank
        }
    }
}
