/**
 * @file closest_pair.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=ClosestPair
 * @version 0.1
 * @date 2023-03-23
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <iostream>
#include <set>
#include <cmath>

#include "closest_pair.h"

namespace valhalla {
    namespace arrays {
        namespace closest_pair {
            /*

            Given two sorted integer arrays, `X[]` and `Y[]`, and an integer `k`,
            find a pair `(x, y)` whose sum is closest to `k`, where the pair consists
            of elements from each array. The solution should return the pair `(x, y)` `x`
            is taken from the first array, and `y` from the second array.

            Input:

            X[] = [1, 8, 10, 12]
            Y[] = [2, 4, 9, 15]
            k = 11

            Output: (1, 9)


            • For some inputs, the multiple pairs are feasible. For such cases, the
            solution can return any matching pair. For example,

            Input:

            X[] = [2, 4, 6, 8, 10]
            Y[] = [1, 3, 5, 7, 9]
            k = 4

            Output: (2, 1) or (2, 3)


            • If no pair exists, the solution should return the pair (-1, -1).

            Input:

            X[] = [1, 2, 3]
            Y[] = []
            k = 4

            Output: (-1, -1)

            */

            std::pair<int,int> Solution::findClosestPair(std::vector<int> const & X, std::vector<int> const & Y, int k) {
                std::pair<int,int> closest_pair(-1,-1);
                // std::cout << "[";
                // for (int value : X)
                //     std::cout << " " << value;
                // std::cout << " ]" << std::endl;
                // std::cout << "[";
                // for (int value : Y)
                //     std::cout << " " << value;
                // std::cout << " ]" << std::endl;
                // std::cout << k << std::endl;

                if ( ! X.empty() && ! Y.empty()) {
                    int closest = std::abs( k - (X[0] + Y[0]) );
                    closest_pair.first = X[0];
                    closest_pair.second = Y[0];

                    for (int x_value : X) {
                        for (int y_value : Y) {
                            int diff = std::abs(k - (x_value + y_value));

                            if (diff < closest) {
                                closest_pair.first = x_value;
                                closest_pair.second = y_value;
                                closest = diff;
                                continue;
                            } // if

                            if ((x_value + y_value) >= k) {
                                break;
                            } // ifs
                        } // for
                    } // for
                } // if

                // std::cout << "(" << closest_pair.first << "," << closest_pair.second << ")" << std::endl;
                return closest_pair;
            } // findClosestPair
        }
    }
}
