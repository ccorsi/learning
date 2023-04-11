/**
 * @file counting_sort.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=CountingSort
 * @version 0.1
 * @date 2023-04-11
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <map>

#include "counting_sort.h"

namespace valhalla {
    namespace arrays {
        namespace counting_sort {
            /*

            Given a collection of `n` items, each of which has a non-negative integer
            key whose maximum value is at most `k`, effectively sort it using the
            counting sort algorithm.

            Input : nums[] = [4, 2, 10, 10, 1, 4, 2, 1, 10], k = 10
            Output: [1, 1, 2, 2, 4, 4, 10, 10, 10]

            */

            void Solution::sort(std::vector<int> & nums, int k) {
                if ( ! nums.empty() ) {
                    const int size = nums.size();
                    std::map<int,int> counts;

                    for (int value : nums) {
                        counts[value]++;
                    } // for

                    int idx = 0;
                    for(int key = 0 ; key <= k ; key++) {
                        for (int count = counts[key] ; count > 0 ; count--) {
                            nums[idx++] = key;
                        } // for
                    } // for
                } // if
            } // sort
        }
    }
}
