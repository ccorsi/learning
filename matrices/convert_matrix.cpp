/**
 * @file convert_matrix.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=ConvertMatrix
 * @version 0.1
 * @date 2023-02-22
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "convert_matrix.h"

/*

Give an `M × N` binary matrix, change all elements of row `i` and column `j` to 0 if cell (i, j) has value 0.

Input:
[
	[1, 1, 0, 1, 1],
	[1, 1, 1, 1, 1],
	[1, 1, 1, 0, 1],
	[1, 1, 1, 1, 1],
	[0, 1, 1, 1, 1]
]

Output:
[
	[0, 0, 0, 0, 0],
	[0, 1, 0, 0, 1],
	[0, 0, 0, 0, 0],
	[0, 1, 0, 0, 1],
	[0, 0, 0, 0, 0]
]

Explanation:

0’s are present at (0, 2), (4, 0), and (2, 3) in the input matrix. Therefore, every element of the following cells is changed to 0:

• row 0 and column 2
• row 4 and column 0
• row 2 and column 3

*/

void valhalla::matrices::convert_matrix::Solution::convertMatrix(std::vector<std::vector<int>> & mat) {
    std::vector<std::pair<int,int>> zeros;

    for(int row = 0 ; row < mat.size() ; row++) {
        for(int col = 0 ; col < mat[row].size() ; col++) {
            if (mat[row][col] == 0) zeros.push_back(std::pair<int,int>(row,col));
        } // for
    } // for

    for (std::pair<int,int> indice : zeros) {
        // set all columns to zero for given row
        for(int col = 0; col < mat[indice.first].size() ; col++) {
            mat[indice.first][col] = 0;
        } // for
        // sel all rows to zero for given column
        for(int row = 0 ; row < mat.size() ; row++) {
            mat[row][indice.second] = 0;
        } // for
    } // for
}
