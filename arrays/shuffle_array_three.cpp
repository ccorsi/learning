/**
 * @file shuffle_array_three.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=ShuffleArrayIII
 * @version 0.1
 * @date 2023-03-28
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "shuffle_array_three.h"

#include <random>

namespace valhalla {
    namespace arrays {
        namespace shuffle_array_three {
            /*

            Given an array of distinct integer, in-place shuffle the array. The
            solution should produce an unbiased permutation, i.e., every
            permutation is equally likely.

            Input: [1, 2, 3, 4, 5]
            Output: [5, 4, 2, 1, 3] or [4, 1, 5, 3, 2] or any other unbiased permutation.

            */

            void Solution::shuffle(std::vector<int> & nums) {
                if (nums.size() > 1) {
                    const int size = nums.size();

                    std::random_device rd;
                    std::mt19937 gen(rd());
                    std::uniform_int_distribution<> uniform(0, size - 1);

                    for (int cnt = 0 ; cnt < size ; cnt++) {
                        int from = uniform(gen);
                        int to = uniform(gen);
                        while (from == to) to = uniform(gen);

                        // swap values
                        int value  = nums[from];
                        nums[from] = nums[to];
                        nums[to]   = value;
                    } // for
                } // if
            } // shuffle
        }
    }
}
