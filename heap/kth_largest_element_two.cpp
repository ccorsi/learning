/**
 * @file kth_largest_element_two.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=KthLargestElementII
 * @version 0.1
 * @date 2026-04-24
 * 
 * @copyright Copyright (c) 2026 Claudio Corsi
 * 
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */


#include "kth_largest_element_two.h"

namespace valhalla {

namespace heap {

namespace kth_largest_element_two {

/*

Given an infinite stream of integers, return the element representing the k'th largest element in the stream.

Input: k = 3, nextInt = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, ...]
Output : [-1, -1, 1, 2, 3, 4, 5, 6, 7, 8, ...]

Here, `k` is constant for each run and `nextInt` is the next integer in the infinite stream. The solution
should return the next k'th largest element, and return -1 when the stream has fewer elements than `k`.

*/
int Solution::findKthLargest(int k, int nextInt) {
    // return negative 1 for non-positive k values
    if (k < 1) return -1;
    // push the current entry to the back of the vector
    m_heap.push_back(nextInt);
    int kth_largest_element = -1;
    if (m_heap.size() == k) {
        // sort the heap for the first time
        std::make_heap(m_heap.begin(), m_heap.end(), std::greater<>());
        // the kth largest element is on the top
        kth_largest_element = m_heap.front();
    } else if (m_heap.size() > k) {
        std::push_heap(m_heap.begin(), m_heap.end(), std::greater<>());
        std::pop_heap(m_heap.begin(), m_heap.end(), std::greater<>());
        kth_largest_element = m_heap.front();
        m_heap.pop_back();
    }
    
    return kth_largest_element;
} // findKthLargest

} // namespace kth_largest_element_two

} // namespace heap

} // namespace valhalla
