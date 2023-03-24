/**
 * @file minimum_absolute_difference.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=MinimumAbsoluteDifference
 * @version 0.1
 * @date 2023-03-22
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */


#include "minimum_absolute_difference.h"

#include <cmath>

namespace valhalla {
    namespace arrays {
        namespace minimum_absolute_difference {
            /*

            Given an integer array `nums` and two integers `x` and `y` present in it, find
            the minimum absolute difference between indices of `x` and `y` in a single
            traversal of the array.

            Input : nums[] = [1, 3, 5, 4, 8, 2, 4, 3, 6, 5], x = 3, y = 2
            Output: 2
            Explanation: Element 3 is present at index 1 and 7, and element 2 is present
            at index 5. Their minimum absolute difference is min(abs(1-5), abs(7-5)) = 2

            Input : nums[] = [1, 3, 5, 4, 8, 2, 4, 3, 6, 5], x = 2, y = 5
            Output: 3
            Explanation: Element 2 is present at index 5, and element 5 is present at index
            2 and 9. Their minimum absolute difference is min(abs(5-2), abs(5-9)) = 3

            Input : nums[] = [], x = 0, y = 1
            Output: 0

            */

            int Solution::findDifference(std::vector<int> const & nums, int x, int y) {
                int difference = 0;
                int idx = 0;
                std::vector<int> X,Y;

                for (int num : nums) {
                    if (num == x) {
                        X.push_back(idx);
                    } // if
                    if (num == y) {
                        Y.push_back(idx);
                    } // if
                    if (X.size() + Y.size() >= 3 && X.size() > 0 && Y.size() > 0) {
                        int x1, x2, x3;
                        if (X.size() > Y.size()) {
                            x1 = X.front();
                            x2 = X.back();
                            x3 = Y.front();
                        } else {
                            x1 = Y.front();
                            x2 = Y.back();
                            x3 = X.front();
                        } // else
                        difference = std::min(std::abs(x3 - x1), std::abs(x3 - x2));
                        break;
                    } // if
                    idx++;
                } // for

                if (X.size() == 1 && Y.size() == 1) {
                    difference = std::abs(X[0] - Y[0]);
                } // if

                return difference;
            } // findDifference
        }
    }
}
