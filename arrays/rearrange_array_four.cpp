/**
 * @file rearrange_array_four.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=RearrangeArrayIV
 * @version 0.2
 * @date 2023-02-10
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <iostream>

#include "rearrange_array_four.h"

/*

Given an array of positive and negative integers, in-place segregate them in linear time and constant space. The output should contain all negative numbers, followed by all positive numbers.

Input : [9, -3, 5, -2, -8, -6, 1, 3]
Output: [-3, -2, -8, -6, 9, 5, 1, 3] or [-3, -2, -8, -6, 9, 5, 1, 3] or any other valid combination.

Input : [-4, -2, -7, -9]
Output: [-4, -2, -7, -9] or any other valid combination.

Input : [2, 4, 3, 1, 5]
Output: [2, 4, 3, 1, 5] or any other valid combination.

*/

void valhalla::arrays::rearrange_array_four::Solution::rearrange(std::vector<int> & nums) {
    if (nums.empty()) return;

    const std::vector<int>::size_type size = nums.size();
    std::vector<int>::size_type left = 0;
    std::vector<int>::size_type right = size - 1;

    /*
        NOTE: The main issue with this solution is that it assumes that all the entries are
              going to be positive or negative only.  Which is not the case so that
              description of the problem is deceptive.  It is clear that when reading the
              description of the problem one should consider entries that are not explicitly
              stated that these values will never occur.

              The following solution will take that into account and be able to produce the
              required output with conditionally processing 0 entries.
    */
    while (left < right) {
        while (left < size && nums[left] < 0) left++;

        while (right > 0 && nums[right] > 0 ) right--;

        if (left < right) {
            // swap the entries
            int temp = nums[left];
            nums[left] = nums[right];
            nums[right] = temp;
        } // if

        if (left < right && nums[left] == 0 && nums[left] == nums[right]) {
            // We've encountered multiple zero entries.
            // We need to move passed these and get them
            // somewhere that we can proceed
            std::vector<int>::size_type start = left;
            while (start < right && nums[start] == 0) start++;

            if (start == right) return; // we are done

            nums[left] = nums[start];
            nums[start] = 0;
        } // if
    } // while
}

// NOTE: The problem with the following solutions is that they both assunmed that the
//       passed integer array will *only* contain positve and negative integers.  They
//       never assumed that the array would contain one or more zero values.  This was
//       causing these implementations to loop forever.

// NOTE: The following version was too slow for techie delight

// VERSION #2

// if (nums.empty()) return;

// std::vector<int>::size_type left = 0, right = nums.size() - 1;
// const std::vector<int>::size_type size = nums.size();

// while (left < right) {
//     while (left < right && ( nums[left] < 0 || nums[right] > 0 )) {
//         if (nums[left] < 0) left++;
//         if (nums[right] > 0) right--;
//     } // while

//     if (left < right) {
//         // swap the entries
//         int temp = nums[left];
//         nums[left] = nums[right];
//         nums[right] = temp;
//     } // if
// } // while

// NOTE: The following version was too slow for techie delight

// VERSION #1

// void valhalla::arrays::rearrange_array_four::Solution::rearrange(std::vector<int> & nums) {
//     if (nums.empty()) return;

//     std::vector<int>::size_type left = 0, right = nums.size() - 1;
//     const std::vector<int>::size_type size = nums.size();

//     // find the first positive entry
//     while (left < size && nums[left] < 0) left++;

//     // find the first negative entry starting from the end
//     while (right < size && nums[right] > 0) right--;

//     while (left < right && right < size) {
//         // swap the entries
//         int temp = nums[left];
//         nums[left] = nums[right];
//         nums[right] = temp;

//         // find the next positive entry
//         while (left < size && nums[left] < 0) left++;

//         // find the next negative entry
//         while (right < size && nums[right] > 0) right--;
//     } // while
// }
