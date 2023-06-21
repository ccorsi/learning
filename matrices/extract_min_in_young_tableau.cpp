/**
 * @file extract_min_in_young_tableau.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=ExtractMinInYoungTableau
 * @version 0.1
 * @date 2023-06-21
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "extract_min_in_young_tableau.h"

namespace valhalla {
    namespace matrices {
        namespace extract_min_in_young_tableau {
            /*

            Given an `N × N` Young tableau, extract and return the minimum element from it and
            in-place fix the Young tableau.

            An `N × N` Young tableau is an `N × N` matrix such that the entries of each row
            are sorted from left to right and the entries of each column are sorted from top
            to bottom. Some entries of a Young tableau may be infinity, which indicates an
            empty entry.

            Input:

            tableau = [
                [10, 11, 12, 15],
                [16, 18, 20, 22],
                [25, 27, 30, 34],
                [35, 40, 44, 45]
            ]

            Output: 10

            tableau = [
                [11, 12, 15, 22],
                [16, 18, 20, 34],
                [25, 27, 30, 45],
                [35, 40, 44, inf]
            ]

            OR, any other valid `N × N` Young tableau.

            Here, inf = INT_MAX

            Input:

            tableau = [
                [11, 12, 25],
                [20, 22, 34],
                [27, 30, inf]
            ]

            Output: 11

            tableau = [
                [12, 22, 25],
                [20, 30, 34],
                [27, inf, inf]
            ]

            OR, any other valid `N × N` Young tableau.

            */

            int Solution::extractMin(std::vector<std::vector<int>> & tableau) {
                int min = -1;



                return min;
            } // extractMin
        }
    }
}
