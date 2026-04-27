/**
 * @file merge_sorted_lists.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=MergeSortedLists
 * @version 0.1
 * @date 2026-04-24
 * 
 * @copyright Copyright (c) 2026 Claudio Corsi
 * 
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <algorithm>
#include <iostream>
#include <queue>
#include <list>

#include "merge_sorted_lists.h"

namespace valhalla {

namespace heap {

namespace merge_sorted_lists {

struct Vector {
    const std::vector<int> & m_vec;
    std::vector<int>::const_iterator m_itr;
    Vector(const std::vector<int> & vec) : m_vec(vec), m_itr(vec.cbegin()) {}
    bool end() { return m_itr == m_vec.cend(); }
    std::vector<int>::const_iterator operator++(int) { return m_itr++; }
    bool operator<(const Vector & other) {
        // std::cout << "operator< comparing " << *this << " with " << other << "\n";
        return *m_itr < other.value();
    }
    int value() const { return *m_itr; }
    std::vector<int> const vector() const { return m_vec; }
    bool operator=(const Vector & other) {
        return this == &other;
    }
    std::ostream & operator<<(std::ostream & out) {
        out << "Vector[";
        for (auto & v : m_vec)
            out << " " << v;
        return out << " ] value=" << value() << " ]";
    }
    friend std::ostream & operator<<(std::ostream & out, const Vector & vec);
};

/*

Given `M` sorted lists of variable length, merge them efficiently in sorted order.

Input:

mat = [
	[10, 20, 30, 40],
	[15, 25, 35],
	[27, 29, 37, 48, 93],
	[32, 33]
]

Output: [10, 15, 20, 25, 27, 29, 30, 32, 33, 35, 37, 40, 48, 93]

*/

template<
    typename Iterator
>
void print(Iterator & first, Iterator & end) {
    while (first != end) {
        std::cout << *first << "\n";
        first++;
    } // while (first != end)
}

void print(std::vector<Vector> & heap) {
    std::cout << "Heap\n";
    for (Vector & vector : heap) {
        std::cout << vector << "\n";
    }
    std::cout << "Done\n";
}

std::vector<int> attempt_one(std::vector<std::vector<int>> const & lists) {
    std::vector<int> merged_sorted_list;

    auto min_compare = [](const Vector & lhs, const Vector & rhs) {
        int lvalue = lhs.value(), rvalue = rhs.value();
        std::cout << "Comparing " << lhs << " to " << rhs << "\n";
        return lvalue > rvalue;
    };

    std::vector<Vector> heap;
    for (auto & vec : lists) {
        Vector vector(vec);
        if ( vector.end() == false) {
            heap.push_back(vector);
        } // if ( vector.end() == false)
    } // for (auto & vec : lists)

    if (heap.empty()) {
        // we don't have any entries that were passed to this method
        return merged_sorted_list;
    } // if (heap.empty())

    std::cout << "Before make_heap\n";
    std::make_heap(heap.begin(), heap.end(), min_compare);
    std::cout << "After make_heap\n";

    print(heap);

    while ( ! heap.empty() ) {
        // pop the top entry from the heap
        std::pop_heap(heap.begin(), heap.end(), min_compare);
        // get a reference to the popped entry
        Vector & vector = heap.back();
        std::cout << "Top: " << vector << "\n";
        // add the value to the merged sorted list...
        merged_sorted_list.push_back(vector.value());
        // ...iterate the current iterator...
        vector++;
        // ...determine if we should remove the instance or not...
        if (vector.end()) {
            // remove the Vector instance since we've exhausted the entries
            heap.pop_back();
        } else {
            // sort the updated Vector instance since it hasn't reached the end of the vector.
            std::push_heap(heap.begin(), heap.end(), min_compare);
        } // if (vector.end())
        print(heap);
    } // while ( ! heap.empty() )

    return merged_sorted_list;
} // attempt_one

std::vector<int> attempt_two(std::vector<std::vector<int>> const & lists) {
    std::vector<int> merged_sorted_list;

    std::vector<Vector> heap;
    for (auto & vec : lists) {
        Vector vector(vec);
        if ( vector.end() == false) {
            heap.push_back(vector);
        } // if ( vector.end() == false)
    } // for (auto & vec : lists)

    if (heap.empty()) {
        // we don't have any entries that were passed to this method
        return merged_sorted_list;
    } // if (heap.empty())

    std::cout << "Before make_heap\n";
    std::make_heap(heap.begin(), heap.end());
    std::cout << "After make_heap\n";

    print(heap);

    while ( ! heap.empty() ) {
        std::cout << "Before pop_heap\n"; print(heap);
        // pop the top entry from the heap
        std::pop_heap(heap.begin(), heap.end());
        std::cout << "After pop_heap\n"; print(heap);
        // get a reference to the popped entry
        Vector & vector = heap.back();
        std::cout << "Top: " << vector << "\n";
        // add the value to the merged sorted list...
        merged_sorted_list.push_back(vector.value());
        // ...iterate the current iterator...
        vector++;
        // ...determine if we should remove the instance or not...
        if (vector.end()) {
            // remove the Vector instance since we've exhausted the entries
            heap.pop_back();
        } else {
            // sort the updated Vector instance since it hasn't reached the end of the vector.
            std::push_heap(heap.begin(), heap.end());
        } // if (vector.end())
        print(heap);
    } // while ( ! heap.empty() )

    return merged_sorted_list;
} // std::vector<int> attempt_two(std::vector<std::vector<int>> const & lists)

std::vector<int> solution_three(std::vector<std::vector<int>> const & lists) {
    std::vector<int> merged_sorted_list;

    std::list<Vector> heap;
    for (auto & vec : lists) {
        Vector vector(vec);
        if ( vector.end() == false) {
            auto itr = heap.begin();
            for ( ; itr != heap.end() ; itr++) {
                if (vector < *itr) {
                    heap.insert(itr, vector);
                    break;
                } // if (vector < *itr)
            } // for ( ; itr != heap.end() ; itr++)
            if (itr == heap.end()) {
                heap.push_back(vector);
            } // if (itr == heap.end())
        } // if ( vector.end() == false)
    } // for (auto & vec : lists)

    if (heap.empty()) {
        // we don't have any entries that were passed to this method
        return merged_sorted_list;
    } // if (heap.empty())

    // print(heap.begin(), heap.end());

    while (heap.empty() == false) {
        Vector vector = heap.front();
        heap.pop_front();
        merged_sorted_list.push_back(vector.value());
        vector++;
        if (vector.end() == false) {
            auto itr = heap.begin();
            for ( ; itr != heap.end() ; itr++) {
                if (vector < *itr) {
                    heap.insert(itr, vector);
                    break;
                } // if (vector < *itr)
            } // for ( ; itr != heap.end() ; itr++)
            if (itr == heap.end()) {
                heap.push_back(vector);
            } // if (itr == heap.end())
            // print(heap.begin(), heap.end());
        } // if (vector.end() == false)
    } // while (heap.empty() == false)

    return merged_sorted_list;
} // std::vector<int> solution_three(std::vector<std::vector<int>> const & lists)

std::vector<int> Solution::mergeSortedLists(std::vector<std::vector<int>> const & lists) {
    return solution_three(lists);
} // mergeSortedLists

std::ostream & operator<<(std::ostream & out, const Vector & data) {
    out << "Vector[";
    for (auto & v : data.vector())
        out << " " << v;
    return out << " ] value=" << data.value() << " ]";
}

} // namespace merge_sorted_lists

} // namespace heap

} // namespace valhalla
