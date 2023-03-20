/**
 * @file longest_continuous_sequence.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=LongestContinuousSequence
 * @version 0.1
 * @date 2023-03-19
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <iostream>
#include <cmath>

#include "longest_continuous_sequence.h"

namespace valhalla {
    namespace arrays {
        namespace longest_continuous_sequence {
            /*

            Given two binary arrays, `X` and `Y`, find the length of the longest continuous
            sequence that starts and ends at the same index in both arrays and have the
            same sum. In other words, find `max(j-i+1)` for every `j >= i`, where the sum
            of subarray `X[i, j]` is equal to the sum of subarray `Y[i, j]`.

            Input:

            X[]: [0, 0, 1, 1, 1, 1]
            Y[]: [0, 1, 1, 0, 1, 0]

            Output: 5
            Explanation: The length of the longest continuous sequence with the same sum is
            5 as

            X[0, 4]: [0, 0, 1, 1, 1]	(sum = 3)
            Y[0, 4]: [0, 1, 1, 0, 1]	(sum = 3)

            */

            int Solution::findMaxSubarrayLength(std::vector<int> const & X, std::vector<int> const & Y) {
                std::cout << "X: [";
                for (int value : X)
                    std::cout << " " << value;
                std::cout << " ]" << std::endl;
                std::cout << "Y: [";
                for (int value : Y)
                    std::cout << " " << value;
                std::cout << " ]" << std::endl;
                const int size = std::min(X.size(), Y.size());
                int longest = 0;

                for (int start = 0 ; start < size ; start++) {
                    int sum_x = 0, sum_y = 0;
                    for (int idx = start ; idx < size ; idx++) {
                        sum_x += X[idx];
                        sum_y += Y[idx];
                        if (sum_x == sum_y && idx - start + 1 > longest) {
                            longest = idx - start + 1;
                        } // if
                    } // for
                } // for

                return longest;
            } // findMaxSubarrayLength
        }
    }
}
