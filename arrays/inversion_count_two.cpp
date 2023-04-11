/**
 * @file inversion_count_two.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=InversionCountII
 * @version 0.1
 * @date 2023-04-11
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */


#include "inversion_count_two.h"

namespace valhalla {
    namespace arrays {
        namespace inversion_count_two {
            /*

            Given an integer array, count the total number of triplets,
            which leads to an inversion.
            If (i < j < k) and (nums[i] > nums[j] > nums[k]),
            then the triplet (i, j, k) has formed an inversion in array `nums`.

            Input : [1, 9, 6, 4, 5]
            Output: 2
            Explanation: There are two inversions of size three in the array:
            (9, 6, 4) and (9, 6, 5).

            Input : [9, 4, 3, 5, 1]
            Output: 5
            Explanation: There are five inversions of size three in the array:
            (9, 4, 3), (9, 4, 1), (9, 3, 1), (4, 3, 1), and (9, 5, 1).

            */

            int Solution::findInversionCount(std::vector<int> const & nums) {
                int count = 0;
                const int size = nums.size();

                for (int i = 0 ; i < size ; i++) {
                    int left = nums[i];
                    for (int j = i + 1 ; j < size ; j++) {
                        int middle = nums[j];
                        if (left > middle) {
                            for (int k = j + 1 ; k < size ; k++) {
                                if (middle > nums[k]) count++;
                            } // for
                        } // for
                    } // for
                } // for

                return count;
            } // findInversionCount
        }
    }
}
