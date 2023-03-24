/**
 * @file group_elements.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=GroupElements
 * @version 0.1
 * @date 2023-03-22
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "group_elements.h"

#include <utility>
#include <set>
#include <algorithm>

namespace valhalla {
    namespace arrays {
        namespace group_elements {
            /*

            Given an unsorted integer array containing many duplicate elements, rearrange
            it such that the same element appears together and the relative order of the
            first occurrence of each element remains unchanged.

            Input : [1, 2, 3, 1, 2, 1]
            Output: [1, 1, 1, 2, 2, 3]

            Input : [5, 4, 5, 5, 3, 1, 2, 2, 4]
            Output: [5, 5, 5, 4, 4, 3, 1, 2, 2]

            Input : [7, 0, 4, 2, 5, 0, 6, 4, 0, 5]
            Output: [7, 0, 0, 0, 4, 4, 2, 5, 5, 6]

            */

            std::vector<int> Solution::sortArray(std::vector<int> const & nums) {
                std::vector<int> sorted;

                std::set<std::pair<int,std::pair<int,int>>, cmp> grouped;

                int index = 0;

                for (int num : nums) {
                    std::pair<int,std::pair<int,int>> current;
                    current.first = num;
                    current.second.first = index;
                    current.second.second = 1;

                    std::pair<std::set<std::pair<int,std::pair<int,int>>>::iterator,bool> result = grouped.insert(current);

                    if (result.second) {
                        // entry was newly added
                        index++;
                        continue;
                    }

                    std::set<std::pair<int,std::pair<int,int>>>::iterator itr = result.first;

                    // get a reference to the original values
                    current = (*itr);
                    current.second.second++;

                    // remove entry from set
                    grouped.erase(itr);

                    // add updated entry to the set
                    grouped.insert(current);

                } // for

                std::vector<std::pair<int,std::pair<int,int>>> values(grouped.begin(), grouped.end());

                std::sort(values.begin(), values.end(),
                          [](const std::pair<int,std::pair<int,int>> & lhs, const std::pair<int,std::pair<int,int>> & rhs) {
                            return lhs.second.first < rhs.second.first;
                        });

                for (std::pair<int,std::pair<int,int>> & value : values) {
                    int num  = value.first;
                    while (value.second.second-- > 0) {
                        sorted.push_back(num);
                    } // while
                } // for

                return sorted;
            } // sortArray
        }
    }
}
