/**
 * @file magnet_puzzle.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-06-22
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */
#ifndef __MAGNET_PUZZLE_H__
#define __MAGNET_PUZZLE_H__

#include <vector>

namespace valhalla {
    namespace matrices {
        namespace magnet_puzzle {
            class Solution {
            public:
                std::vector<std::vector<char>> solveMagnetPuzzle(std::vector<std::vector<char>> const &,
                    std::vector<int> const &, std::vector<int> const &, std::vector<int> const &,
                    std::vector<int> const &);
            };
        }
    }
}

#endif
