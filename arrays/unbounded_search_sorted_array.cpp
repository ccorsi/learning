/**
 * @file unbounded_search_sorted_array.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=UnboundedSearchSortedArray
 * @version 0.1
 * @date 2023-02-20
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <iostream>

#include "unbounded_search_sorted_array.h"

std::function<int(int)> f;

/*

Given a monotonically increasing function f(x) on positive numbers, find the lowest positive integer x where f(x) > 0. In other words, find a positive number x such that f(i) > 0 for any integer i greater than or equal to x.

A function is called monotonically increasing if f(x) <= f(y) is true for all x and y, where x <= y. For example,

Input: f(x) = 2x - 100
Output: 51
Explanation: f(x) becomes positive for the first time when x = 51.

Input: f(x) = 3x - 100
Output: 34
Explanation: f(x) becomes positive for the first time when x = 34.

*/

int valhalla::arrays::unbounded_search_sorted_array::Solution::findValue() {
    /*
        NOTE: I don't like this implementation even thou it does work as expected.
            Will try to create a better solution for my next attempt.
    */
    int result = f(0);

    if (result == 0) {
        return 1;
    } // if

    int lower, higher;

    if (result < 0) {
        lower = 0;
        higher = -result;
        while (f(higher) < 0) higher = -f(higher);
        if (f(higher) == 0) return higher + 1;
    } else {
        lower = -result;
        higher = 0;
        while(f(lower) > 0) lower = -f(lower);
        if (f(lower) == 0) return lower + 1;
    }

    while (lower < higher) {
        int mid = ( higher + lower ) / 2;
        result = f(mid);

        if (result == 0) {
            return mid + 1;
        }

        if (result < 0) {
            lower = mid + 1;
        } else {
            higher = mid - 1;
        }
    } // while

    return (f(lower) <= 0) ? lower + 1 : lower;
}
