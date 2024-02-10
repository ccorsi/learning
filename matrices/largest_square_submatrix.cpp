/**
 * @file largest_square_submatrix.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=LargestSquareSubmatrix
 * @version 0.1
 * @date 2023-06-01
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <iostream>

#include "largest_square_submatrix.h"

namespace valhalla {
    namespace matrices {
        namespace largest_square_submatrix {
            /*

            Given a binary matrix, find size of the largest square submatrix, which is
            surrounded by all 1’s.

            Input:
            [
                [1, 1, 1, 1, 1, 1],
                [1, 0, 1, 1, 0, 1],
                [0, 1, 1, 0, 0, 1],
                [1, 1, 1, 1, 1, 1],
                [1, 0, 0, 1, 0, 1],
                [1, 0, 1, 1, 0, 0],
                [1, 0, 1, 0, 1, 1],
                [1, 1, 1, 0, 1, 1]
            ]

            Output: 4

            Explanation: The size of the largest square submatrix in the following binary
            matrix is 4. The largest square submatrix is formed by cells (0, 2), (3, 2),
            (0, 5), and (3, 5).

            */

            int Solution::findLargestSquareMatrix(std::vector<std::vector<int>> const & mat) {
                for (auto row : mat) {
                    for (auto value : row)
                        std::cout << " " << value;
                    std::cout << "\n";
                }
                if (mat.empty()) {
                    return 0;
                }
                int largest = 0;
                const size_t rows = mat.size(), cols = mat[0].size(), last = std::min(rows,cols);

                // Solution 1:  Start at the top-left and move towards the bottom-right.  We use
                //              the idea that we will create square entries moving to the right
                //              and towards the bottom.  We then think about the comparing the
                //              largest current square with the current state of the comparison.
                //              This should simplify the algorithm.

                for (size_t row = 0 ; row + largest < rows ; row++) {
                    for (size_t col = 0 ; col + largest < cols ; col++) {
                        if (mat[row][col] == 1) {
                            // top-left corner
                            size_t cur = 0;
                            // determine the largest possible square for the given row,col start
                            while (row+cur+1 < rows && col+cur+1 < cols && mat[row][col+cur+1] == 1 && mat[row+cur+1][col] == 1) {
                                cur++;
                            }
                            // determine if a square is possible
                            if (cur > 0) {
                                while (cur > 0 && cur+1 > largest) {
                                    size_t end = 0;
                                    // check the row entries
                                    while (end < cur && mat[row+cur][col+end+1] == 1) {
                                        end++;
                                    }
                                    if (end == cur) {
                                        end = 0;
                                        while (end < cur && mat[row+end+1][col+cur] == 1) {
                                            end++;
                                        }
                                        if (end == cur) {
                                            std::cout << "Found square at (" << row << "," << col << "), (" << (row + cur) << "," << col << "), (" << row << "," << (col + cur) << "), (" << (row+cur) << "," << (col+cur) << ")\n";
                                            if (cur+1 > largest) {
                                                std::cout << "Found LARGEST square at (" << row << "," << col << "), (" << (row + cur) << "," << col << "), (" << row << "," << (col + cur) << "), (" << (row+cur) << "," << (col+cur) << ")\n";
                                                largest = static_cast<int>(cur+1);
                                                // we are done break out of the while loop
                                                break;
                                            }
                                        }
                                    }
                                    cur--;
                                } // while (cur > 0 && cur > largest)
                            } else if (largest == 0) {
                                std::cout << "Found LARGEST square at (" << row << "," << col << "), (" << (row + cur) << "," << col << "), (" << row << "," << (col + cur) << "), (" << (row+cur) << "," << (col+cur) << ")\n";
                                largest = 1;
                            } // (cur != 0)
                        } // if (mat[row][col] == 1)
                    } // for (size_t col =...)
                } // for (size_t row =...)

                return largest;
            } // findLargestSquareMatrix
        }
    }
}
