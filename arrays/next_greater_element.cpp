/**
 * @file next_greater_element.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=NextGreaterElement
 * @version 0.1
 * @date 2023-05-03
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "next_greater_element.h"

#include <climits>

namespace valhalla {
    namespace arrays {
        namespace next_greater_element {

            // This following structure does not offer the correct solution to this problem.
            struct node {
                node *left, *right;
                int m_value;
                node(int value) : left(nullptr), right(nullptr), m_value(value) {}
                int add(int value) {
                    if (value < m_value) {
                        if (left) {
                            return left->add(value);
                        }
                        left = new node(value);
                        return m_value;
                    } else if (value > m_value) {
                        if (right) {
                            return right->add(value);
                        }
                        right = new node(value);
                        return -1;
                    }
                    if (left) return -1;
                    else return m_value;
                }
                ~node() {
                    if (left) {
                        delete left;
                        left = nullptr;
                    }

                    if (right) {
                        delete right;
                        right = nullptr;
                    }
                }
            };

            /*

            Given an integer array, find the next greater element for every array element. The
            next greater element of a number x is the first greater number to the right of x in
            the array.

            In other words, for each element A[i] in the array A, find an element A[j] such
            that j > i and A[j] > A[i] and the value of j should be as minimum as possible. If
            the next greater element doesn't exist in the array for any element, consider it -1.

            Input:  [2, 7, 3, 5, 4, 6, 8]
            Output: [7, 8, 5, 6, 6, 8, -1]

            Input:  [5, 4, 3, 2, 1]
            Output: [-1, -1, -1, -1, -1]

            Note that the next greater element for the last array element is always -1.

            */

            std::vector<int> Solution::findNextGreaterElements(std::vector<int> const & nums) {
                const int size = nums.size();

                std::vector<int> elements(size, INT_MIN);

                if (size == 0) return elements;

                /*
                    Version 1:  This is valid solution to this problem but it is really inefficient
                                of a solution.
                for (int i = 0 ; i < size ; i++) {
                    const int value = nums[i];
                    for (int j = i + 1 ; j < size ; j++) {
                        if (nums[j] > value) {
                            elements[i] = nums[j];
                            break; // we are done therefore exit inner loop
                        } // if
                    } // for
                } // for
                */

                /*
                    Version 2:  This one was completely wrong and didn't offer any insight besides
                                the fact that this was a really bad idea that offered no solution.

                if (size > 0) {
                    struct node root(nums.back());

                    int idx = nums.size() - 1;

                    while (idx-- > 0) {
                        elements[idx] = root.add(nums[idx]);
                    } // while
                }
                */

                /*
                    Version 3:  Let us assume that the last entries will always be the ones that are
                                greater than the prior one.  So we then compare the resulting next 
                                greater element with the current element value.  We choose first the
                                passed entries and then the greater one.
                */

                int idx = size - 1;

                while (idx-- > 0) {
                    int value = nums[idx];
                    int next = idx + 1;
                    while (next < size) {
                        if (nums[next] > value) {
                            elements[idx] = nums[next];
                            break;
                        } else if (elements[next] > value) {
                            elements[idx] = elements[next];
                            break;
                        }
                        next++;
                    } // while
                    if (next == size) {
                        elements[idx] = -1;
                    } // if
                } // while

                elements[size - 1] = -1;

                return elements;
            } // findNextGreaterElements
        }
    }
}
