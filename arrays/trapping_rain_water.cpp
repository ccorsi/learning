/**
 * @file trapping_rain_water.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=TrappingRainWater
 * @version 0.2
 * @date 2023-03-16
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "trapping_rain_water.h"

/*

Find the maximum amount of water that can be trapped within a given set of bars where
each bar’s width is 1 unit.

Input : [7, 0, 4, 2, 5, 0, 6, 4, 0, 5]
Output: 25
Explanation: The maximum amount of water that can be trapped is 25.

Pictorial representation: https://techiedelight.com/practice/images/TrappingRainWater.png

Here is a textual representation of the solution to the above input:

  7 0 4 2 5 0 6 4 0 5

  *
  * + + + + + *
  * + + + * + * + + *
  * + * + * + * * + *
  * + * + * + * * + *
  * + * + * + * * + *
  * + * + * + * * + *

  + == 25

Input : [10, 8, 6, 5, 4, 2]
Output: 0

*/

#include <iostream>

int valhalla::arrays::trapping_rain_water::Solution::trapWater(std::vector<int> const & bars) {
    /* We are looking for peaks and valleys before deciding which ones offer the best coverage. */
    std::vector<int> peaks;

    const int last = bars.size() - 1;
    int idx = 0;

    while (true) {

        // find a peak
        while (idx < last && bars[idx] < bars[idx+1]) idx++;

        peaks.push_back(idx);

        if (idx == last) break;

        // find a valley

        while (idx < last && bars[idx] >= bars[idx+1]) idx++;

        if (idx == last) break;

    } // while

    // We've correctly identified all the peaks within the passed bars array

    std::cout << "Peaks [";
    for (int peak : peaks)
        std::cout << " (" << peak << "," << bars[peak] << ")";
    std::cout << " ]" << std::endl;

    if (peaks.size() < 2) return 0;

    if (peaks.size() == 2) {
        // This is the most ideal solution that can be found.

        int height = std::min(bars[peaks[0]], bars[peaks[1]]);

        int space = 0;

        for (idx = peaks[0] + 1 ; idx < peaks[1] ; idx++) {
            if (height > bars[idx])
                space += ( height - bars[idx] );
        } // for

        return space;
    } else {
        // This is where all of the trickity issues need to be thought out and resolved.

        int space = 0;

        // Find the larger integer greater than or equal to the left entry
        int left = 0, right = 1;

        const int peaks_size = peaks.size(), last_peaks = peaks.size() - 1;

        while (right < last_peaks) {
            int max_right = right;
            while (right < peaks_size && bars[peaks[left]] >= bars[peaks[right]]) {
                if (bars[peaks[right]] >= bars[peaks[max_right]]) {
                    max_right = right;
                } // if
                right++;
            } // while

            int height = std::min(bars[peaks[left]], bars[peaks[max_right]]);

            std::cout << "Adding (" << peaks[left] << "," << bars[peaks[left]] << ") to ("
                << peaks[max_right] << "," << bars[peaks[max_right]] << ")" << std::endl;

            for (idx = peaks[left] + 1 ; idx < peaks[max_right] ; idx++) {
                if (height > bars[idx])
                    space += ( height - bars[idx] );
            } // for

            left = max_right;
            right = left + 1;
        } // while

        if (right < peaks_size) {
            int height = std::min(bars[peaks[left]], bars[peaks[right]]);

            for (idx = peaks[left] + 1 ; idx < peaks[right] ; idx++) {
                if (height > bars[idx])
                    space += ( height - bars[idx] );
            } // for
        } // if

        return space;
    } // else
}
