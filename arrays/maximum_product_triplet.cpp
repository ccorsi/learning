/**
 * @file maximum_product_triplet.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=MaximumProductTriplet
 * @version 0.1
 * @date 2023-03-26
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <climits>

#include "maximum_product_triplet.h"

namespace valhalla {
    namespace arrays {
        namespace maximum_product_triplet {
            /*

            Given an integer array, find a triplet having the maximum product.

            Input : [-4, 1, -8, 9, 6]
            Output: [-4, -8, 9]

            If the input contains several triplets with maximum product, the solution
            can return any one of them.

            Input : [5, 2, -10, 4, 5, 1, -2]
            Output: [5, 4, 5] or [5, -10, -2]

            Note: The solution can return the triplet in any order, not necessarily
            as they appear in the array.

            */

            std::vector<int> Solution::findTriplet(std::vector<int> const & nums) {
                std::vector<int> triplet;

                if (nums.size() > 2) {
                    const int size = nums.size();
                    int max = INT_MIN;
                    for (int i = 0 ; i < size ; i++) {
                        for (int j = i + 1 ; j < size ; j++) {
                            for (int k = j + 1 ; k < size ; k++) {
                                int product = nums[i] * nums[j] * nums[k];
                                if (product >= max) {
                                    max = product;
                                    triplet = { nums[i], nums[j], nums[k] };
                                } // if
                            } // for k
                        } // for j
                    } // for i
                } // if

                return triplet;
            } // findTriplet
        }
    }
}
