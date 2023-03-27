/**
 * @file add_arrays.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=AddArrays
 * @version 0.1
 * @date 2023-03-27
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */


#include "add_arrays.h"

namespace valhalla {
    namespace arrays {
        namespace add_arrays {
            /*

            Given two arrays of positive integers, add their elements into a new array.
            The solution should add both arrays, one by one starting from the 0'th index,
            and split the sum into individual digits if it is a 2–digit number.

            Input : [23, 5, 2, 7, 87], [4, 67, 2, 8]
            Output: [2, 7, 7, 2, 4, 1, 5, 8, 7]

            Input : [], [4, 67, 2, 8]
            Output: [4, 6, 7, 2, 8]

            */

            std::vector<int> Solution::add(std::vector<int> const & X, std::vector<int> const & Y) {
                std::vector<int> combined;

                const int x_size = X.size(), y_size = Y.size();
                const int min = std::min(x_size, y_size);

                for (int idx = 0 ; idx < min ; idx++) {
                    int sum = X[idx] + Y[idx];
                    if (sum < 10) {
                        if (sum > 0) {
                            combined.push_back(sum);
                        } // if
                        continue;
                    } // if
                    std::vector<int> current;
                    while (sum > 0) {
                        current.push_back(sum % 10);
                        sum /= 10;
                    } // while
                    for (std::vector<int>::const_reverse_iterator itr = current.rbegin() ; itr != current.rend() ; itr++ ) {
                        combined.push_back(*itr);
                    }
                } // for

                for (int idx = min ; idx < x_size ; idx++) {
                    int sum = X[idx];
                    if (sum < 10) {
                        if (sum > 0) {
                            combined.push_back(sum);
                        } // if
                        continue;
                    } // if
                    std::vector<int> current;
                    while (sum > 0) {
                        current.push_back(sum % 10);
                        sum /= 10;
                    } // while
                    for (std::vector<int>::const_reverse_iterator itr = current.rbegin() ; itr != current.rend() ; itr++ ) {
                        combined.push_back(*itr);
                    }
                } // for

                for (int idx = min ; idx < y_size ; idx++) {
                    int sum = Y[idx];
                    if (sum < 10) {
                        if (sum > 0) {
                            combined.push_back(sum);
                        } // if
                        continue;
                    } // if
                    std::vector<int> current;
                    while (sum > 0) {
                        current.push_back(sum % 10);
                        sum /= 10;
                    } // while
                    for (std::vector<int>::const_reverse_iterator itr = current.rbegin() ; itr != current.rend() ; itr++ ) {
                        combined.push_back(*itr);
                    }
                } // for

                return combined;
            } // add
        }
    }
}
