/**
 * @file lexicographic_sorting.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2025-02-23
 *
 * @copyright Copyright (c) 2025 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */
#ifndef __LEXICOGRAPHIC_SORTING_H__
#define __LEXICOGRAPHIC_SORTING_H__

#include <string>
#include <vector>
#include <unordered_set>

namespace valhalla {

namespace trie {

namespace lexicographic_sorting {

class Solution {
public:
    std::vector<std::string> lexicographicSort(std::unordered_set<std::string> const &);
};

} // namespace lexicographic_sorting

} // namespace trie

} // namespace valhalla

#endif
