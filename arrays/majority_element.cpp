/**
 * @file majority_element.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a implementation for the solution to the problem https://www.techiedelight.com/?problem=MajorityElement
 * @version 0.1
 * @date 2023-02-04
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <map>

#include "majority_element.h"

/*

Given an integer array of size `n`, return the element which appears more than `n/2` times. Assume that the input always contain the majority element.

Input : [2, 8, 7, 2, 2, 5, 2, 3, 1, 2, 2]
Output: 2

Input : [1, 3, 1, 1]
Output: 1

*/
int valhalla::arrays::majority_element::Solution::findMajorityElement(std::vector<int> &nums) {
    int max = nums[0];
    int cnt = 1;
    std::map<int,int> counts;
    counts[max]++;

    for(size_t idx = 1 ; idx < nums.size() ; idx++) {
        int value = nums[idx];
        counts[value]++;
        if (counts[value] > cnt) {
            cnt = counts[value];
            max = value;
        }
    }

    return max;
}
