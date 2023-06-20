/**
 * @file boggle_search.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=BoggleSearch
 * @version 0.1
 * @date 2023-06-20
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "boggle_search.h"

namespace valhalla {
    namespace matrices {
        namespace boggle_search {
            /*

            Given an `M × N` boggle board, find a list of all possible words that can be formed
            by a sequence of adjacent characters on the board.

            You are allowed to search a word in all eight possible directions,
            i.e., North, West, South, East, North-East, North-West, South-East, South-West, but
            a word should not have multiple instances of the same cell.

            Input:

            board =
            [
                ['M', 'S', 'E'],
                ['R', 'A', 'T'],
                ['L', 'O', 'N']
            ]

            words = ["STAR", "NOTE", "SAND", "STONE"]

            Output: {"STAR", "NOTE"}

            */

            std::unordered_set<std::string> Solution::searchBoggle(std::vector<std::vector<char>> const & board,
                std::unordered_set<std::string> const & words) {
                std::unordered_set<std::string> boggles;



                return boggles;
            } // searchBoggle
        }
    }
}
