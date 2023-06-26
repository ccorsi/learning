/**
 * @file next_permutations.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=NextPermutations
 * @version 0.1
 * @date 2023-06-26
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "next_permutations.h"

namespace valhalla {
    namespace strings {
        namespace next_permutations {
            /*

            Given a string, find all lexicographically next permutations of it.

            The words are arranged in the same order in the lexicographic order as they
            are presumed to appear in a dictionary. For example, the lexicographically
            next permutation of string "ABCD" is "ABDC", for string "ABDC" is "ACBD",
            and for string "ACBD" is "ACDB".

            Input : "ABCD"
            Output: ["ABCD", "ABDC", "ACBD", "ACDB", "ADBC", "ADCB", "BACD", "BADC", "BCAD",
                     "BCDA", "BDAC", "BDCA", "CABD", "CADB", "CBAD", "CBDA", "CDAB", "CDBA",
                     "DABC", "DACB", "DBAC", "DBCA", "DCAB", "DCBA"]

            Input : "CABD"
            Output: ["CABD", "CADB", "CBAD", "CBDA", "CDAB", "CDBA", "DABC", "DACB", "DBAC",
                     "DBCA", "DCAB", "DCBA"]

            Input : "ABA"
            Output: ["ABA", "BAA"]

            Input : "AAA"
            Output: ["AAA"]

            Note that the solution should not print duplicate permutations.

            */

            std::vector<std::string> Solution::findPermutations(std::string s) {
                std::vector<std::string> permutations;



                return permutations;
            } // findPermutations
        }
    }
}
