/**
 * @file symmetric_pairs.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=SymmetricPairs
 * @version 0.1
 * @date 2023-03-23
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */


#include "symmetric_pairs.h"

namespace valhalla {
    namespace arrays {
        namespace symmetric_pairs {
            /*

            Given a set of pairs of integers, find all symmetric pairs, i.e., pairs that mirror each other.
            For instance, pairs `(x, y)` and `(y, x)` are mirrors of each other.

            Input : {(1, 2), (5, 2), (3, 4), (7, 10), (4, 3), (2, 5)}
            Output: {{(2, 5), (5, 2)}, {(3, 4), (4, 3)}}
            Explanation: The pairs (2, 5) and (5, 2) mirror each other. Similarly, pairs (3, 4) and (4, 3)
            are symmetric.

            Input : {(1, 2), (5, 2), (3, 4)}
            Output: {}
            Explanation: No pairs mirror each other

            */

            std::set<std::set<std::pair<int,int>>> Solution::findSymmetricPairs(std::set<std::pair<int,int>> const & pairs) {
                std::set<std::set<std::pair<int,int>>> symmetric_pairs;

                for (std::pair<int,int> pnt : pairs) {
                    std::pair<int,int> sym(pnt.second, pnt.first);

                    if (pairs.find(sym) != pairs.end()) {
                        std::set<std::pair<int,int>> value = { pnt, sym };
                        symmetric_pairs.insert(value);
                    } // if
                } // for

                return symmetric_pairs;
            } // findSymmetricPairs
        }
    }
}
