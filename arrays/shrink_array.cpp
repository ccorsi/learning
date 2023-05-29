/**
 * @file shrink_array.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=ShrinkArray
 * @version 0.1
 * @date 2023-05-21
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "shrink_array.h"

#include <iostream>
#include <algorithm>
#include <set>

namespace valhalla {
    namespace arrays {
        namespace shrink_array {
            /*

            Given an integer array and an integer k, shrink it by removing adjacent triplets
            that satisfy the given constraints and return the total number of elements in the
            resultant array.

            A triplet (x, y, z) can only be removed if, for the number k, the second element
            y of the triplet is precise k more than the first element x. The third element,
            z, is precise k more than the second element y. The total number of elements in
            the final array should be as few as possible.

            Input: nums = [1, 2, 3, 5, 7, 8], k = 2
            Output: 3
            Explanation: The adjacent triplet (3, 5, 7) can be removed from the array.
                         The resultant array is [1, 2, 8] cannot be reduced further.

            Input: nums = [-1, 0, 1, 2, 3, 4], k = 1
            Output: 0
            Explanation: The result is 0 since all elements can be removed from the array.
                         First, the adjacent triplet (2, 3, 4) is removed. The array is now
                         reduced to [-1, 0, 1], which forms another valid triplet and can be
                         removed from the array.

            Note that if the adjacent triplet (1, 2, 3) is removed from the array first,
            the resultant array [-1, 0, 4] cannot be reduced further.

            */

            int Solution::shrink(std::vector<int> const & nums, int k) {
                /*
                    Version 1:  This implementation can purged entries that can be
                                used for other triplets and shrink the array more
                                than removing them at the moment.

                const int size = nums.size();
                const int last = size - 2;
                std::set<int> purged;
                bool shrinked;

                do {
                    shrinked = false;
                    for (int left = 0 ; left < last ; left++) {
                        if (purged.find(left) != purged.end()) {
                            // skip purged entries
                            continue;
                        } // if
                        int next = nums[left] + k;
                        int middle = left + 1;
                        while (purged.find(middle) != purged.end()) {
                            middle++;
                        } // while
                        if (middle == size) continue;
                        if (next != nums[middle]) {
                            // we are done
                            continue;
                        }
                        int right = middle + 1;
                        while (purged.find(right) != purged.end()) {
                            right++;
                        } // while
                        if (right == size) continue;
                        next += k;
                        if (next == nums[right]) {
                            // we shrinked a triplet
                            purged.insert(left);
                            purged.insert(middle);
                            purged.insert(right);
                            shrinked = true;
                        } // if
                    } // for
                } while (shrinked);
                */

                const int size = nums.size();
                std::set<int> purged;
                bool shrinked;

                do {
                    shrinked = false;
                    for (int right = size - 1 ; right > -1 ; right--) {
                        if (purged.find(right) != purged.end()) {
                            // skip purged entries
                            continue;
                        } // if
                        int next = nums[right] - k;
                        int middle = right - 1;
                        while (purged.find(middle) != purged.end()) {
                            middle--;
                        } // while
                        if (middle == -1) continue;
                        if (next != nums[middle]) {
                            // we are done
                            continue;
                        }
                        int left = middle - 1;
                        while (purged.find(left) != purged.end()) {
                            left--;
                        } // while
                        if (left == -1) continue;
                        next -= k;
                        if (next == nums[left]) {
                            // we shrinked a triplet
                            purged.insert(left);
                            purged.insert(middle);
                            purged.insert(right);
                            shrinked = true;
                        } // if
                    } // for
                } while (shrinked);

                // std::cout << "[";
                // for (int value : nums) {
                //     std::cout << " " << value;
                // }
                // std::cout << " ], " << k << ", " << (nums.size() - purged.size()) << std::endl;

                return nums.size() - purged.size();
            } // shrink
        }
    }
}
