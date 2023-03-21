/**
 * @file geometric_triplets.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=GeometricTriplets
 * @version 0.1
 * @date 2023-03-20
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */


#include "geometric_triplets.h"

namespace valhalla {
    namespace arrays {
        namespace geometric_triplets {
            /*

            Given a sorted array of distinct positive integers, return all triplets that
            forms a geometric progression with an integral common ratio. A geometric
            progression is a sequence of numbers where each term after the first is
            found by multiplying the previous one by a fixed, non-zero number called the
            common ratio.

            Input : [1, 2, 6, 10, 18, 54]
            Output: {[2, 6, 18], [6, 18, 54]}

            Input : [2, 8, 10, 15, 16, 30, 32, 64]
            Output: {[2, 8, 32], [8, 16, 32], [16, 32, 64]}

            Input : [1, 2, 6, 18, 36, 54]
            Output: {[2, 6, 18], [1, 6, 36], [6, 18, 54]}

            Input : [1, 2, 4, 16]
            Output: {[1, 2, 4], [1, 4, 16]}

            Input : [1, 2, 3, 6, 18, 22]
            Output: {[2, 6, 18]}

            */

            std::set<std::vector<int>> Solution::findTriplets(std::vector<int> const & nums) {
                std::set<std::vector<int>> triplets;

                const int size = nums.size();

                if (size > 2) {
                    for (int idx_1 = 0 ; idx_1 < size ; idx_1++) {
                        for (int idx_2 = idx_1 + 1 ; idx_2 < size ; idx_2++) {
                            int multiple = nums[idx_2] / nums[idx_1];
                            if (nums[idx_1] * multiple == nums[idx_2]) {
                                for (int idx_3 = idx_2 + 1 ; idx_3 < size ; idx_3++) {
                                    if (nums[idx_2] * multiple == nums[idx_3]) {
                                        std::vector<int> triplet = {
                                            nums[idx_1], nums[idx_2], nums[idx_3]
                                        };
                                        triplets.insert(triplet);
                                    } // if
                                } // for
                            } // if
                        } // for
                    } // for
                } // if

                return triplets;
            } // findTriplets
        }
    }
}
