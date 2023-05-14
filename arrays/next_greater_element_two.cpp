/**
 * @file next_greater_element_two.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=NextGreaterElementII
 * @version 0.1
 * @date 2023-05-03
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "next_greater_element_two.h"

#include <climits>

namespace valhalla {
    namespace arrays {
        namespace next_greater_element_two {
            /*

            Given a circular integer array, find the next greater element for every element in it.
            The next greater element of an element `x` in the array is the first larger number to
            the next of `x`.

            In a circular array, the indices will wrap around as if it were connected end-to-end.
            In other words, the end of the array wraps around to the start of the array. This
            facilitate searching circularly to find the next greater number. If the next greater
            element doesn't exist, consider it to be -1.

            Input : [3, 5, 2, 4]
            Output: [5, -1, 4, 5]

            Input : [7, 5, 3, 4]
            Output: [-1, 7, 4, 7]

            */

            std::vector<int> Solution::findNextGreaterElements(std::vector<int> const & nums) {
                std::vector<int> elements(nums.size(), INT_MIN);

                if (nums.empty()) return elements;

                const int size = nums.size();

                /*
                    Version 1:  This version is correct but it is really not very good.  There has
                                to be another version that is correct and much faster than this
                                current version that takes O(n^2).
                for (int i = 0 ; i < size ; i++) {
                    const int value =  nums[i];
                    for (int j = (i + 1) % size ;  j != i ; j = (j + 1) % size) {
                        if (nums[j] > value) {
                            elements[i] = nums[j];
                            break;
                        } // if
                    } // for
                } // for
                */

                int idx = size;

                while (idx-- > 0) {
                    int value = nums[idx];
                    int next = (idx + 1) % size;
                    while (next != idx) {
                        if (nums[next] > value) {
                            elements[idx] = nums[next];
                            break;
                        } else if (elements[next] > value) {
                            elements[idx] = elements[next];
                            break;
                        }
                        next = (next + 1) % size;
                    } // while

                    if (next == idx) {
                        elements[idx] = -1;
                    } // if
                } // while

                return elements;
            } // findNextGreaterElements
        }
    }
}
