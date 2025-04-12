/**
 * @file missing_and_duplicate_element.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=MissingAndDuplicateElement
 * @version 0.1
 * @date 2025-04-12
 *
 * @copyright Copyright (c) 2025 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "missing_and_duplicate_element.h"

#include <set>
#include <map>

namespace valhalla {

namespace bit_manipulation {

namespace missing_and_duplicate_element {

/*

Given an integer array of size `n`, with all its elements between 1 and `n` and one element
occurring twice and one element missing. Find the missing number and the duplicate element
in linear time and without using any extra memory.

Input: [4, 3, 6, 5, 2, 4]
Output: (4, 1)
Explanation: The duplicate element is 4 and the missing element is 1.

Input: [4, 2, 2, 1]
Output: (2, 3)
Explanation: The duplicate element is 2 and the missing element is 3.

Note: The solution should return (duplicate element, missing element) pair. Assume valid input.

*/

// This is not a valid solution :-(
std::pair<int,int> attempt_one(std::vector<int> const & nums) {
    int number = 1, duplicate = 0, n = static_cast<int>(nums.size());

    for (int num : nums) {
        duplicate += (number++ - num);
    } // for (int num : nums)

    return std::pair<int,int>(n - duplicate, duplicate);
} // attempt_one

// This is not a valid solution :-(
std::pair<int,int> attempt_two(std::vector<int> const & nums) {
    int number = 1, n = static_cast<int>(nums.size());
    std::set<int> solution;

    for (int num : nums) {
        if (solution.insert(number).second == false)
            solution.erase(number);
        if (solution.insert(num).second == false)
            solution.erase(num);
        number++;
    } // for (int num : nums)

    std::pair<int,int> values;
    auto itr = solution.begin();
    values.first = *itr++;
    values.second = *itr;
    return values;
} // attempt_two

// This is a valid solution
std::pair<int,int> solution_one(std::vector<int> const & nums) {
    int number = 1, n = static_cast<int>(nums.size());
    std::set<int> solution;
    std::map<int,int> count;

    for (int num : nums) {
        if (solution.insert(number).second == false)
            solution.erase(number);
        if (solution.insert(num).second == false)
            solution.erase(num);
        number++;
        count[num]++;
    } // for (int num : nums)

    std::pair<int,int> values;
    for (int value : solution) {
        if (count[value] == 0)
            values.second = value;
        else
            values.first = value;
    }

    return values;
} // solution_one

// This is a better solution
std::pair<int,int> solution_two(std::vector<int> const & nums) {
    int number = 1, n = static_cast<int>(nums.size());
    std::vector<int> solution(n+1,0);

    for (int num : nums) {
        solution[num]++;
    } // for (int num : nums)

    std::pair<int,int> values;

    for (int idx = 1 ; idx < n + 1 ; idx++) {
        if (solution[idx] == 0)
            values.second = idx;
        else if (solution[idx] == 2)
            values.first = idx;
    } // for (int idx = 1 ; idx < n + 1 ; idx++)

    return values;
} // solution_two

// This is a better solution
std::pair<int,int> solution_three(std::vector<int> const & nums) {
    int number = 1, n = static_cast<int>(nums.size());
    std::vector<int> solution(n+1,0);

    for (int num : nums) {
        solution[num]++;
    } // for (int num : nums)

    std::pair<int,int> values;
    int count = 0;

    for (int idx = 1 ; idx < n + 1 ; idx++) {
        if (solution[idx] == 0) {
            values.second = idx;
            count++;
        } else if (solution[idx] == 2) {
            values.first = idx;
            count++;
        } // if (solution[idx] == 0)
        if (count == 2) {
            // we are done those break out of the for loop
            break;
        } // if (count == 2)
    } // for (int idx = 1 ; idx < n + 1 ; idx++)

    return values;
} // solution_three

std::pair<int,int> Solution::findMissingAndDuplicate(std::vector<int> const & nums) {
    return solution_three(nums);
} // findMissingAndDuplicate

} // namespace missing_and_duplicate_element

} // namespace bit_manipulation

} // namespace valhalla
