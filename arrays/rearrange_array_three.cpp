/**
 * @file rearrange_array_three.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=RearrangeArrayIII
 * @version 0.1
 * @date 2023-02-06
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <iostream>
#include <set>

#include "rearrange_array_three.h"

/*

Given an unsorted integer array `A` of size `n`, whose elements lie in the range 0 to `n-1`,
in-place rearrange the array such that `A[A[i]]` is set to `i` for every array element `A[i]`.
Do this in linear time and without using any extra constant space.

Input : [1, 3, 4, 2, 0]
Output: [4, 0, 3, 1, 2]
Explanation:

A[0] = 1, A[1] becomes 0
A[1] = 3, A[3] becomes 1
A[2] = 4, A[4] becomes 2
A[3] = 2, A[2] becomes 3
A[4] = 0, A[0] becomes 4

*/

void valhalla::arrays::rearrange_array_three::Solution::rearrange(std::vector<int> & A) {
    // std::cout << "A [";
    // for (int value : A)
    //     std::cout << " " << value;
    // std::cout << " ]" << std::endl;

    std::set<int> processed;
    const std::vector<int>::size_type size = A.size();
    // int cnt = 0;
    // const int end = 10;

    while (processed.size() < size) {
        int index = 0;
        while (processed.find(index) != processed.end()) {
            index = ( index + 1 ) % size;
        } //  while

        int stops_at = A[index];

        int set_to = index;
        int pos = stops_at;

        // std::cout << "Start index: " << index << ", A[index]: " << A[index] << ", stops_at: " << stops_at << std::endl;
        do {
            processed.insert(pos);
            int temp_set_to = pos;
            int temp_pos = A[pos];
            A[pos] = set_to;
            set_to = temp_set_to;
            pos = temp_pos;
            // std::cout << "Next set_to: " << set_to << ", pos: " << pos << ", processed: [";
            // for (int i : processed)
            //     std::cout << " " << i;
            // std::cout << " ], A: [";
            // for (int i : A)
            //     std::cout << " " << i;
            // std::cout << " ]" << std::endl;
            // if (++cnt > end) break;
        } while (pos != stops_at);

        // std::cout << "End" << std::endl;
        // if (++cnt > end) break;
    } // while
}
