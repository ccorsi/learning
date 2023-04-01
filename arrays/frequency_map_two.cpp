/**
 * @file frequency_map_two.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=FrequencyMapII
 * @version 0.1
 * @date 2023-03-28
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */


#include "frequency_map_two.h"

namespace valhalla {
    namespace arrays {
        namespace frequency_map_two {
            /*

            Given a sorted array containing duplicates, efficiently find each
            element's frequency without traversing the whole array.

            Input: [2, 2, 2, 4, 4, 4, 5, 5, 6, 8, 8, 9]
            Output: {2: 3, 4: 3, 5: 2, 6: 1, 8: 2, 9: 1}

            Explanation:

            2 and 4 occurs thrice
            5 and 8 occurs twice
            6 and 9 occurs once

            */

            std::unordered_map<int,int> Solution::findFrequency(std::vector<int> const & nums) {
                std::unordered_map<int,int> frequency;

                const int size = nums.size();

                if (size > 0) {
                    int min = nums.front(), max = nums.back();

                    if (min == max) {
                        frequency[min] = size;
                    } else {
                        int front = 0, back = size - 1;

                        while (front < back) {
                            if (nums[front] == nums[back]) {
                                int key = nums[front];
                                frequency[key] += back - front + 1;
                                front = back + 1;
                                break;
                            } // if
                            frequency[nums[front++]]++;
                            frequency[nums[back--]]++;
                        } // while

                        if (front == back) {
                            frequency[nums[front]]++;
                        } // if
                    } // else
                } // if

                return frequency;
            } // findFrequency
        }
    }
}
