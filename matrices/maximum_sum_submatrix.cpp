/**
 * @file maximum_sub_submatrix.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=MaximumSumSubmatrix
 * @version 0.1
 * @date 2023-06-20
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <utility>
#include <climits>

#include "maximum_sum_submatrix.h"

namespace valhalla {
    namespace matrices {
        namespace maximum_sum_submatrix {
            /*

            Given an `M × N` integer matrix, calculate the maximum sum submatrix of size `k × k` in it.

            Input:

            mat = [
                [ 3, -4,  6, -5,  1],
                [ 1, -2,  8, -4, -2],
                [ 3, -8,  9,  3,  1],
                [-7,  3,  4,  2,  7],
                [-3,  7, -5,  7, -6]
            ]

            • If k = 2, then

            Output:
            [
                [9, 3],
                [4, 2]
            ]

            • If k = 3, then

            Output:
            [
                [8, -4, -2],
                [9,  3,  1],
                [4,  2,  7]
            ]

            In case the multiple `k × k` submatrix exists with the maximum sum, the solution can return
            any one of them.

            */

            std::vector<std::vector<int>> Solution::findMaxSumSubmatrix(std::vector<std::vector<int>> const & mat, int k) {
                std::vector<std::vector<int>> max;

                if (mat.empty() || k > mat.size()) {
                    return max;
                } // if (mat.empty() || k > mat.size())

                std::vector<std::vector<int>> rowSums;

                for (auto row : mat) {
                    rowSums.push_back(std::vector<int>());
                    auto & next = rowSums.back();
                    int sum = 0;
                    auto col = 0;
                    for ( ; col < k ; col++ ) {
                        sum += row[col];
                    } // for ( ; col < k ; col++ )
                    next.push_back(sum);
                    for ( ; col < row.size() ; col++ ) {
                        sum += row[col];
                        sum -= row[col-k];
                        next.push_back(sum);
                    } // for ( ; col < row.size() ; col++ )
                } // for (auto row : mat)

                std::pair<int,int> point(-1,-1);
                int max_sum = INT_MIN;

                for (auto col = 0 ; col < rowSums[0].size() ; col++) {
                    int sum = 0;
                    auto row = 0;
                    for ( ; row < k ; row++ ) {
                        sum += rowSums[row][col];
                    } // for ( ; row < k ; row++ )
                    if (sum > max_sum) {
                        max_sum = sum;
                        point = std::pair(0,col);
                    } // if (sum > max_sum)
                    for ( ; row < rowSums.size() ; row++ ) {
                        sum += rowSums[row][col];
                        sum -= rowSums[row-k][col];
                        if (sum > max_sum) {
                            max_sum = sum;
                            point = std::pair(row-k+1,col);
                        } // if (sum > max_sum)
                    } // for ( ; row < mat.size() ; row++ )
                } // for (auto col = 0 ; col < mat[0].size() ; col++)

                for ( auto row = 0 ; row < k ; row++ ) {
                    max.push_back(std::vector<int>());
                    for ( auto col = 0 ; col < k ; col++ ) {
                        max[row].push_back(mat[point.first+row][point.second+col]);
                    } // for ( auto col = 0 ; col < k ; col++ )
                } // for ( auto row = 0 ; row < k ; row++ )

                return max;
            } // findMaxSumSubmatrix
        }
    }
}
