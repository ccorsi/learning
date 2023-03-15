/**
 * @file rotate_matrix_two.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=RotateMatrixII
 * @version 0.1
 * @date 2023-01-04
 * 
 * @copyright Copyright (c) 2023 Claudio Corsi
 * 
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "rotate_matrix_two.h"

/*

Given an `N × N` integer matrix, rotate the matrix by 180 degrees in a clockwise direction. The transformation should be done in-place in quadratic time.

Input:

[
	[1,  2,  3,  4],
	[5,  6,  7,  8],
	[9,  10, 11, 12],
	[13, 14, 15, 16]
]

Output:

[
	[16, 15, 14, 13],
	[12, 11, 10, 9],
	[8,  7,  6,  5],
	[4,  3,  2,  1]
]

*/

/*
    2x2 ==> ( 2 - 1 ) * 2 = 2
    3x3 ==> ( 3 - 1 ) * 2 = 4
    4x4 ==> ( 4 - 1 ) * 2 = 6
    5x5 ==> ( 5 - 1 ) * 2 = 8
    6x6 ==> ( 6 - 1 ) * 2 = 10
    7x7 ==> ( 7 - 1 ) * 2 = 12
    8x8 ==> ( 8 - 1 ) * 2 = 14
    9x9 ==> ( 9 - 1 ) * 2 = 16

    9x9 ==> 7x7 ==> 5x5 ==> 3x3
     16 ==>  12 ==>   8 ==>   4

    8x8 ==> 6x6 ==> 4x4 ==> 2x2
     14 ==>  10 ==>   6 ==>   2

    7x7 ==> 5x5 ==> 3x3
     12 ==>   8 ==>   4

    6x6 ==> 4x4 ==> 2x2
     10 ==>   6 ==> 2

    5x5 ==> 3x3
      8 ==>   4
*/
void valhalla::matrices::rotate_matrix_two::Solution::rotate(std::vector<std::vector<int>> &mat) {
    std::vector<int>::size_type size = mat.size();

    if (size < 2) {
        // there is nothing to do so just return
        return;
    }

    std::vector<int>::size_type steps = ( size - 1 ) * 2;
    std::vector<int>::size_type rtop = 0, ctop = 0, rbot = size - 1, cbot = size - 1;

    while (rtop < rbot) {
        for(std::vector<int>::size_type step = 0 ; step < steps ; step++) {
            std::vector<int>::size_type currow = rtop, curcol = ctop + step;

            // correct the curcol and currow if step is too large
            if (curcol > cbot) {
                currow += (curcol - cbot);
                curcol = cbot;
            }

            std::vector<int>::size_type nextrow = rbot, nextcol = cbot;

            // correct the nextrow and nextcol if steps too large
            if (step > ( cbot - ctop )) {
                // update the nextrow and nextcol
                nextrow -= ( step + ctop - cbot );
                nextcol = ctop;
            } else {
                // update the nextcol only
                nextcol -= step;
            } // else

            // swap the values
            int temp = mat[nextrow][nextcol];
            mat[nextrow][nextcol] = mat[currow][curcol];
            mat[currow][curcol] = temp;

        } // for

        // reduce the size of the square
        rtop++; ctop++; rbot--; cbot--;
        // reduce the steps by 4
        steps -= 4;
    } // while

}