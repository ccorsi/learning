/**
 * @file minimum_range_two.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=MinimumRangeII
 * @version 0.1
 * @date 2023-04-01
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */


#include "minimum_range_two.h"

namespace valhalla {
    namespace arrays {
        namespace minimum_range_two {
            /*

            Given M sorted lists of variable length, efficiently compute the smallest
            range, including at least one element from each list.

            Input:

            mat = [
                [3, 6, 8, 10, 15],
                [1, 5, 12],
                [4, 8, 15, 16],
                [2, 6],
            ]

            Output: (4, 6)

            Input:

            mat = [
                [2, 3, 4, 8, 10, 15],
                [1, 5, 12],
                [7, 8, 15, 16],
                [3, 6],
            ]

            Output: (4, 7)

            If minimum range doesn't exist, the solution should return the pair (-1, -1).

            Input : [[], [], []]
            Output: (-1, -1)

            */

            std::pair<int,int> Solution::findMinimumRange(std::vector<std::vector<int>> const & lists) {
                std::pair<int,int> minRange(-1, -1);

                if ( ! lists.empty() ) {
                    const int size = lists.size();
                    int idx = 0;
                    int min = -1, max = -1;

                    while (idx < size && lists[idx].empty()) idx++;

                    if (idx < size) {
                        min = lists[idx].front();
                        max = lists[idx].back();

                        for ( ; idx < size ; idx++) {
                            if (lists[idx].empty()) {
                                minRange.first  = -1;
                                minRange.second = -1;
                                return minRange;
                            } // if

                            int value = lists[idx].front();
                            if (min < value) {
                                min = value;
                            } // if
                            value = lists[idx].back();
                            if (max > value) {
                                max = value;
                            } // if
                        } // for

                        if (min < max) {
                            minRange.first = min;
                            minRange.second = max;
                        } // if
                    } // if
                } // if

                return minRange;
            } // findMinimumRange
        }
    }
}
