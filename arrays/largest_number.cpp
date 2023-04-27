/**
 * @file largest_number.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=LargestNumber
 * @version 0.1
 * @date 2023-04-12
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */


#include "largest_number.h"
#include <sstream>
#include <algorithm>
#include <iostream>

namespace valhalla {
    namespace arrays {
        namespace largest_number {
            /*

            Find the largest number possible from a set of given numbers, where the numbers
            append to each other in any order to form the largest number. The solution
            should return the string representation of the largest number.

            Input : [10, 68, 75, 7, 21, 12]
            Output: 77568211210

            */

            std::string Solution::findLargestNumber(std::vector<int> & nums) {
                std::string largest;

                std::vector<std::string> values;

                for (int num : nums) {
                    std::stringstream ss;
                    ss << num;
                    std::string value;
                    std::getline(ss, value);
                    values.push_back(value);
                } // for

                std::sort(values.begin(), values.end(), [values](const std::string & lhs, const std::string & rhs) {
                    // std::cout << "values: [";
                    // for (std::string value : values)
                    //     std::cout << " " << value;
                    // std::cout << " ], lhs=" << lhs << ", rhs=" << rhs << std::endl;
                    if (lhs.length() == rhs.length())
                        return lhs < rhs;

                    const int llen = lhs.length(), rlen = rhs.length();

                    int idx = 0;

                    if (llen < rlen) {
                        while ( idx < llen && lhs[idx] == rhs[idx]) {
                            idx++;
                        } // while

                        if (idx < llen) {
                            return lhs[idx] < rhs[idx];
                        } // if

                        while (idx % llen == 0 && idx < rlen) {
                            for (int cnt = 0 ; cnt < llen && idx < rlen ; cnt++) {
                                if (lhs[cnt] != rhs[idx]) {
                                    return lhs[cnt] < rhs[idx];
                                }
                                idx++;
                            } // for
                        } // while

                        if (idx != rlen) {
                            return lhs[idx % llen] < rhs[idx];
                        } // else

                        return false;
                    }

                    while ( idx < rlen && lhs[idx] == rhs[idx]) {
                        idx++;
                    } // while

                    if (idx < rlen) {
                        return lhs[idx] < rhs[idx];
                    } // if

                    while (idx % rlen == 0 && idx < llen) {
                        for (int cnt = 0 ; cnt < rlen && idx < llen ; cnt++) {
                            if (lhs[idx] != rhs[cnt]) {
                                return lhs[idx] < rhs[cnt];
                            }
                            idx++;
                        } // for
                    } // while

                    if (idx != llen) {
                        return lhs[idx] < rhs[idx % rlen];
                    } // else

                    return false;
                });

                // std::cout << "values: [";
                // for (std::string value : values)
                //     std::cout << " " << value;
                // std::cout << " ]" << std::endl;

                for (std::vector<std::string>::const_reverse_iterator itr = values.rbegin() ; itr != values.rend() ; itr++) {
                    largest += *itr;
                }

                return largest;
            } // findLargestNumber
        }
    }
}
