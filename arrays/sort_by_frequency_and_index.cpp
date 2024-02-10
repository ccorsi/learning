/**
 * @file sort_by_frequency_and_index.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=SortByFrequencyAndIndex
 * @version 0.1
 * @date 2023-04-11
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */


#include "sort_by_frequency_and_index.h"

#include <iostream>
#include <algorithm>
#include <map>
#include <set>

namespace valhalla {
    namespace arrays {
        namespace sort_by_frequency_and_index {
            /*

            Given an integer array, in-place sort its element by their frequency and index.
            If two elements have different frequencies, then the one which has more
            frequency should come first; otherwise, the one which has less index should
            come first, i.e., the solution should preserve the relative order of the equal
            frequency elements.

            Input : [3, 3, 1, 1, 1, 8, 3, 6, 8, 7, 8]
            Output: [3, 3, 3, 1, 1, 1, 8, 8, 8, 6, 7]

            */

            void Solution::sortByFrequencyAndIndex(std::vector<int> & nums) {
                std::map<int,int> counts;
                std::set<std::pair<int,std::vector<int>::size_type>> maps;

                for(std::vector<int>::size_type idx = 0 ; idx < nums.size() ; idx++) {
                    int num = nums[idx];
                    counts[num]++;
                    if (counts[num] == 1) {
                        maps.insert(std::pair<int,std::vector<int>::size_type>(num,idx));
                    }
                }

                std::vector<std::pair<int,std::vector<int>::size_type>> sorted(maps.begin(), maps.end());

                std::sort(sorted.rbegin(), sorted.rend(),
                    [&counts](std::pair<int,std::vector<int>::size_type> & lhs,
                             std::pair<int,std::vector<int>::size_type> & rhs) {
                        if (counts[lhs.first] == counts[rhs.first]) {
                            return lhs.second > rhs.second;
                        } else {
                            return counts[lhs.first] < counts[rhs.first];
                        }
                });

                std::vector<int>::size_type idx = 0;

                for(std::pair<int,std::vector<int>::size_type> entry : sorted) {
                    // std::cout << "first: " << entry.first << ", second: " << entry.second << ", count: " << counts[entry.first] << std::endl;
                    int cnt = counts[entry.first], value = entry.first;
                    while (cnt-- > 0) nums[idx++] = value;
                }

            } // sortByFrequencyAndIndex
        }
    }
}
