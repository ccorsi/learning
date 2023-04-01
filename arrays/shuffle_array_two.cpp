/**
 * @file shuffle_array_two.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=ShuffleArrayII
 * @version 0.1
 * @date 2023-03-28
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <iostream>
#include <map>
#include <algorithm>

#include "shuffle_array_two.h"

namespace valhalla {
    namespace arrays {
        namespace shuffle_array_two {
            /*

            Given two integer arrays, reorder elements of the first array by the
            order of elements defined by the second array.

            The elements that are not present in the second array but present in
            the first array should be appended at the end in sorted order. The
            second array can contain some extra elements which are not part of
            the first array.

            Input:

            nums[] = [5, 8, 9, 3, 5, 7, 1, 3, 4, 9, 3, 5, 1, 8, 4]
            pos[] = [3, 5, 7, 2]

            Output : [3, 3, 3, 5, 5, 5, 7, 1, 1, 4, 4, 8, 8, 9, 9]

            */

            void Solution::shuffle(std::vector<int> & nums, std::vector<int> & pos) {

                if ( ! nums.empty() && ! pos.empty() ) {
                    std::map<int,int> values;
                    const int size = pos.size();

                    for(int idx = 0 ; idx < size ; idx++)
                        values[pos[idx]] = idx;

                    int front = 0, last = nums.size() - 1;

                    while (front < last) {
                        // find first entry not part of the pos vector
                        while (front < last && values.find(nums[front]) != values.end()) front++;

                        // find last entry that is part of the pos vector
                        while (front < last && values.find(nums[last]) == values.end()) last--;

                        // swap entry
                        if (front < last) {
                            int value = nums[last];
                            nums[last] = nums[front];
                            nums[front] = value;
                            front++;
                        } // if
                    } // while

                    // insure that the front entry is not part of the values
                    if (values.find(nums[front]) != values.end()) front++;

                    // std::cout << "front: " << front << ", last: " << last << std::endl;
                    // std::cout << "1 - [";
                    // for (int value : nums)
                    //     std::cout << " " << value;
                    // std::cout << " ]" << std::endl;
                    // std::cout << "Iterator value at front: " << *(nums.begin() + front) << std::endl;

                    // sort the first part of the array based on the pos vector
                    std::sort(nums.begin(), nums.begin() + front, [&tosort = values](const int & lhs, const int & rhs) -> bool {
                        int l = tosort[lhs], r = tosort[rhs];
                        return l < r;
                    });

                    // std::cout << "2 - [";
                    // for (int value : nums)
                    //     std::cout << " " << value;
                    // std::cout << " ]" << std::endl;

                    // sort the last part of the vector from front onwards
                    std::sort(nums.begin() + front, nums.end());

                    // std::cout << "3 - [";
                    // for (int value : nums)
                    //     std::cout << " " << value;
                    // std::cout << " ]" << std::endl;
                } // if

            } // shuffle
        }
    }
}
