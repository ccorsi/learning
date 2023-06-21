/**
 * @file construct_young_tableau.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=ConstructYoungTableau
 * @version 0.1
 * @date 2023-06-21
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "construct_young_tableau.h"

namespace valhalla {
    namespace matrices {
        namespace construct_young_tableau {
            /*

            Given an integer array containing n elements, construct an `N × N` Young tableau from it
            where N is ceil of square root of n. i.e., N = ceil(sqrt(n)).

            An `N × N` Young tableau is an `N × N` matrix such that the entries of each row are sorted
            from left to right and the entries of each column are sorted from top to bottom. Some
            entries of a Young tableau may be infinity, which indicates an empty entry.

            Input: [12, 10, 20, 22, 25, 30, 34, 11, 44, 27, 16, 40, 35, 15, 18, 45]

            Output: [
                [10, 11, 12, 15],
                [16, 18, 20, 22],
                [25, 27, 30, 34],
                [35, 40, 44, 45]
            ]

            OR [
                [10, 12, 15, 16],
                [11, 18, 20, 25],
                [22, 27, 30, 35],
                [34, 40, 44, 45]
            ]

            OR, any other valid `N × N` Young tableau.


            Input: [12, 10, 20, 22, 25, 30, 34, 11, 27, 16]

            Output: [
                [10,  11,  12,  16],
                [20,  22,  25,  27],
                [30,  34,  inf, inf],
                [inf, inf, inf, inf]
            ]

            Here, inf = INT_MAX = 2147483647

            OR, any other valid `N × N` Young tableau.

            */

            std::vector<std::vector<int>> Solution::constructYoungTableau(std::vector<int> const & keys) {
                std::vector<std::vector<int>> tableau;


                return tableau;
            } // constructYoungTableau
        }
    }
}
