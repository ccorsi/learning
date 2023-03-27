/**
 * @file distinct_absolute_count.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=DistinctAbsoluteCount
 * @version 0.1
 * @date 2023-03-27
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <set>
#include <cmath>

#include "distinct_absolute_count.h"

namespace valhalla {
    namespace arrays {
        namespace distinct_absolute_count {
            /*

            Given an array of sorted integers that may contain several duplicate
            elements, count the total number of distinct absolute values in it.

            Input : [-1, -1, 0, 1, 1, 1]
            Output: 2
            Explanation: There are 2 distinct absolutes in the array [0, 1]

            Input : [-2, -1, 0, 1, 2, 3]
            Output: 4
            Explanation: There are 4 distinct absolutes in the array [0, 1, 2, 3]

            Input : [-1, -1, -1, -1]
            Output: 1
            Explanation: There is only 1 distinct absolute in the array [1]

            */

            int Solution::findDistinctCount(std::vector<int> const & nums) {
                std::set<int> distinct_counts;

                for (int num : nums) {
                    distinct_counts.insert(std::abs(num));
                } // for

                return distinct_counts.size();
            } // findDistinctCount
        }
    }
}
