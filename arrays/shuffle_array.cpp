/**
 * @file shuffle_array.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution of the problem https://www.techiedelight.com/?problem=ShuffleArray
 * @version 0.1
 * @date 2023-03-28
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <set>

#include "shuffle_array.h"

namespace valhalla {
    namespace arrays {
        namespace shuffle_array {
            /*

            Given an array of distinct integers `nums`, in-place shuffle it according
            to order specified by another array `pos`. For every index `i` in `nums`,
            the solution should update `nums[pos[i]] = nums[i]`.

            Input:

            nums[] = [1, 2, 3, 4, 5]
            pos[] = [3, 2, 4, 1, 0]

            Output: [5, 4, 2, 1, 3]

            */

            void Solution::shuffle(std::vector<int> & nums, std::vector<int> & pos) {
                // This contains the position in nums that have been replaced
                std::set<int> processed;

                while (nums.size() != processed.size()) {
                    int last_idx = 0; // Last updated nums entry

                    // Find the first nums index that hasn't been processed
                    while (processed.find(pos[last_idx]) != processed.end()) {
                        last_idx++;
                    } // while

                    // add index to processed data
                    processed.insert(last_idx);
                    // save the last value being replaced
                    int last_value = nums[pos[last_idx]];
                    // replace the value
                    nums[pos[last_idx]] = nums[last_idx];
                    // keep a reference to the last pos that was updated
                    last_idx = pos[last_idx];

                    while (processed.find(last_idx) == processed.end()) {
                        processed.insert(last_idx);
                        int temp_idx   = pos[last_idx];
                        int temp_value = nums[temp_idx];
                        nums[temp_idx] = last_value;

                        last_value = temp_value;
                        last_idx   = temp_idx;
                    } // while
                } // while

                /*

                Version 1:

                const int size = nums.size();
                if (size > 0) {
                    int last_value = nums[pos[0]];
                    int last_idx = pos[0];
                    nums[pos[0]] = nums[0];

                    for (int cnt = 1 ; cnt < size ; cnt++) {
                        int temp_value = nums[pos[last_idx]];
                        nums[pos[last_idx]] = last_value;
                        last_value = temp_value;
                        last_idx = pos[last_idx];
                    } // for
                } // if

                */

            } // shuffle
        }
    }
}
