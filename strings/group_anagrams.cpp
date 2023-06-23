/**
 * @file group_anagrams.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=GroupAnagrams
 * @version 0.1
 * @date 2023-06-23
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "group_anagrams.h"

namespace valhalla {
    namespace strings {
        namespace group_anagrams {
            /*

            Given a list of words, efficiently group all anagrams. The two strings, X and Y,
            are anagrams if by rearranging X's letters, we can get Y using all the original
            letters of X exactly once.

            Input : ["CARS", "REPAID", "DUES", "NOSE", "SIGNED", "LANE", "PAIRED", "ARCS",
                     "GRAB", "USED", "ONES", "BRAG", "SUED", "LEAN", "SCAR", "DESIGN"]

            Output:

            {
                ["CARS", "ARCS", "SCAR"],
                ["REPAID", "PAIRED"],
                ["SIGNED", "DESIGN"],
                ["LANE", "LEAN"],
                ["GRAB", "BRAG"],
                ["NOSE", "ONES"],
                ["DUES", "USED", "SUED"]
            }


            Input : ["CARS", "LANE", "ONES"]
            Output: {}

            The solution should return a set containing all the anagrams grouped together,
            irrespective of the order.

            */

            std::set<std::set<std::string>> Solution::groupAnagrams(std::vector<std::string> const & words) {
                std::set<std::set<std::string>> anagrams;



                return anagrams;
            } // groupAnagrams
        }
    }
}
