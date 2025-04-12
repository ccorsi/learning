/**
 * @file odd_occurring_element_four.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=OddOccurringElementIV
 * @version 0.1
 * @date 2025-04-11
 *
 * @copyright Copyright (c) 2025 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "odd_occurring_element_four.h"

namespace valhalla {

namespace bit_manipulation {

namespace odd_occurring_element_four {

/*

Given an integer array where every element appears an even number of times,
except one element which appears an odd number of times. If the identical
elements appear in pairs in the array and there cannot be more than two
consecutive occurrences of an element, find the odd occurring element in
logarithmic time and constant space.

Input: [2, 2, 3, 3, 2, 2, 4, 4, 3, 1, 1]
Output: 3

Assume valid input. For instance, both arrays [1, 2, 1] and [1, 1, 2, 2, 2, 3, 3]
are invalid. The first one doesn't have identical elements appear in pairs, and
the second one contains three consecutive instances of an element.

*/

/**
 * @brief The following solution doesn't assume that only pair of identical values
 *      will appear together.  Which this is different from the definition of the
 *      problem that we are trying to solve.  The difference is this solution assumes
 *      the you can have any even number of values next to each other.  While this
 *      solution works it will perform unnecessary checks when the pair is located
 *      on the first conditional check.  Yet these extra checks aren't going to slow
 *      the solution down in a perceptable way compared to the update solution below.
 *
 * @param nums The array of numbers containing pairs and a single odd value
 * @return int The odd value in the above array
 */
int solution_one(const std::vector<int> &nums) {
    int start = 0, end = static_cast<int>(nums.size()) - 1, mid = (start + end) / 2;
    const int size = static_cast<int>(nums.size());

    while (start < end) {
        int count = 1;
        int idx = mid + 1;
        int last = mid;
        while (idx < size && nums[mid] == nums[idx]) {
            count++;
            last = idx++;
        } // while (idx < size && nums[mid] == nums[idx])

        idx = mid - 1;
        while (idx > -1 && nums[mid] == nums[idx--]) {
            count++;
        } // while (idx > -1    && nums[mid] == nums[idx--])

        if (count & 0x1)
            return nums[mid];

        if (last % 2 == 1) {
            // The odd number of entries are located in the upper side
            start = mid + 1;
        } else {
            // The odd number of entries are located in the lower side
            end = mid - 1;
        } // if (last % 2 == 0)

        mid = (start + end) / 2;
    } // while (start < end)

    return (start == 0 || end == 0) ? nums.front() : nums.back();
}

/**
 * @brief The following solution assume that each value will contain its either to
 *      its left or right side of its current position.  This solution will perform
 *      less checks compared to the solution above.
 *
 * @param nums The array that contains an odd entry value
 * @return int The odd entry value within the passed array
 */
int solution_two(const std::vector<int> &nums) {
    int start = 0, end = static_cast<int>(nums.size()) - 1, mid = (start + end) / 2;
    const int size = static_cast<int>(nums.size());

    while (start < end)
    {
        if ((mid + 1) < size && nums[mid] == nums[mid + 1]) {
            if ((mid + 1) % 2 == 1) {
                // The odd number of entries are located in the upper side
                start = mid + 1;
            } else {
                // The odd number of entries are located in the lower side
                end = mid - 1;
            } // if ((mid + 1) % 2 == 1)
        } else if ((mid - 1) > -1 && nums[mid] == nums[mid - 1]) {
            if (mid % 2 == 1) {
                // The odd number of entries are located in the upper side
                start = mid + 1;
            } else {
                // The odd number of entries are located in the lower side
                end = mid - 1;
            } // if ((mid + 1) % 2 == 1)
        } else {
            // This is the odd entry value
            return nums[mid];
        } // if ((mid + 1) < size && nums[mid] == nums[mid + 1])

        mid = (start + end) / 2;
    } // while (start < end)

    return (start == 0 || end == 0) ? nums.front() : nums.back();
}

int Solution::findOddOccurringElement(std::vector<int> const & nums) {
    return solution_two(nums);
} // findOddOccurringElement

} // namespace odd_occurring_element_four

} // namespace bit_manipulation

} // namespace valhalla
