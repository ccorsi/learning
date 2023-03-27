/**
 * @file frequency_map.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=FrequencyMap
 * @version 0.1
 * @date 2023-03-27
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */


#include "frequency_map.h"

namespace valhalla {
    namespace arrays {
        namespace frequency_map {
            /*

            Given an unsorted integer array whose elements lie in the range 0 to `n-1`
            where `n` is the array size, calculate the frequency of all array elements
            in linear time and using constant space.

            Input : [2, 3, 1, 3, 1, 1]
            Output: {1: 3, 2: 1, 3: 2}

            Explanation:

            Element 1 appears thrice.
            Element 2 appears once.
            Element 3 appears twice.

            */

            std::unordered_map<int,int> Solution::findFrequency(std::vector<int> & nums) {
                std::unordered_map<int,int> frequency;

                for (int key : nums)
                    frequency[key]++;

                return frequency;
            } // findFrequency
        }
    }
}
