/**
 * @file minimum_platforms.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=MinimumPlatforms
 * @version 0.1
 * @date 2023-03-16
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "minimum_platforms.h"

/*

Given a schedule containing the arrival and departure time of trains in a station,
find the minimum number of platforms needed to avoid delay in any train’s arrival.

Input:

arrival = [2.00, 2.10, 3.00, 3.20, 3.50, 5.00]
departure = [2.30, 3.40, 3.20, 4.30, 4.00, 5.20]

Output: 2

Explanation: The minimum platforms needed is 2

The train arrived at 2.00 on platform 1
The train arrived at 2.10 on platform 2
The train departed at 2.30 from platform 1
The train arrived at 3.00 on platform 1
The train departed at 3.20 from platform 1
The train arrived at 3.20 on platform 1
The train departed at 3.40 from platform 2
The train arrived at 3.50 on platform 2
The train departed at 4.00 from platform 2
The train departed at 4.30 from platform 1
The train arrived at 5.00 on platform 1
The train departed at 5.20 from platform 1

*/

#include <iostream>
#include <algorithm>

int valhalla::arrays::minimum_platforms::Solution::findMinPlatforms(std::vector<double> arrival, std::vector<double> departure) {
    int min = 0, current = 0, a_idx = 0, d_idx = 0;
    const int asize = arrival.size(), dsize = departure.size();
    std::sort(arrival.begin(), arrival.end());
    std::sort(departure.begin(), departure.end());

    while (a_idx < asize) {
        if (arrival[a_idx] < departure[d_idx]) {
            current++; a_idx++;
            if (current > min) {
                min = current;
            } // if
        } else {
            current--; d_idx++;
        } // else
    } // while

    return min;
}
