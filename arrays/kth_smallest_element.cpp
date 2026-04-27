#include <iostream>
#include "kth_smallest_element.h"

int attempt_one(std::vector<int> const & nums, int k) {
    int kidx = 0, kth_smallest = nums[kidx];

    // first determine the smallest value in the array
    for (auto i = 0; i < nums.size(); i++)
    {
        if (nums[i] < kth_smallest) {
            kidx = i;
            kth_smallest = nums[kidx];
        } // if (nums[i] < kth_smallest)
    }
    
    // use the above information to determine the kth smallest element
    for (auto i = 1; i < k; i++)
    {
        /*
            We currently have the ith smallest value so we use this information
            to determine which is the next smallest value of the list of values.

            There are two cases that allow us to move on to the next smallest
            element in the list

            - we've found a duplicate smallest value that is located beyond the
              currently duplicate value index.
            - we've determined the next smallest value larger than the prior
              ith smallest element

            we thus need to keep this information per ith smallest element
            check.  What should we use to keep this information per ith check?
        */
        // use this information to help with the cases of duplicate values
        const auto cidx = kidx;
        const int ith_smallest = kth_smallest;
        for (auto j = 0; j < nums.size(); j++)
        {
            if (nums[j] < ith_smallest) {
                // skip all smaller values
                continue;
            } // if (nums[j] < ith_smallest)

            // deal with the case of duplicate values
            if (nums[j] == ith_smallest) {
                if (j > cidx && cidx == kidx) {
                    // only update the initial index that is larger than cidx
                    kidx = j;
                } // if (j > cidx && cidx == kidx)
                continue;
            } // if (nums[j] == ith_smallest)

            if (nums[j] > ith_smallest && (kth_smallest == ith_smallest || nums[j] < kth_smallest)) {
                kidx = j;
                kth_smallest = nums[kidx];
            } // if (nums[j] > ith_smallest && nums[j] < kth_smallest)
        }        
    }

    return kth_smallest;
}

int attempt_two(std::vector<int> const & nums, int k) {
    // figure out the smallest value in the array
    int ith_smallest = nums[0];
    std::vector<int>::size_type iidx = 0;

    for (auto idx = 1 ; idx < nums.size() ; idx++) {
        if (nums[idx] < ith_smallest) {
            ith_smallest = nums[idx];
            iidx = idx;
        } // if (nums[idx] < ith_smallest)
    } // for (auto idx = 1 ; idx < nums.size() ; idx++)

    while (--k > 0) {
        const int smallest = ith_smallest;
        const std::vector<int>::size_type sidx = iidx;

        for (auto idx = 0 ; idx < nums.size() ; idx++) {
            // skip through all smaller values or the current smallest value
            if (idx == sidx || nums[idx] < smallest || (nums[idx] == smallest && idx < sidx)) {
                continue;
            } // if (idx == iidx || nums[idx] < ith_smallest || (nums[idx] == ith_smallest && idx < sidx))

            // look for duplicate values within the array
            if (nums[idx] == smallest) {
                // we are done thus move to the next k
                ith_smallest = nums[idx];
                iidx = idx;
                break; // we are exiting the for loop
            } // if (nums[idx] == smallest)

            // look for the next smallest list afte purging all irrelavent values
            if (nums[idx] < ith_smallest || smallest == ith_smallest) {
                ith_smallest = nums[idx];
                iidx = idx;
                continue;
            } // if (nums[idx] < ith_smallest || smallest == ith_smallest)
        } // for (auto idx = 0 ; idx < nums.size() ; idx++)
    } // while (--k > 0)

    return ith_smallest;
}

int valhalla::arrays::kth_smallest_element::Solution::findKthSmallest(std::vector<int> const & nums, int k) {
    return attempt_two(nums, k);
} // findKthSmallest
