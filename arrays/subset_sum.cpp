/**
 * @file subset_sum.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=SubsetSum
 * @version 0.1
 * @date 2023-03-08
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <cstddef>

#include "subset_sum.h"

/*

Given an integer array, return the total number of ways to calculate the specified target from
array elements using only the addition and subtraction operator. The use of any other operator
is forbidden.

Input: nums = [5, 3, -6, 2], target = 6
Output: 4
Explanation: There are 4 ways to calculate the target of 6 using only + and - operators:

(-)-6 = 6
(+) 5 (+) 3 (-) 2 = 6
(+) 5 (-) 3 (-) -6 (-) 2 = 6
(-) 5 (+) 3 (-) -6 (+) 2 = 6

Input: nums = [5, 3, -6, 2], target = 4
Output: 4
Explanation: There are 4 ways to calculate the target of 4 using only + and - operators:

(-)-6 (-) 2 = 4
(-) 5 (+) 3 (-)-6 = 4
(+) 5 (-) 3 (+) 2 = 4
(+) 5 (+) 3 (+)-6 (+) 2 = 4

*/

#include <iostream>

void valhalla::arrays::subset_sum::Solution::countWay(std::set<std::vector<int>> & processed, std::vector<int> & entries, std::vector<int> const & nums, int target, const int sum, int idx) {
    int size = nums.size();
    if (idx < size) {
        int total = sum + nums[idx];

        std::cout << "Checking entries [";
        for (int entry : entries)
            std::cout << " " << entry;
        std::cout << " " << nums[idx] << " ] = "
            << total << " against " << target << std::endl;

        if (total == target) {
            std::cout << "Found target:";
            for (int entry : entries)
                std::cout << " " << entry;
            std::cout << " " << nums[idx] << " = " << target << std::endl;
            if (processed.insert(entries).second) {
                std::cout << "Added target:";
                for (int entry : entries)
                    std::cout << " " << entry;
                std::cout << " " << nums[idx] << " = " << target << std::endl;
            }
        } // if

        for (int next = idx + 1 ; next < size ; next++) {
            entries.push_back(nums[idx]);
            countWay(processed, entries, nums, target, total, next);
            entries.pop_back();
        } // for
    } // if
}

void valhalla::arrays::subset_sum::Solution::processInput(std::set<std::vector<int>> & processed, std::vector<int> & nums, int target, int idx) {
    const int length = static_cast<int>(nums.size());

    std::cout << "Processing nums [";
    for (int num : nums)
        std::cout << " " << num;
    std::cout << " ] for idx = " << idx << std::endl;

    for (int start = 0 ; start < length ; start++) {
        std::vector<int> entries;
        countWay(processed, entries, nums, target, 0, start);
    }

    if ( idx < length ) {
        for (int cnt = 0 ; cnt < 2 ; cnt++) {
            nums[idx] *= -1;
            processInput(processed, nums, target, idx + 1);
        } // for
    } // if
}

int valhalla::arrays::subset_sum::Solution::countWays(std::vector<int> const & nums, int target) {
    std::set<std::vector<int>> processed;

    if ( ! nums.empty() ) {
        std::cout << "Input:";
        for(int num : nums)
            std::cout << " " << num;
        std::cout << ", target = " << target << std::endl;

        std::vector<int> inputs = nums;

        for (int cnt = 0 ; cnt < 2 ; cnt++) {
            inputs[0] *= -1;
            processInput(processed, inputs, target, 1);
        } // for
    } // if

    return processed.size();
}
