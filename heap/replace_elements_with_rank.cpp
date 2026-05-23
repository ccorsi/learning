/**
 * @file replace_elements_with_rank.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=ReplaceElementsWithRank
 * @version 0.1
 * @date 2026-05-02
 *
 * @copyright Copyright (c) 2026 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <iostream>
#include <queue>

#include "replace_elements_with_rank.h"

namespace valhalla {

namespace heap {

namespace replace_elements_with_rank {

/*

Given an array of distinct integers, in-place replace each array element by
its corresponding rank in the array. The minimum array element has the
rank 1; the second minimum element has a rank of 2, and so on.

Input : [10, 8, 15, 12, 6, 20, 1]
Output: [4, 3, 6, 5, 2, 7, 1]

Input : [0, 1, -1]
Output: [2, 3, 1]

*/

void attempt_one(std::vector<int> & nums) {
    using size_type = std::vector<int>::size_type;

    auto cmp = [&nums](const size_type & lhs, const size_type & rhs) {
        return nums[lhs] > nums[rhs];
    };

    std::priority_queue<size_type, std::vector<size_type>, decltype(cmp)> heap(cmp);

    for (auto idx = 0 ; idx < nums.size() ; idx++) {
        heap.push(idx);
    } // for (auto idx = 0 ; idx < nums.size() ; idx++)

    int rank = 1;

    while (heap.empty() == false) {
        size_type idx = heap.top(); heap.pop();
        nums[idx] = rank++;
    } // while (heap.empty() == false)

} // void attempt_one(std::vector<int> & nums)

void Solution::transform(std::vector<int> & nums) {
    attempt_one(nums);
} // transform

} // namespace replace_elements_with_rank

} // namespace heap

} // namespace valhalla
