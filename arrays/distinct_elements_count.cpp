/**
 * @file distinct_elements_count.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=DistinctElementsCount
 * @version 0.1
 * @date 2023-03-26
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <iostream>
#include <map>

#include "distinct_elements_count.h"

namespace valhalla {
    namespace arrays {
        namespace distinct_elements_count {
            /*

            Given an integer array and a positive integer `k`, find the count of
            distinct elements in every contiguous subarray of size `k`.

            Input : nums[] = [2, 1, 2, 3, 2, 1, 4, 5], k = 5
            Output: [3, 3, 4, 5]
            Explanation:

            The count of distinct elements in subarray [2, 1, 2, 3, 2] is 3
            The count of distinct elements in subarray [1, 2, 3, 2, 1] is 3
            The count of distinct elements in subarray [2, 3, 2, 1, 4] is 4
            The count of distinct elements in subarray [3, 2, 1, 4, 5] is 5


            Input : nums[] = [1, 1, 2, 1, 3], k = 3
            Output: [2, 2, 3]
            Explanation:

            The count of distinct elements in subarray [1, 1, 2] is 2
            The count of distinct elements in subarray [1, 2, 1] is 2
            The count of distinct elements in subarray [2, 1, 3] is 3

            */

            std::vector<int> Solution::findDistinctCount(std::vector<int> const & nums, int k) {
                std::vector<int> distinct;
                const int size = nums.size();

                if (size < k) return distinct;

                std::map<int,int> counts;

                for (int idx = 0 ; idx < k && idx < size ; idx++) {
                    int key = nums[idx];
                    counts[key]++;
                }

                distinct.push_back(counts.size());

                for (int idx = k ; idx < size ; idx++) {
                    std::cout << "counts: ";
                    for (std::map<int,int>::value_type entry : counts) {
                        std::cout << " " << entry.first << " = " << entry.second;
                    } // for
                    std::cout << std::endl;
                    int key =  nums[idx - k];
                    counts[key]--;
                    if (counts[key] == 0) {
                        // delete the key
                        counts.erase(key);
                        std::cout << "removed key = " << key << std::endl;
                    } // if
                    key = nums[idx];
                    counts[key]++;

                    distinct.push_back(counts.size());
                } // for

                return distinct;
            } // findDistinctCount
        }
    }
}
