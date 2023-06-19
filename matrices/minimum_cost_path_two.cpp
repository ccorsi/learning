/**
 * @file minimum_cost_path_two.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=MinimumCostPathII
 * @version 0.1
 * @date 2023-06-19
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "minimum_cost_path_two.h"

namespace valhalla {
    namespace matrices {
        namespace minimum_cost_path_two {
            /*

            Given an `N × N` matrix of non-negative integers, where each cell of the
            matrix (i, j) indicates the direct flight cost from the city `i` to city `j`.
            The task is to find the minimum cost to reach the destination city `N-1`
            from the source city 0.

            Input:

            mat = [
                [0,   20, 30, 100],
                [20,  0,  15, 75 ],
                [30,  15, 0,  50 ],
                [100, 75, 50, 0  ]
            ]

            Output: 80

            Explanation: The minimum cost is 80 and the minimum cost path is:

            city 0 —> city 2 (cost = 30)
            city 2 —> city 3 (cost = 50)


            Input:

            mat = [
                [0,  25, 20, 10, 105],
                [20, 0,  15, 80, 80 ],
                [30, 15, 0,  70, 90 ],
                [10, 10, 50, 0,  100],
                [40, 50, 5,  10, 0  ]
            ]

            Output: 100

            Explanation: The minimum cost is 100 and the minimum cost path is:

            city 0 —> city 3 (cost = 10)
            city 3 —> city 1 (cost = 10)
            city 1 —> city 4 (cost = 80)

            */

            int Solution::findMinCost(std::vector<std::vector<int>> const & cost) {
                int min = -1;



                return min;
            } // findMinCost
        }
    }
}
