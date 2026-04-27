/**
 * @file max_heap_to_min_heap.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=MaxHeapToMinHeap
 * @version 0.1
 * @date 2025-04-12
 *
 * @copyright Copyright (c) 2025 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "max_heap_to_min_heap.h"

#include <iostream>
#include <set>
#include <utility>
#include <algorithm>

namespace valhalla {

namespace heap {

namespace max_heap_to_min_heap {

/*

Given an array representing a max-heap, in-place convert it into the min-heap in linear time.

Input: [9, 4, 7, 1, -2, 6, 5]

		   9
		 /   \
		/	  \
	   4	   7
	  / \	  / \
	 /   \   /   \
	1	 -2 6	  5


Output: [-2, 1, 5, 9, 4, 6, 7]

		   -2
		 /	  \
		/	   \
	   1		5
	  / \	   / \
	 /   \	  /   \
	9	  4  6	   7		or, any other valid min-heap.

*/

// This attempt is a failure!!!
void attempt_one(std::vector<int> & nums) {
    if (nums.empty() == false) {
        const int size = static_cast<int>(nums.size());

        // This solution just swaps the right most for the current entry
        for (int idx = 0 ; idx < size ; idx++) {
            const int next = 2 * idx + 2;
            if (next < size && nums[idx] > nums[next]) {
                nums[idx] ^= nums[next];
                nums[next] ^= nums[idx];
                nums[idx] ^= nums[next];
            } // if (next < size && nums[idx] > nums[next])
        } // for (int idx = 0 ; idx < size ; idx++)
    } // if (nums.empty() == false)    
} // attempt_one

// This attempt is another failure!!!
void attempt_two(std::vector<int> & nums) {
    if (nums.empty() == false) {
        const int size = static_cast<int>(nums.size());
        
        // This solution reverses each level in the heap
        for (int idx = 1, step = 2 ; idx < size ; idx+=step, step*=2) {
            int start = idx, end = std::min(size-1, idx+step-1);
            for ( ; start < end ; start++, end--) {
                nums[start] ^= nums[end];
                nums[end] ^= nums[start];
                nums[start] ^= nums[end];
            } // for ( ; start < end ; start++, end--)
        } // for (int idx = 1, step = 2 ; idx < size ; idx+=step, step*=2)
    } // if (nums.empty() == false)
} // attempt_two

inline int left_child(int parent) {
    return 2 * parent + 1;
} // left_child

inline int right_child(int parent) {
    return left_child(parent) + 1;
} // right_child

inline int child_parent(int child) {
    return child / 2;
} // child_parent

inline void print_vector(std::vector<int> & vec) {
    std::cout << "{";
    auto itr = vec.begin();
    while (itr != vec.end()) {
        std::cout << ' ' << *itr;
        itr++;
        std::cout << (itr != vec.end() ? ',' : ' ');
    } // while (itr != vec.end())
    std::cout << "}\n";
} // print_vector

void attempt_three(std::vector<int> & nums) {
    if (nums.empty() == false) {
        const int size = static_cast<int>(nums.size());

        // swap the maximum value with the minimum value.

        // Note that this process will only need to be perform at least n/2 actions.

        // since the processing heap is a max heap we can then determine
        // where the min and max values are located. The max is the top
        // entry so we only need to get the min value.  The only issue concern
        // is how to proceed from each min value to the next.

        int min_lchild = 0, min_rchild = min_lchild, child;

        // determine where the leaf layer starts.
        while ((child = left_child(min_lchild)) < size) {
            // update the range of entries for the next layer of the heap
            min_lchild = child;
            min_rchild = right_child(min_rchild);
        } // while ((child = left_child(min_lchild)) < size)

        // define the left most index and the right index for a given depth of the heap
        int max_lchild = 0, max_rchild = 0;

        // setup indexes used to process the swapping of values
        int min_idx = min_lchild, max_idx = max_lchild;

        // swap the children that are less than the current maximum values
        while (max_lchild <= min_lchild) {
            std::cout << "max_lchild: " << max_lchild << ", max_rchild: " << max_rchild << ", min_lchild: " << min_lchild << ", min_rchild: " << min_rchild
                << ", max_idx: " << max_idx << ", size: " << size << ", nums[max_idx]: " << nums[max_idx] << '\n';
            std::cout << "Before update: ";
            print_vector(nums);
            int idx = min_lchild, prior_max = nums[max_idx];

            // find the next swapping entry
            while (idx < size && idx <= min_rchild) {
                if (nums[max_idx] > nums[idx]) {
                    nums[max_idx] ^= nums[idx];
                    nums[idx] ^= nums[max_idx];
                    nums[max_idx] ^= nums[idx];
                } // if (nums[max_idx] > nums[idx])
                idx++;
            } // while (idx < min_rchild)

            std::cout << "[nums[max_idx],prior_max]: [" << nums[max_idx] << ',' << prior_max << "]\n";

            if (nums[max_idx] != prior_max) {
                max_idx++;

                if (max_idx > max_rchild) {
                    // update the max_idx
                    max_idx = max_lchild = left_child(max_lchild);
                    max_rchild = right_child(max_rchild);
                } // if (max_idx > max_rchild)
    
            } else {
                // update the indexes
                min_lchild = child_parent(min_lchild);
                min_rchild = child_parent(min_rchild);
            } // if (nums[max_idx] != prior_max)

            std::cout << "After update: ";
            print_vector(nums);
        } // while (max_lchild < min_lchild)
    } // if (nums.empty() == false)
} // attempt_three

void attempt_four(std::vector<int> & nums) {
    if (nums.empty() == false) {
        // We need to somehow keep a reference to all of the leaf parents that contain children
        // values.  This information should be easily retreived and easily diseminated while
        // move the values around the heap.

        // This contains the parent index that contain entries that are being processed.
        std::set<int> parents;
        const int size = static_cast<int>(nums.size());

        int idx = 0;

        while (left_child(idx) < size) {
            idx = left_child(idx);
        } // while (left_child(idx) < size)

        // add the index of all the parents to the second to last layer.
        for (int parent = child_parent(idx) ; parent < idx ; parent++) {
            parents.insert(parent);
        } // for (int parent = child_parent(idx) ; parent < idx ; parent++)

        // this contains the current max ranges and current entry being updated
        int max_lchild = 0, max_rchild = max_lchild, max_idx = 0;

        // process each parent to determine the smallest value and swap the entries
        while ( ! parents.empty() ) {
            std::cout << "Before update: "; print_vector(nums);
            const int prior = nums[max_idx];

            for (int parent :  parents) {
                if (parent <= max_idx) {
                    parents.erase(parent);
                    continue;
                } // if (parent <= max_idx)
                int lchild = left_child(parent), rchild = right_child(parent);
                if (lchild < size && nums[max_idx] > nums[lchild]) {
                    // std::cout << "Swapping entries [" << max_idx << "," << lchild << "].\n";
                    std::cout << "Swapping entries [" << nums[max_idx] << "," << nums[lchild] << "].\n";
                    // print_vector(nums);
                    nums[max_idx] ^= nums[lchild];
                    nums[lchild] ^= nums[max_idx];
                    nums[max_idx] ^= nums[lchild];
                    // std::swap(nums[max_idx], nums[lchild]);
                    // print_vector(nums);
                    std::cout << "Swapped entries [" << nums[max_idx] << "," << nums[lchild] << "].\n";
                } // if (nums[max_idx] > nums[lchild])

                if (rchild < size && nums[max_idx] > nums[rchild]) {
                    // std::cout << "Swapping entries [" << max_idx << "," << rchild << "].\n";
                    std::cout << "Swapping entries [" << nums[max_idx] << "," << nums[rchild] << "].\n";
                    // print_vector(nums);
                    nums[max_idx] ^= nums[rchild];
                    nums[rchild] ^= nums[max_idx];
                    nums[max_idx] ^= nums[rchild];
                    // std::swap(nums[max_idx], nums[rchild]);
                    // print_vector(nums);
                    std::cout << "Swapped entries [" << nums[max_idx] << "," << nums[rchild] << "].\n";
                } // if (rchild < size && nums[max_idx] > nums[rchild])

                if (prior != nums[max_idx]) {
                    // we found an entry that was less than the current entry
                    max_idx++;
                    if (max_idx == max_rchild) {
                        max_lchild = left_child(max_lchild);
                        max_rchild = right_child(max_rchild);
                    } // if (max_idx == max_rchild)
                    std::cout << "Vector was updated: "; print_vector(nums);
                    continue;
                } // if (prior != nums[max_idx])

                // This parent currently doesn't contain any entries less than the current
                // entry thus move up the heap and remove this entry.

                std::cout << "vector was not updated by children of parent: " << parent << '\n';

                const int nparent = child_parent(parent);

                if (nparent != parent) {
                    parents.erase(parent);
                } // if (nparent != parent)

                if (nparent > max_idx) {
                    parents.insert(nparent);
                } // if (nparent > max_idx)
            } // for (auto parent :  parents)
            std::cout << "After updating current set of parents: "; print_vector(nums);
        } // while ( ! parents.empty() )
    } // if (nums.empty() == false)    
} // attempt_four

void attempt_five(std::vector<int> & nums) {
    if ( ! nums.empty() ) {
        // create a valid min heap from the current min heap using in place replacement only
        // in linear time

        // The largest value is on the top, while the smallest is somewhere in the tail of the
        // array

        int front = 0, back = static_cast<int>(nums.size()) - 1; // get a reference to the front and back entries
        
        std::cout << "Input nums: "; print_vector(nums);

        while (front < back) {
            // move the largest to the back and resort
            nums[front] ^= nums[back];
            nums[back] ^= nums[front];
            nums[front] ^= nums[back];

            // check that the upper entry is greater than the current entry
            auto parent = child_parent(front);

            if (nums[parent] > nums[front]) {
                nums[parent] ^= nums[front];
                nums[front] ^= nums[parent];
                nums[parent] ^= nums[front];
            } // if (nums[parent] > nums[front])

            // check that the lower entries are less than the current entry

            auto child = right_child(back);

            if (child < nums.size() && nums[child] < nums[back]) {
                nums[child] ^= nums[back];
                nums[back] ^= nums[child];
                nums[child] ^= nums[back];
            } // if (child < nums.size() && nums[child] < nums[back])

            child = left_child(back);

            if (child < nums.size() && nums[child] < nums[back]) {
                nums[child] ^= nums[back];
                nums[back] ^= nums[child];
                nums[child] ^= nums[back];
            } // if (child < nums.size() && nums[child] < nums[back])

            std::cout << "Updated nums with front: " << front << " back: " << back << " :"; print_vector(nums);
            front++; back--;
        } // while (front < back)
        // std::make_heap(nums.begin(), nums.end(), std::greater<int>());
    } // if ( ! nums.empty() )
} // attempt_five

void attempt_six(std::vector<int> & nums) {
    if ( ! nums.empty() ) {
        // create a valid min heap from the current min heap using in place replacement only
        // in linear time

        // The largest value is on the top, while the smallest is somewhere in the tail of the
        // array

        int front = 0, back = static_cast<int>(nums.size()) - 1; // get a reference to the front and back entries
        
        std::cout << "Input nums: "; print_vector(nums);

        while (front <= back) {
            auto fvalue =  nums[front], bvalue = nums[back];
            if (nums[front] > nums[back]) {
                // move the largest to the back and resort
                nums[front] ^= nums[back];
                nums[back] ^= nums[front];
                nums[front] ^= nums[back];
            }

            // check that the upper entry is greater than the current entry
            auto child = front;

            auto parent = child_parent(front);

            while (nums[parent] > nums[child]) {
                std::cout << "1 - Swapping parent " << parent << " = " << nums[parent] << " with child " << child << " = " << nums[child] << "\n";
                nums[parent] ^= nums[child];
                nums[child] ^= nums[parent];
                nums[parent] ^= nums[child];
                child = parent;
                parent = child_parent(child);
            } // while (nums[parent] > nums[front])

            // check that the lower entries are less than the current entry

            parent = back;

            child = right_child(parent);

            while (child < nums.size() && nums[child] < nums[parent]) {
                std::cout << "2 - Swapping parent " << parent << " = " << nums[parent] << " with child " << child << " = " << nums[child] << "\n";
                nums[child] ^= nums[parent];
                nums[parent] ^= nums[child];
                nums[child] ^= nums[parent];
                parent = child;
                child = right_child(parent);
            } // while (child < nums.size() && nums[child] < nums[parent])

            parent = back;

            child = left_child(parent);

            while (child < nums.size() && nums[child] < nums[parent]) {
                std::cout << "3 - Swapping parent " << parent << " = " << nums[parent] << " with child " << child << " = " << nums[child] << "\n";
                nums[child] ^= nums[parent];
                nums[parent] ^= nums[child];
                nums[child] ^= nums[parent];
                parent = child;
                child = left_child(parent);
            } // while (child < nums.size() && nums[child] < nums[parent])

            std::cout << "Updated nums with front: " << front << " = " << fvalue << " back: " << back << " = " << bvalue << " :";
            print_vector(nums);
            front++; back--;
        } // while (front < back)
        // std::make_heap(nums.begin(), nums.end(), std::greater<int>());
    } // if ( ! nums.empty() )
} // attempt_six

void attempt_seven(std::vector<int> & nums) {
    if ( nums.size() > 1 ) {
        // How do we convert a max heap into a min heap?
        /*
            Thought process of performing a linear time conversion of a max heap into a min heap
        
            Step 1: Determine the min value of the current heap.
            Step 2: Swap the min value with the max value, root
            Step 3: Determine the next max value and min value
            Step 4: swap the min value with the max value
            Step 5: continue until we've completed the swap

            Issue: How do we store the current set of values that need to be checked?

            The root will reference a single entry when the children can be referencing one or two
            entries.  We need to produce the logic that allows me to be able to gracefully manage
            these situations.  Note that as soon as we've swapped one of the children that that
            entry is not required to be checked any longer.  We need to be able to manage this case.
        */

        // Find the last row of the heap array since those are the smallest values
        std::vector<int>::size_type row = 0, next_row = left_child(row);
        while (next_row < nums.size()) {
            // move the last row to the next row value
            row = next_row;
            // determine the start of the next row
            next_row = left_child(row);
        } // while (next_row < nums.size())

        // what's next?
        // process each last row and then move up to the next row until you've crossed index
    } // if ( nums.size() > 1 )
} // attempt_seven

void Solution::convert(std::vector<int> & nums) {
    attempt_six(nums);
} // convert

} // namespace max_heap_to_min_heap

} // namespace heap

} // namespace valhalla
