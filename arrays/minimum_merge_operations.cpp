/**
 * @file minimum_merge_operations.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=MinimumMergeOperations
 * @version 0.1
 * @date 2023-05-01
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */


#include "minimum_merge_operations.h"

namespace valhalla {
    namespace arrays {
        namespace minimum_merge_operations {
            /*

            Given a list of non-negative integers, find the minimum number of merge operations to make it a palindrome.

            Input : [6, 1, 3, 7]
            Output: 1
            Explanation: [6, 1, 3, 7] —> Merge 6 and 1 —> [7, 3, 7]

            Input : [6, 1, 4, 3, 1, 7]
            Output: 2
            Explanation: [6, 1, 4, 3, 1, 7] —> Merge 6 and 1 —> [7, 4, 3, 1, 7] —> Merge 3 and 1 —> [7, 4, 4, 7]

            Input : [1, 3, 3, 1]
            Output: 0
            Explanation: The list is already a palindrome

            */

            int Solution::findMin(std::vector<int> & nums) {

                if (nums.empty()) return 0;

                int min = 0, front = 0, back = nums.size() - 1,
                    frontValue = 0, backValue = 0;

                bool incFront = true, incBack = true;

                while (front < back) {
                    if (incFront) frontValue += nums[front];
                    if (incBack) backValue += nums[back];
                    if (frontValue == backValue) {
                        frontValue = backValue = 0;
                        front++; back--;
                        incFront = incBack = true;
                        continue;
                    }
                    min++; // increment count
                    if (frontValue < backValue) {
                        front++;
                        incFront = true;
                        incBack = false;
                    } else {
                        back--;
                        incFront = false;
                        incBack = true;
                    }
                } // while

                return min;
            } // findMin
        }
    }
}
