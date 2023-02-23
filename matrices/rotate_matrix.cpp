/**
 * @file rotate_matrix.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief 
 * @version 0.1
 * @date 2023-01-02
 * 
 * @copyright Copyright (c) 2023 Claudio Corsi
 * 
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "rotate_matrix.h"

/*

Given an `N × N` integer matrix, rotate the matrix by 90 degrees in a clockwise direction. The transformation should be done in-place and in quadratic time.

Input:

[
	[1,  2,  3,  4],
	[5,  6,  7,  8],
	[9,  10, 11, 12],
	[13, 14, 15, 16],
]

Output:

[
	[13, 9,  5, 1],
	[14, 10, 6, 2],
	[15, 11, 7, 3],
	[16, 12, 8, 4]
]

Input:

[
    [ 1,  2,  3,  4,  5],
    [ 6,  7,  8,  9, 10],
    [11, 12, 13, 14, 15],
    [16, 17, 18, 19, 20],
    [21, 22, 23, 24, 25]
]

Output:

[
    [21, 16, 11,  6,  1],
    [22, 17, 12,  7,  2],
    [23, 18, 13,  8,  3],
    [24, 19, 14,  9,  4],
    [25, 20, 15, 10,  5]
]
*/

#include <iostream>

using std::cout;
using std::endl;

#include <iostream>

std::ostream& operator<<(std::ostream& out, const std::vector<int> &values) {
    out << "[";

    for(int value : values) {
        out << " " << value;
    }

    out << ((values.empty()) ? "]" : " ]") << std::endl;

    return out;
}

std::ostream& operator<<(std::ostream& out, const std::vector<std::vector<int>> &values) {
    out << "[" << std::endl;

    for(std::vector<int> value : values) {
        cout << " " << value;
    }

    if (! values.empty()) out << std::endl;

    out << "]";

    return out;
}

void valhalla::matrices::rotate_matrix::Solution::rotate(std::vector<std::vector<int>> &mat) {
    cout << "Processing matrix: " << mat << endl;
    std::vector<std::vector<int>>::size_type steps = mat.size();

    cout << "steps: " << steps << endl;
    if (steps < 2) return; // nothing to do

    // decrement the steps by one
    steps--;

    // we need to perform a smart set of steps here

    std::vector<std::vector<int>>::size_type rtop, ctop, rbot, cbot;

    rtop = ctop = 0;
    rbot = cbot = steps;

    cout << "Initial: [rtop,ctop]: [" << rtop << "," << ctop << "], [rbot,cbot]: [" << rbot << "," << cbot << "], steps: " << steps << endl;
    while (rtop < rbot) {

        cout << "[rtop,ctop]: [" << rtop << "," << ctop << "], [rbot,cbot]: [" << rbot << "," << cbot << "], steps: " << steps << endl;
        for(std::vector<std::vector<int>>::size_type step = 0 ; step < steps ; step++) {
            std::vector<std::vector<int>>::size_type currow = rtop, curcol = ctop + step;
            int temp; // holds the currently replacing value to be passed to next

            // move the entries around the outer square
            int next = mat[currow][curcol]; // store value to be moved
            cout << "[rtop,ctop]: [" << rtop << "," << ctop << "], step: " << step << ", [currow,curcol]: [" << currow << "," << curcol << "], next: " << next << endl;

            // perform the first shift
            curcol += steps;
            if (curcol > cbot) {
                currow += curcol - cbot;
                curcol = cbot;
            }

            cout << "1 - [currow,curcol]: [" << currow << "," << curcol << "], next: " << next << endl;
            // move value
            temp = mat[currow][curcol];
            mat[currow][curcol] = next;
            next = temp;

            // perform the second shift
            currow += steps;
            if (currow > rbot) {
                curcol = cbot + rbot - currow;
                currow = rbot;
            }

            cout << "2 - [currow,curcol]: [" << currow << "," << curcol << "], next: " << next << endl;
            // move value
            temp = mat[currow][curcol];
            mat[currow][curcol] = next;
            next = temp;

            // perform the third shift
            if (ctop + steps > curcol) {
                currow -= ( ctop + steps - curcol );
                curcol = ctop;
            } else {
                curcol -= steps;
            }

            cout << "3 - [currow,curcol]: [" << currow << "," << curcol << "], next: " << next << endl;
            // move value
            temp = mat[currow][curcol];
            mat[currow][curcol] = next;
            next = temp;

            // perform the fourth and last shift
            if (rtop + steps > currow) {
                curcol += ( rtop + steps - currow );
                currow = rtop;
            } else {
                currow -= steps;
            }

            cout << "4 - [currow,curcol]: [" << currow << "," << curcol << "], next: " << next << endl;
            // move value
            temp = mat[currow][curcol];
            mat[currow][curcol] = next;
            next = temp;
        } // for

        // narrow the square to be rotated 90 degrees
        rtop++; ctop++; rbot--; cbot--;
        // reduce the steps size by 2
        steps -= 2;

        cout << "Rotated: " << mat << endl;
    } // while
}