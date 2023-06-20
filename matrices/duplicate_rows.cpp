/**
 * @file duplicate_rows.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=DuplicateRows
 * @version 0.1
 * @date 2023-06-20
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "duplicate_rows.h"

namespace valhalla {
    namespace matrices {
        namespace duplicate_rows {
            /*

            Find duplicate rows present in a given binary matrix by traversing the matrix
            only once.

            Input:

            mat = [
                [1, 0, 0, 1, 0],
                [0, 1, 1, 0, 0],
                [1, 0, 0, 1, 0],
                [0, 0, 1, 1, 0],
                [0, 1, 1, 0, 0]
            ]

            Output: {3, 5}

            Explanation: Row #3 is duplicate of row #1 and row #5 is duplicate of row #2

            */

            std::unordered_set<int> Solution::findDuplicateRows(std::vector<std::vector<int>> const & mat) {
                std::unordered_set<int> duplicates;



                return duplicates;
            } // findDuplicateRows
        }
    }
}
