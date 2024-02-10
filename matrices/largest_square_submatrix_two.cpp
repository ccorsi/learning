/**
 * @file largest_square_submatrix_two.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=LargestSquareSubmatrixII
 * @version 0.1
 * @date 2023-06-01
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "largest_square_submatrix_two.h"

namespace valhalla {
    namespace matrices {
        namespace largest_square_submatrix_two {
            /*

            Given an `M × N` binary matrix, find the size of the largest square submatrix of 1’s in it.

            Input:

            [
                [0, 0, 1, 0, 1, 1],
                [0, 1, 1, 1, 0, 0],
                [0, 0, 1, 1, 1, 1],
                [1, 1, 0, 1, 1, 1],
                [1, 1, 1, 1, 1, 1],
                [1, 1, 0, 1, 0, 1],
                [1, 0, 1, 1, 1, 1],
                [1, 1, 1, 0, 1, 1]
            ]

            Output: 3

            Explanation: The largest square submatrix of 1’s is marked below by `x`.

                0  0  1  0  1  1
                0  1  1  1  0  0
                0  0  1  x  x  x
                1  1  0  x  x  x
                1  1  1  x  x  x
                1  1  0  1  0  1
                1  0  1  1  1  1
                1  1  1  0  1  1

            */

            int Solution::findLargestSquareSubmatrix(std::vector<std::vector<int>> const & mat) {
                if (mat.empty()) {
                    return 0;
                }

                int largest = 0;
                const size_t rows = mat.size(), cols = mat[0].size();

                // Solution 1:  We look for the first 1 then we look for the first 0 or the end of the
                //              matrix.  After that we can compare the largest square with the currently
                //              found one.  If it is larger, replace it.  If not, move to the column of
                //              the first 0 we found or the end of the current row's column.
                for (size_t row = 0 ; row + largest < rows ; row++) {
                    for (size_t col = 0 ; col + largest < cols ; col++) {
                        // Check if the current row/col has a 1
                        if (mat[row][col] == 1) {
                            size_t cur = 0;
                            // check if the next row and column has a 1
                            while (row+cur+1 < rows && col+cur+1 < cols && mat[row][col+cur+1] == 1 && mat[row+cur+1][col] == 1) {
                                // check if the rest of the row and col entries contains a 1
                                const size_t crow = row+cur+1, ccol = col+cur+1, last = cur+1;
                                size_t cnt = 1;
                                // check if this current row/column completes the square
                                while (cnt < last && mat[crow][col+cnt] == 1 && mat[row+cnt][ccol] == 1) {
                                    cnt++;
                                }
                                if (cnt != last || mat[crow][ccol] != 1) {
                                    // this current row/column doesn't complete the square thus exit the while loop
                                    break;
                                }
                                cur++;
                            } // while (row+cur+1 < rows &&...
                            if (cur > 0) {
                                if (cur+1 > largest) {
                                    largest = static_cast<int>(cur+1);
                                }
                                // increment col by cur because the next largest square cannot be found within [col,col+cur]
                                col += cur;
                            } else if (largest == 0) {
                                // a square of a single 1 is a square
                                largest = 1;
                            } // if (cur > 0)
                        } // if (mat[row][col] == 1...
                    }
                } // for (size_t row = 0...
                return largest;
            } // findLargestSquareSubmatrix
        }
    }
}
