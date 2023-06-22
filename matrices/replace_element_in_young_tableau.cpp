/**
 * @file replace_element_in_young_tableau.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=ReplaceElementInYoungTableau
 * @version 0.1
 * @date 2023-06-21
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "replace_element_in_young_tableau.h"

namespace valhalla {
    namespace matrices {
        namespace replace_element_in_young_tableau {
            /*

            Given an `N × N` Young tableau and two integers x and y, replace x by y in the Young tableau and in-place fix the Young tableau property.

            An `N × N` Young tableau is an `N × N` matrix such that the entries of each row are sorted from left to right and the entries of each column are sorted from top to bottom. Some entries of a Young tableau may be infinity, which indicates an empty entry.

            Input:

            tableau = [
                [10, 12, 15, 16],
                [11, 18, 20, 25],
                [22, 27, 30, 35],
                [34, 40, 44, 45]
            ]

            x = 20, y = 14		# replace 20 by 14

            Output:

            tableau = [
                [10, 12, 14, 15]
                [11, 16, 18, 25]
                [22, 27, 30, 35]
                [34, 40, 44, 45]
            ]

            OR, any other valid `N × N` Young tableau.

            Input:

            tableau = [
                [11, 12, 25],
                [20, 22, 34],
                [27, 30, inf]
            ]

            Here, inf = INT_MAX

            x = 20, y = 35		# replace 20 by 35

            Output:

            tableau = [
                [11, 12, 25],
                [22, 30, 34],
                [27, 35, inf]
            ]

            OR, any other valid `N × N` Young tableau.

            */

            void Solution::replaceInYoungTableau(std::vector<std::vector<int>> & tableau, int x, int y) {



            } // replaceInYoungTableau
        }
    }
}
