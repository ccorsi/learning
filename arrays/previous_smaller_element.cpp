/**
 * @file previous_smaller_element.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=PreviousSmallerElement
 * @version 0.1
 * @date 2023-05-14
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */


#include "previous_smaller_element.h"

namespace valhalla {
    namespace arrays {
        namespace previous_smaller_element {
            /*

            Given an integer array, find the previous smaller element for every array element.
            The previous smaller element of a number `x` is the first smaller number to the left
            of `x` in the array.

            In other words, for each element A[i] in the array A, find an element A[j] such that
            j < i and A[j] < A[i] and value of j should be as maximum as possible. If the previous
            smaller element doesn't in the array for any element, consider it -1.

            Input : [2, 5, 3, 7, 8, 1, 9]
            Output: [-1, 2, 2, 3, 7, -1, 1]

            Input : [5, 7, 4, 9, 8, 10]
            Output: [-1, 5, -1, 4, 4, 8]

            Note that the first element always has a previous smaller element as -1.

            */

            std::vector<int> Solution::findNextGreaterElements(std::vector<int> const & nums) {
                const int size = nums.size();
                std::vector<int> elements(size, -1);

                /*
                    Version 1:  This version of the solution was not very good at all and more often
                                than not.
                if (size > 0) {
                    int idx = 1, min = nums[0];

                    while (idx < size) {
                        int value = nums[idx];

                        if (min < value) {
                            elements[idx] = min;
                        } else if (value < min) {
                            min = value;
                        } // else if

                        idx++;
                    } // while
                } // if
                */

                for (int idx = size - 1 ; idx > -1 ; idx--) {
                    elements[idx] = findNextGreaterElement(nums, nums[idx], idx - 1);
                } // for

                return elements;
            } // findNextGreaterElements

            int Solution::findNextGreaterElement(std::vector<int> const & nums, int value, int idx) {
                if (idx < 0) {
                    return -1;
                } // if

                if (nums[idx] < value) {
                    return nums[idx];
                } // if

                return findNextGreaterElement(nums, value, idx - 1);
            }
        }
    }
}
