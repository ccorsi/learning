/**
 * @file maximum_product_subarray.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=MaximumProductSubarray
 * @version 0.1
 * @date 2023-03-14
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "maximum_product_subarray.h"

/*

Given an integer array, find the contiguous subarray that has the maximum product of its elements.
The solution should return the maximum product of elements among all possible subarrays.

Input : [-6, 4, -5, 8, -10, 0, 8]
Output: 1600
Explanation: The maximum product subarray is [4, -5, 8, -10] which has product 1600.

Input : [40, 0, -20, -10]
Output: 200
Explanation: The maximum product subarray is [-20, -10] which has product 200.

Input : [10]
Output: 10

Input : []
Output: 0

*/

void valhalla::arrays::maximum_product_subarray::Solution::checkMaxProduct(std::vector<int> const & nums, int & max_prod, int product, int next) {
    if (product > max_prod)
        max_prod = product;

    const int size = nums.size();

    for ( ; next < size ; next++) {
        product *= nums[next];
        if (product > max_prod) {
            max_prod = product;
        } // if
    } // for
}

int valhalla::arrays::maximum_product_subarray::Solution::findMaxProduct(std::vector<int> const & nums) {
    int max_prod = 0;

    const int size = nums.size();

    if (size > 0) {
        max_prod = nums[0];

        for (int idx = 0 ; idx < size ; idx++) {
            checkMaxProduct(nums, max_prod, nums[idx], idx + 1);
        } // for
    } // if

    return max_prod;
}
