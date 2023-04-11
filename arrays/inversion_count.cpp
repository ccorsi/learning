/**
 * @file inversion_count.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=InversionCount
 * @version 0.1
 * @date 2023-04-11
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */


#include "inversion_count.h"

namespace valhalla {
    namespace arrays {
        namespace inversion_count {
            /*

            Given an integer array, find the total number of inversions of it.
            If `(i < j)` and `(nums[i] > nums[j])`, then pair `(i, j)` is called
            an inversion of an array `nums`. The solution should provide count
            of all such pairs in the array.

            Input : [1, 9, 6, 4, 5]
            Output: 5
            Explanation: There are 5 inversions in the array: (9, 6), (9, 4), (9, 5), (6, 4), (6, 5)

            */

            int Solution::findInversionCount(std::vector<int> & nums) {
                int count = 0;
                const int size = nums.size();

                for (int i = 0 ;  i < size ; i++) {
                    const int value = nums[i];
                    for (int j = i + 1 ; j < size ; j++) {
                        if (value > nums[j]) count++;
                    }
                }

                return count;
            } // findInversionCount
        }
    }
}
