/**
 * @file kth_largest_element_two.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief 
 * @version 0.1
 * @date 2026-04-24
 * 
 * @copyright Copyright (c) 2026 Claudio Corsi
 * 
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

 #ifndef __KTH_LARGEST_ELEMENT_TWO_H__
 #define __KTH_LARGEST_ELEMENT_TWO_H__
 
 #include <vector>
 #include <algorithm>
 
 namespace valhalla {
 
 namespace heap {
 
 namespace kth_largest_element_two {
 
 class Solution {
    std::vector<int> m_heap;
 public:
    int findKthLargest(int, int);
 };
 
 } // namespace kth_largest_element_two
 
 } // namespace heap
 
 } // namespace valhalla
 
 #endif
 