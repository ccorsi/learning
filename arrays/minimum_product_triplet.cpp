/**
 * @file minimum_product_triplet.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=MinimumProductTriplet
 * @version 0.1
 * @date 2023-03-27
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <climits>

#include "minimum_product_triplet.h"

namespace valhalla {
    namespace arrays {
        namespace minimum_product_triplet {
            /*

            Given an integer array, find the minimum product among all combinations of triplets in the array.

            Input : [4, -1, 3, 5, 9]
            Output: -45
            Explanation: The minimum product triplet is (-1, 5, 9)

            Input : [1, 4, 10, -2, 4]
            Output: -80
            Explanation: The minimum product triplet is (10, 4, -2)

            Input : [3, 4, 1, 2, 5]
            Output: 6
            Explanation: The minimum product triplet is (3, 1, 2)

            Input : [1, 2]
            Output: 0
            Explanation: Invalid input

            */

            int Solution::findMin(std::vector<int> & nums) {
                int min = 0;
                const int size = nums.size();

                if (size > 2) {
                    min = INT_MAX;
                    for (int first = 0 ; first < size ; first++) {
                        for (int second = first + 1 ; second < size ; second++) {
                            for (int third = second + 1 ; third < size ; third++) {
                                int product = nums[first] * nums[second] * nums[third];
                                if (product < min) {
                                    min = product;
                                } // if
                            } // for third
                        } // for second
                    } // for first
                } // if

                return min;
            } // findMin
        }
    }
}
