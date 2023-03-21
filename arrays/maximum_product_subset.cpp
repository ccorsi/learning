/**
 * @file maximum_product_subset.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=MaximumProductSubset
 * @version 0.1
 * @date 2023-03-20
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "maximum_product_subset.h"

#include <climits>

namespace valhalla {
    namespace arrays {
        namespace maximum_product_subset {
            /*

            Given an integer array, find the maximum product of its elements among all its subsets.

            Input : [-6, 4, -5, 8, -10, 0, 8]
            Output: 15360
            Explanation: The subset with the maximum product of its elements is [-6, 4, 8, -10, 8]

            Input : [4, -8, 0, 8]
            Output: 32
            Explanation: The subset with the maximum product of its elements is [4, 8]

            Input : []
            Output: 0

            */

            int Solution::findMaxProduct(std::vector<int> const & nums) {
                const int size = nums.size();
                int max = 0;

                if (size > 0) {
                    max = INT_MIN;

                    for(int idx = 0 ; idx < size ; idx++) {
                        checkMaxProduct(nums, idx, 1, max);
                    } // for
                } // if

                return max;
            } // findMaxProduct

            void Solution::checkMaxProduct(std::vector<int> const & nums, int at, int sum, int & max) {
                sum *= nums[at];

                if (sum > max) {
                    max = sum;
                } // if

                const int size = nums.size();

                for (int idx = at + 1 ; idx < size ; idx++) {
                    checkMaxProduct(nums, idx, sum, max);
                } // for
            } // checkMaxProduct
        }
    }
}
