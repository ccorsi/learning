/**
 * @file power_set.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2025-03-22
 *
 * @copyright Copyright (c) 2025 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */
#ifndef __POWER_SET_H__
#define __POWER_SET_H__

#include <vector>

namespace valhalla {

namespace backtracking {

namespace power_set {

class Solution {
public:
    std::vector<std::vector<int>> findPowerSet(std::vector<int> const &);
};

} // namespace power_set

} // namespace backtracking

} // namespace valhalla

#endif
