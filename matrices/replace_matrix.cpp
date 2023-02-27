/**
 * @file replace_matrix.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=ReplaceMatrix
 * @version 0.1
 * @date 2023-02-24
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <iostream>
#include <utility>
#include <set>

#include "replace_matrix.h"

/*

Given an `M × N` binary matrix, replace all occurrences of 0’s by 1’s, which are not completely surrounded
by 1’s from all sides, i.e., top, left, bottom, right, top-left, top-right, bottom-left, and bottom-right.

Input:

[
	[1, 1, 1, 1, 0, 0, 1, 1, 0, 1],
	[1, 0, 0, 1, 1, 0, 1, 1, 1, 1],
	[1, 0, 0, 1, 1, 1, 1, 1, 1, 1],
	[1, 1, 1, 1, 0, 0, 1, 1, 0, 1],
	[1, 1, 1, 1, 0, 0, 0, 1, 0, 1],
	[1, 1, 0, 1, 1, 0, 1, 1, 0, 0],
	[1, 1, 0, 1, 1, 1, 1, 1, 1, 1],
	[1, 1, 0, 1, 1, 0, 0, 1, 0, 1],
	[1, 1, 1, 0, 1, 0, 1, 0, 0, 1],
	[1, 1, 1, 0, 1, 1, 1, 1, 1, 1]
]

Output:

[
	[1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
	[1, 0, 0, 1, 1, 1, 1, 1, 1, 1],
	[1, 0, 0, 1, 1, 1, 1, 1, 1, 1],
	[1, 1, 1, 1, 0, 0, 1, 1, 1, 1],
	[1, 1, 1, 1, 0, 0, 0, 1, 1, 1],
	[1, 1, 1, 1, 1, 0, 1, 1, 1, 1],
	[1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
	[1, 1, 1, 1, 1, 0, 0, 1, 0, 1],
	[1, 1, 1, 1, 1, 0, 1, 0, 0, 1],
	[1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
]

*/

void valhalla::matrices::replace_matrix::Solution::replaceZeroes(std::vector<std::vector<int>> & mat) {
    if (mat.empty() || mat[0].empty()) return;

    std::set<std::pair<std::vector<int>::size_type,std::vector<int>::size_type>> replace;
    std::pair<std::vector<int>::size_type,std::vector<int>::size_type> entry;

    const std::vector<int>::size_type rows = mat.size(),
        cols = mat[0].size();

    // check the first row of the matrix
    for (std::vector<int>::size_type col = 0 ; col < cols ; col++) {
        if (mat[0][col] == 0) {
            mat[0][col] = 1;
            // check the above row except if it is the last row of the matrix
            if (rows > 2) {
                entry.first = 1;
                if (col > 0 && col + 1 < cols && mat[1][col] == 0) {
                    entry.second = col;
                    replace.insert(entry);
                } // if
                // check the right column except for the last column
                if (col + 2 < cols && mat[1][col+1] == 0) {
                    entry.second = col + 1;
                    replace.insert(entry);
                } // if
                // check the left column except for the first column
                if (col > 1 && mat[1][col-1] == 0) {
                    entry.second = col - 1;
                    replace.insert(entry);
                } // if
            } // if
        } // if
    } // for

    // check the first and last column of the matrix except for the first and last row first and last column
    for (std::vector<int>::size_type row = 1 ; row < rows - 1 ; row++) {
        // Check the first entry in the row
        if (mat[row][0] == 0) {
            mat[row][0] = 1;
            // check the second column except for the last column
            if (cols > 2) {
                entry.second = 1;
                // check the next column on the checked row
                if (mat[row][entry.second] == 0) {
                    entry.first = row;
                    replace.insert(entry);
                } // if
                // check the prior row except for the first row
                if (rows > 2 && mat[row-1][entry.second] == 0) {
                    entry.first = row - 1;
                    replace.insert(entry);
                } // if
                // check the next row except for the last row
                if (row + 2 < rows && mat[row+1][entry.second] == 0) {
                    entry.first = row + 1;
                    replace.insert(entry);
                } // if
            } // if
        } // if
        // Check the last entry in the row except for the first column
        if (cols > 1) {
            if (mat[row][cols-1] == 0) {
                mat[row][cols-1] = 1;
                // check the before last entry in the row except for the first two columns
                if (cols > 3) {
                    entry.second = cols - 2;
                    // check the prior column on the checked row
                    if (mat[row][entry.second] == 0) {
                        entry.first = row;
                        replace.insert(entry);
                    } // if
                    // check the prior row except for the first two rows
                    if (rows > 3 && mat[row-1][entry.second] == 0) {
                        entry.first = row - 1;
                        replace.insert(entry);
                    } // if
                    // check the next row except for the last row and the first two rows
                    if (row + 3 < rows && mat[row+1][entry.second] == 0) {
                        entry.first = row + 1;
                        replace.insert(entry);
                    } // if
                } // if
            } // if
        } // if
    } // for

    // check the last row of the matrix
    for (std::vector<int>::size_type col = 0 ; col < cols ; col++) {
        entry.first = rows - 1;
        if (mat[entry.first][col] == 0) {
            mat[entry.first][col] = 1;
            // check the before last row of the matrix except for the first two rows
            if (rows > 3) {
                entry.first = rows - 2;
                // check the entry below the current column
                if (mat[entry.first][col] == 0) {
                    entry.second = col;
                    replace.insert(entry);
                } // if
                // check the entry below and to the left of the current column
                if (col > 0 && mat[entry.first][col-1] == 0) {
                    entry.second = col - 1;
                    replace.insert(entry);
                }  // if
                // check the entry below and to the right of the current column
                if (col + 1 < cols && mat[entry.first][col+1] == 0) {
                    entry.second = col + 1;
                    replace.insert(entry);
                }  // if
            } // if
        } // if
    } // for

    while ( ! replace.empty() ) {
        entry = *(replace.begin()); // get a reference to the next point
        replace.erase(entry); // remove the referenced point from the set
        mat[entry.first][entry.second] = 1; // set the entry to 1
        // check if any of its surrounding entries are 0
        if (mat[entry.first-1][entry.second-1] == 0)
            replace.insert(std::pair(entry.first-1,entry.second-1));
        if (mat[entry.first-1][entry.second] == 0)
            replace.insert(std::pair(entry.first-1,entry.second));
        if (mat[entry.first-1][entry.second+1] == 0)
            replace.insert(std::pair(entry.first-1,entry.second+1));
        if (mat[entry.first][entry.second-1] == 0)
            replace.insert(std::pair(entry.first,entry.second-1));
        if (mat[entry.first][entry.second+1] == 0)
            replace.insert(std::pair(entry.first,entry.second+1));
        if (mat[entry.first+1][entry.second-1] == 0)
            replace.insert(std::pair(entry.first+1,entry.second-1));
        if (mat[entry.first+1][entry.second] == 0)
            replace.insert(std::pair(entry.first+1,entry.second));
        if (mat[entry.first+1][entry.second+1] == 0)
            replace.insert(std::pair(entry.first+1,entry.second+1));
    } // for
}
