/**
 * @file trapping_rain_water.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=TrappingRainWater
 * @version 0.1
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

int valhalla::arrays::trapping_rain_water::Solution::trapWater(std::vector<int> const & bars) {
    return -1;
}
