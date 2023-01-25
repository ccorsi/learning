/**
 * @file maximum_continuous_sequence_two.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is the solution to the problem https://www.techiedelight.com/?problem=MaximumContinuousSequenceII
 * @version 0.1
 * @date 2023-01-22
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <iostream>
#include <algorithm>
#include <assert.h>

#include "maximum_continuous_sequence_two.h"

using namespace std;

ostream& operator<<(ostream& out, const pair<int,int>& p) {
    out << "[" << p.first << "," << p.second << "]";
    return out;
}

/*

Given a binary array and a positive integer `k`, return the indices of the maximum sequence of continuous 1’s that can be formed by replacing at most `k` zeroes by ones.

• The solution should return a pair of the starting and the ending index of the maximum sequence.
• For invalid inputs, the solution should return pair (-1, -1).
• In case multiple sequence of continuous 1’s of maximum length exists, the solution can return any one of them.

Input : nums[] = [1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0], k = 0
Output: (6, 9)
Explanation: The longest sequence of continuous 1’s is formed by index 6 to 9.

Input : nums[] = [1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0], k = 1
Output: (3, 9)
Explanation: The longest sequence of continuous 1’s is formed by index 3 to 9 on replacing zero at index 5.

Input : nums[] = [1, 1, 1, 1, 1], k = 1
Output: (0, 4)

Input : nums[] = [1, 0, 1, 1, 0, 0, 1, 1, 0, 1], k = 1
Output: (0, 3) or (6, 9)

Input : nums[] = [], k = 1
Output: (-1, -1)

*/

pair<int,int> valhalla::arrays::maximum_continuous_sequence_two::Solution::findLongestSequence(vector<int> const &nums, int k) {
    pair<int,int> p(-1,-1);

    // check if the passed vector is empty
    if (nums.empty()) {
        // there is nothing to do so just return
        return p;
    } // if

    // if there is only a single entry in the array
    if (nums.size() == 1) {
        // check if the single entry is zero
        if (k > 0 && nums[0] == 0) {
            p.first = p.second = 0;
        } // if
        return p;
    } // if

    size_t kcnt = 1;
    size_t idx = 0;
    const size_t zeros_size = k + 2;
    size_t size;

    // setup an array that will contain the different zeros within the passed nums
    vector<size_t> zeros(zeros_size);

    // insure that this is correct
    assert(zeros_size == zeros.size());

    // find all k zeros in the passed nums
    do {
        // find next zero entry index
        while (idx < nums.size() && nums[idx] == 1) idx++;
        // set the zero entry index to the next kcnt and set it to size also
        size = zeros[kcnt] = idx;
        // increment the kcnt zeros array
        kcnt++;
        // increment the idx count for the nums array
        idx++;
    } while (kcnt < zeros_size && size < nums.size());

    if (kcnt < zeros_size) {
        // this implies that there was less than k zeros within the nums vector
        // we are done since all of the information we need is within the zeros array
        p.first = 0;
        p.second = nums.size() - 1;
    } else {
        // this implies that there was at least k zeros within the nums vector
        // we firstly calculate the longest sequence given the current zeros
        int max_len = 0;

        for( size_t cnt = 1 ; cnt < zeros_size ; cnt++) {
            max_len += (zeros[cnt] - zeros[cnt - 1]);
        } // for

        // this calculation is not required at first because we start at zero
        // max_len += k;

        // set the first and second entries in the pair for the current max_len
        p.first = zeros.front();
        p.second = zeros.back() - 1;

        cout << ">>>>>> nums: [";
        for (size_t num : nums)
            cout << " " << num;
        cout << " ] <<<<<<" << endl;
        cout << ">>>>>> zeros: [";
        for (size_t zero : zeros)
            cout << " " << zero;
        cout << " ] <<<<<<" << endl;
        cout << "max_len: " << max_len << ", p: " << p << ", k: " << k << endl;

        const size_t last_idx = zeros_size - 1;

        // we now find the subsequence zero and calculate its length and compare
        // it to the current maximum sequence length
        while (size < nums.size()) {
            // shift entries by one
            auto first = zeros.begin();
            first++; // move iterator to next entry
            std::move(first, zeros.end(), zeros.begin());

            cout << ">>>>>> shifted zeros: [";
            for (size_t zero : zeros)
                cout << " " << zero;
            cout << " ] <<<<<<" << endl;

            // find next zero entry index
            while (idx < nums.size() && nums[idx] == 1) idx++;
            // set the zero entry index to the last entry in the zeros vector
            size = zeros[last_idx] = idx;
            // increment the idx count for the nums array
            idx++;

            cout << ">>>>>> updates zeros: [";
            for (size_t zero : zeros)
                cout << " " << zero;
            cout << " ] <<<<<<" << endl;

            // calculate the current length and compare to max_length
            int len = 0;

            for( size_t cnt = 1 ; cnt < zeros_size ; cnt++) {
                len += (zeros[cnt] - zeros[cnt - 1]);
            } // for

            len += (k == 0) ? -1 : -k;
            cout << ">>>>>>>>> len: " << len << " <<<<<<<<" << endl;

            if (len > max_len) {
                max_len = len;
                // update p
                // set the first and second entries in the pair for the current max_len
                p.first = zeros.front() + 1;
                p.second = zeros.back() - 1;
                cout << "max_len: " << max_len << ", p: " << p << ", k: " << k << endl;
            } // if

            cout << ">>>>>>> idx: " << idx << " <<<<<<<" << endl;
        } // while
    } // else

    cout << ">>>>>> nums: [";
    for (size_t num : nums)
        cout << " " << num;
    cout << " ] <<<<<<" << endl;

    cout << ">>>>>> zeros: [";
    for (size_t zero : zeros)
        cout << " " << zero;
    cout << " ], k=" << k << " <<<<<<" << endl;

    // if (kcnt < k) {
    //     // we just use the beginning and ending values
    //     p.first = zeros[1];
    //     p.second = zeros[kcnt - 1];
    // } // if

    return p;
}
