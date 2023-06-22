/**
 * @file sort_with_young_tableau.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=SortWithYoungTableau
 * @version 0.1
 * @date 2023-06-22
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "sort_with_young_tableau.h"

namespace valhalla {
    namespace matrices {
        namespace sort_with_young_tableau {
            /*

            Given an integer array, in-place sort it using Young tableau. You are given a utility
            class YoungTableau with the following public member functions:

            1. vector<vector<int>> construct(vector<int> &nums): Construct and return an `N × N`
                Young tableau from the list `nums`. Note that `N` is determined dynamically by
                taking ceil of the square root of `nums` length.

            2. int extractMin(vector<vector<int>> &tableau): Extract the next minimum element
                from the Young tableau `tableau`.

            */

            void Solution::sort(std::vector<int> & nums) {



            } // sort
        }
    }
}
