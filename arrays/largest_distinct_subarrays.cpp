/**
 * @file largest_distinct_subarrays.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=LargestDistinctSubarrays
 * @version 0.1
 * @date 2023-03-26
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <iostream>

#include "largest_distinct_subarrays.h"

namespace valhalla {
    namespace arrays {
        namespace largest_distinct_subarrays {
            /*

            Given an integer array, find all maximum size contiguous subarrays having all distinct elements
            in them.

            Input : [5, 2, 3, 5, 4, 3]
            Output: {[5, 2, 3], [2, 3, 5, 4], [5, 4, 3]}

            Input : [1, 2, 3, 3]
            Output: {[1, 2, 3], [3]}

            Input : [1, 2, 3, 4]
            Output: {[1, 2, 3, 4]}

            Note: Since an input can have multiple subarrays with all distinct elements, the solution should
            return a set containing all the distinct subarrays.

            */

            std::set<std::vector<int>> Solution::findDistinctSubarrays(std::vector<int> const & nums) {
                std::set<std::vector<int>> subarrays;

                if ( ! nums.empty() ) {
                    std::set<int> processed;
                    std::vector<int> subarray;

                    for (int value : nums) {
                        if ( ! processed.insert(value).second ) {
                            // std::cout << "Adding [";
                            // for (int v : subarray)
                            //     std::cout << " " << v;
                            // std::cout << " ]" << std::endl;
                            // std::cout << "value = " << value << std::endl;
                            subarrays.insert(subarray);
                            while ( ! subarray.empty() && subarray[0] != value) {
                                processed.erase(subarray.front());
                                subarray.erase(subarray.begin());
                            } // while

                            if ( ! subarray.empty() && subarray[0] == value ) {
                                subarray.erase(subarray.begin());
                            } // if
                            // std::cout << "Purged [";
                            // for (int v : subarray)
                            //     std::cout << " " << v;
                            // std::cout << " ]" << std::endl;
                        } // if
                        subarray.push_back(value);
                    } // for

                    if ( ! subarray.empty() ) {
                        subarrays.insert(subarray);
                    } // if
                } // if

                return subarrays;
            } // findDistinctSubarrays
        }
    }
}
