/**
 * @file maximum_sub_submatrix_two.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=MaximumSumSubmatrixII
 * @version 0.1
 * @date 2023-06-20
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <climits>

#include "maximum_sum_submatrix_two.h"

namespace valhalla {
    namespace matrices {
        namespace maximum_sum_submatrix_two {

            void Solution::check(std::vector<std::vector<int>> const & mat, const int rk, const int ck,
                                 int & max_sum, std::pair<int,int> & max_point, std::pair<int,int> & max_length) {

                if (mat.empty() || rk > mat.size() || ck > mat[0].size()) {
                    return;
                } // if (mat.empty() || rk > mat.size() || ck > mat[0].size())

                std::vector<std::vector<int>> rowSums;

                for (auto row : mat) {
                    rowSums.push_back(std::vector<int>());
                    auto & next = rowSums.back();
                    int sum = 0;
                    auto col = 0;
                    for ( ; col < ck ; col++ ) {
                        sum += row[col];
                    } // for ( ; col < ck ; col++ )
                    next.push_back(sum);
                    for ( ; col < row.size() ; col++ ) {
                        sum += row[col];
                        sum -= row[col-ck];
                        next.push_back(sum);
                    } // for ( ; col < row.size() ; col++ )
                } // for (auto row : mat)

                for (auto col = 0 ; col < rowSums[0].size() ; col++) {
                    int sum = 0;
                    auto row = 0;
                    for ( ; row < rk ; row++ ) {
                        sum += rowSums[row][col];
                    } // for ( ; row < rk ; row++ )
                    if (sum > max_sum) {
                        max_sum = sum;
                        max_point = std::pair(0,col);
                        max_length = std::pair(rk,ck);
                    } // if (sum > max_sum)
                    for ( ; row < rowSums.size() ; row++ ) {
                        sum += rowSums[row][col];
                        sum -= rowSums[row-rk][col];
                        if (sum > max_sum) {
                            max_sum = sum;
                            max_point = std::pair(row-rk+1,col);
                            max_length = std::pair(rk,ck);
                        } // if (sum > max_sum)
                    } // for ( ; row < mat.size() ; row++ )
                } // for (auto col = 0 ; col < mat[0].size() ; col++)
            } // check

            /*

            Given an `N × N` matrix, find the maximum sum submatrix present in it.

            Input:

            mat = [
                [-5, -6, 3, 1, 0],
                [9, 7, 8, 3, 7],
                [-6, -2, -1, 2, -4],
                [-7, 5, 5, 2, -6],
                [3, 2, 9, -5, 1]
            ]

            Output:

            [
                [7, 8, 3],
                [-2, -1, 2],
                [5, 5, 2],
                [2, 9, -5]
            ]

            In case the multiple maximum sum submatrix exists, the solution can return
            any one of them.

            */

            std::vector<std::vector<int>> Solution::findMaxSumSubmatrix(std::vector<std::vector<int>> const & mat) {
                std::vector<std::vector<int>> max;

                if (mat.empty()) {
                    return max;
                } // if (mat.empty())

                const auto rows = mat.size(), cols = mat[0].size();
                int max_sum = mat[0][0];
                std::pair<int,int> point(0,0), length(1,1);

                // Solution 1:  This solution will just cycle through the different matrix sizes that could be
                //              the maximum value for the passed matrix.  NOTE: this seems like an inefficient
                //              solution that should be improved somehow using caching and/or slowly combining
                //              summed submatrices.

                for (auto rk = 0 ; rk < rows ; rk++) {
                    for (auto ck = 0 ; ck < cols ; ck++) {
                        check(mat, rk + 1, ck + 1, max_sum, point, length);
                    } // for (auto scol = 1 ; scol <= cols ; scol++)
                } // for (auto srow = 1 ; srow <= rows ; srow++)

                int row = point.first, col = point.second;
                const int rlen = length.first, clen = length.second;

                for (auto r = 0 ; r < rlen ; r++) {
                    std::vector<int> entries;
                    for (auto c = 0 ; c < clen ; c++) {
                        entries.push_back(mat[row+r][col+c]);
                    } // for (auto c = 0 ; c < clen ; c++)
                    max.push_back(entries);
                } // for (auto r = 0 ; r < rlen ; r++)

                return max;
            } // findMaxSumSubmatrix
        }
    }
}
