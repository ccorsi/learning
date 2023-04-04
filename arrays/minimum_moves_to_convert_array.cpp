/**
 * @file minimum_moves_to_convert_array.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=MinimumMovesToConvertArray
 * @version 0.1
 * @date 2023-04-03
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */


#include "minimum_moves_to_convert_array.h"

namespace valhalla {
    namespace arrays {
        namespace minimum_moves_to_convert_array {
            /*

            Find the minimum number of moves required for converting an array of zeroes
            to a given array of non-negative integers using only increment and double
            operations. The increment operation increases the value of an array element
            by 1 and the double operation doubles the value of each array element.

            Input: [8, 9, 8]
            Output: 7

            Explanation: The optimal sequence to convert an array [0, 0, 0] to [8, 9, 8]
            requires 3 increment operations, followed by 3 double operations, and a
            single increment operation:

            [0, 0, 0] —> [1, 0, 0] —> [1, 1, 0] —> [1, 1, 1] —> [2, 2, 2] —> [4, 4, 4] —> [8, 8, 8] —> [8, 9, 8]

            */

            int Solution::findMinMoves(std::vector<int> & nums) {
                const int size = nums.size();
                int min = 0;

                while (true) {
                    int sum = 0;

                    for (int value : nums) {
                        if (value != 0) {
                            sum = value;
                            break;
                        } // if
                    } // for

                    if (sum == 0) break;

                    bool multiple = false;

                    for (int idx = 0 ; idx < size ; idx++) {
                        if (nums[idx] == 0) {
                            continue;
                        }

                        min += nums[idx] % 2;

                        nums[idx] /= 2;

                        multiple = (multiple || nums[idx] != 0);

                    } // for

                    if ( multiple ) {
                        min++;
                    } // if
                } // while

                return min;
            } // findMinMoves
        }
    }
}
