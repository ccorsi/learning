/**
 * @file k_closest_elements.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=KClosestElements
 * @version 0.1
 * @date 2023-02-21
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <iostream>

#include "k_closest_elements.h"

/*

Given a sorted integer array `nums` and two positive integers `k` and `target`, find the `k` closest elements to `target`
in the array. Here, `target` may or may not be present in the input array. The solution should return elements in the
same order as present in the input array.

Input : nums[] = [10, 12, 15, 17, 18, 20, 25], k = 4, target = 16
Output: [12, 15, 17, 18]


• If `target` is less than or equal to the first element in the input array, the solution should return the first `k` elements.

Input : nums[] = [2, 3, 4, 5, 6, 7], k = 3, target = 1
Output: [2, 3, 4]


• If `target` is more than or equal to the last element in the input array, the solution should return the last `k` elements.

Input : nums[] = [2, 3, 4, 5, 6, 7], k = 2, target = 8
Output: [6, 7]


• In case multiple sets of `k` closest elements exists, the solution should return the first occuring set.

Input : nums[] = [10, 12, 15, 17, 20, 25], k = 3, target = 16
Output: [12, 15, 17]
Explanation: There are two k-closest element sets present in the array i.e., [12, 15, 17] and [15, 17, 20]. The solution returns set [12, 15, 17] as it appears before set [15, 17, 20] in the array.

*/

std::vector<int> valhalla::arrays::k_closest_elements::Solution::kClosestElements(std::vector<int> const & nums, int k, int target) {
    std::vector<int> result;

    if (nums.empty()) return result;
    
    std::vector<int>::size_type start = 0, end = nums.size() - 1;
    const std::vector<int>::size_type size = nums.size();

    while (start < end && end < size) {
        int mid = (start + end) / 2;

        if (nums[mid] == target) {
            start = mid;
            break;
        } else if (nums[mid] > target) {
            end = mid - 1;
        } else {
            start = mid + 1;
        } // else
    } // while

    if (nums[start] > target && start > 0) start--;

    // std::cout << "input [";
    // for(int num : nums)
    //     std::cout << " " << num;
    // std::cout << " ]" << std::endl;
    // std::cout << "nums[" << start << "]: " << nums[start] << " target: " << target << " k: " << k << std::endl;

    // the start index will always be less than or equal to target
    std::vector<int>::size_type left = start, right = start + 1;

    while (k > 0 && left < size && right < size) {
        // std::cout << "nums[left]: " << nums[left] << " nums[right]: " << nums[right] << " target: " << target << std::endl;
        // std::cout << "left: " << left << " right: " << right << std::endl;
        if ((target - nums[left]) <= (nums[right] - target)) {
            left--;
        } else {
            right++;
        } // if
        k--;
    } // while

    // std::cout << "left: " << left << " right: " << right << std::endl;
    if (right == size) {
        left -= k;
        if (left > size) left = -1;
    } else if (left > size) {
        right += k;
        if (right > size) right = size;
    } // else

    while (++left < right) result.push_back(nums[left]);
    
    return result;
}
