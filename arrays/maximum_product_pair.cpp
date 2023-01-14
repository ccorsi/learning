/**
 * @file maximum_product_pair.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief 
 * @version 0.1
 * @date 2023-01-01
 * 
 * @copyright Copyright (c) 2023 Claudio Corsi
 * 
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "maximum_product_pair.h"

#include <math.h>

/*

Given an integer array, find a pair with the maximum product in it.

Each input can have multiple solutions. The output should match with either one of them.

Input : [-10, -3, 5, 6, -2]
Output: (-10, -3) or (-3, -10) or (5, 6) or (6, 5)

Input : [-4, 3, 2, 7, -5]
Output: (3, 7) or (7, 3)

If no pair exists, the solution should return the pair (-1, -1).

Input : [1]
Output: (-1, -1)

*/
#include <array>

std::pair<int,int> valhalla::arrays::maximum_product_pair::Solution::find(std::vector<int>& values) {
    std::pair<int,int> found(-1,-1);

    if (values.size() < 2) {
        // no such pair exists
        return found;
    }

    found = { values[0], values[1] };
    
    std::array<int,2> positive = { 0, 0 }, negative = { 0, 0 };

    for(int value : values) {
        if (value > 0) {
            if (value > positive[1]) {
                if (value > positive[0]) {
                    positive[1] = positive[0];
                    positive[0] = value;
                } else {
                    positive[1] = value;
                }
            }
        } else {
            if (value < negative[1]) {
                if (value < negative[0]) {
                    negative[1] = negative[0];
                    negative[0] = value;
                } else {
                    negative[1] = value;
                }
            }
        }
    }

    int total = positive[0] * positive[1];
    if (total > 0) {
        found = { positive[0], positive[1] };
        int totneg = negative[0] * negative[1];
        if (totneg > total) {
            found = { negative[0], negative[1] };
        }
    } else {
        total = negative[0] * negative[1];
        if (total > 0) {
            found = { negative[0], negative[1] };
        }
    }

    return found;
}