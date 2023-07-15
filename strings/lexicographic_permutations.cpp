/**
 * @file lexicographic_permutations.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=LexicographicPermutations
 * @version 0.1
 * @date 2023-07-02
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "lexicographic_permutations.h"

namespace valhalla {
    namespace strings {
        namespace lexicographic_permutations {
            /*

            Given a string, find all distinct lexicographic permutations of it where
            the repetition of characters is allowed.

            Input : "AAB"
            Output: {"AAA", "AAB", "ABA", "ABB", "BAA", "BAB", "BBA", "BBB"}

            */

            std::unordered_set<std::string> Solution::findLexicographicPermutations(std::string s) {
                std::unordered_set<std::string> permutations;

                for (char chr : s) {
                    std::string current;
                    current += chr;
                    checkLexigraphicPermutations(s, current, permutations);
                }

                return permutations;
            } // findLexicographicPermutations

            void Solution::checkLexigraphicPermutations(std::string & s, std::string current, std::unordered_set<std::string>  & permutations) {
                if (current.length() == s.length()) {
                    permutations.insert(current);
                    return;
                }

                for (char chr : s) {
                    std::string next = current + chr;
                    checkLexigraphicPermutations(s, next, permutations);
                }

            } // checkLexigraphicPermutations
        }
    }
}
