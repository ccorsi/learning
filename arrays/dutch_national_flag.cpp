/**
 * @file dutch_national_flag.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is an implemention to the problem https://www.techiedelight.com/?problem=DutchNationalFlagProblem
 * @version 0.1
 * @date 2023-01-17
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */
#include <iostream>
#include <assert.h>

#include "dutch_national_flag.h"

using namespace std;

/*

Given an array containing only 0’s, 1’s, and 2’s, in-place sort it in linear time and using constant space.

Input : [0, 1, 2, 2, 1, 0, 0, 2, 0, 1, 1, 0]
Output: [0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2]

*/

void valhalla::arrays::dutch_national_flag::Solution::sort(vector<int>& nums) {
    /*
        Since the array will *only* contain 0,1 and 2 values.  We can use a modified quicksort
        algorithm to sort the array in-place
    */
    if (nums.size() < 2) {
        // No need to do anthing since the array is already sorted
        return;
    }

    cout << "Sorting: ["; for(int value : nums) cout << " " << value; cout << " ]" << endl;

    const size_t last = nums.size() - 1;
    size_t end = 0 - 1; // this will become the largest integer for size_t
    size_t lidx = 0, ridx = last;
    size_t size = nums.size();

    for(int pivot = 2 ; pivot > 0 ; pivot--) {
        size_t left = lidx, right = ridx;

        while (true) {
            while (left < size && nums[left] < pivot) left++;

            if (left == size) break;

            while (right < size && nums[right] >= pivot) right--;

            if (right == end) {
                // we are all done we don't need to check the next pivot since the array is sorted
                break;
            }

            if (right < left) {
                // we can now update the ridx
                ridx = right;
                break;
            }

            if (left < right) {
                // cout << "left: " << left << ", right: " << right << ", [nums[left],nums[right]]: [" << nums[left] << "," << nums[right] << "], pivot: " << pivot;
                // swap entries
                int temp = nums[left];
                nums[left] = nums[right];
                nums[right] = temp;
                // cout << ", updated:  ["; for(int value : nums) cout << " " << value; cout << " ]" << endl;
            }
        }
    }
/*
    size_t idx = 0;
    const size_t last = nums.size() - 1;

    // iterator over pival values 1 and 2 only
    for(int pivot = 1 ; pivot < 3 ; pivot++) {
        size_t left = idx, right = last;
        cout << endl << "Pivot: " << pivot << ", initial: ["; for(int value : nums) cout << " " << value; cout << " ], left: " <<  left << ", right: " << right << endl << endl;

        while (true) {
            // move to first entry that is greater than or equal to pivot
            while (left < nums.size() && nums[left] < pivot) left++;

            if (left == nums.size()) break;

            while (nums[right] >= pivot) right--;

            if (right < left) break;

            if (left < right) {
                cout << "left: " << left << ", right: " << right << ", [nums[left],nums[right]]: [" << nums[left] << "," << nums[right] << "], pivot: " << pivot;
                // swap entries
                int temp = nums[left];
                nums[left] = nums[right];
                nums[right] = temp;
                cout << ", updated:  ["; for(int value : nums) cout << " " << value; cout << " ]" << endl;
            }
        }
    }
*/
}
