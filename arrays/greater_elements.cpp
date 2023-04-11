/**
 * @file greater_elements.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=GreaterElements
 * @version 0.1
 * @date 2023-04-05
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */


#include "greater_elements.h"

namespace valhalla {
    namespace arrays {
        namespace greater_elements {
            /*

            Given an unsorted integer array, print all greater elements than all
            elements present to their right.

            Input : [10, 4, 6, 3, 5]
            Output: [10, 6, 5]
            Explanation: The elements that are greater than all elements to their
            right are 10, 6, and 5.

            Note: The solution should return the elements in the same order as
            they appear in the input array.

            */

            std::vector<int> Solution::findGreaterElements(std::vector<int> const & nums) {
                std::vector<int> elements;
                const int size = nums.size();

    /*
        Version 1:
        This version did find some of the correct answers but at times missed some.  While when
        it did find the correct solution.  It contained multiple instances of the correct values.
                if (size > 0) {
                    is_greater(elements, nums, nums[0], 1);
                } // if
    */

                if (size > 0) {
                    elements.push_back(nums[0]);

                    for (int idx = 1 ; idx < size ; idx++) {
                        if (elements.back() > nums[idx]) {
                            elements.push_back(nums[idx]);
                        } else {
                            while ( ! elements.empty() && elements.back() < nums[idx]) {
                                elements.pop_back();
                            } // while
                            elements.push_back(nums[idx]);
                        }
                    } // for
                } // if

                return elements;
            } // findGreaterElements

    /*
        Version 1:
        This version did find some of the correct answers but at times missed some.  While when
        it did find the correct solution.  It contained multiple instances of the correct values.
            void Solution::is_greater(std::vector<int> & elements, std::vector<int> const & nums, int value, int idx) {
                const int size = nums.size();

                if (idx == size) {
                    elements.push_back(value);
                    return;
                } // if

                if (value > nums[idx]) {
                    is_greater(elements, nums, value, idx+1);
                } //

                for (idx++ ; idx < size ; idx++) {
                    is_greater(elements, nums, nums[idx], idx+1);
                } // for
            }
    */
        }
    }
}
