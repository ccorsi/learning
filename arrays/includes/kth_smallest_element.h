/**
 * @file kth_smallest_element.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief 
 * @version 0.1
 * @date 2026-04-22
 * 
 * @copyright Copyright (c) 2026 Claudio Corsi
 * 
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __KTH_SMALLEST_ELEMENT_H__
#define __KTH_SMALLEST_ELEMENT_H__

#include <vector>

namespace valhalla {

namespace arrays {

namespace kth_smallest_element {

class Solution {
public:
    int findKthSmallest(std::vector<int> const &nums, int k);
};

} // namespace kth_smallest_element

} // namespace arrays

} // namespace valhalla

#endif
