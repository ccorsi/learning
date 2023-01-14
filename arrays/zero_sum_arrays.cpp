/**
 * @file zero_sum_arrays.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief 
 * @version 0.1
 * @date 2022-12-26
 * 
 * @copyright Copyright (c) 2022 Claudio Corsi
 * 
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <iostream>
#include <vector>
#include <set>
#include <map>

using namespace std;

#include "zero_sum_arrays.h"

/*

Given an integer array, find all contiguous subarrays with zero-sum.

Input : [4, 2, -3, -1, 0, 4]
Output: {[-3, -1, 0, 4], [0]}

Input : [3, 4, -7, 3, 1, 3, 1, -4, -2, -2]
Output: {[3, 4, -7], [4, -7, 3], [-7, 3, 1, 3], [3, 1, -4], [3, 1, 3, 1, -4, -2, -2], [3, 4, -7, 3, 1, 3, 1, -4, -2, -2]}

Input : [0, 0]
Output: {[0], [0, 0]}

Input : [1, 2, 3]
Output: {}

Note: Since an input can have multiple subarrays with zero-sum, the solution should return a set containing all the distinct subarrays.

*/
set<vector<int>> valhalla::arrays::zero_sum_arrays::Solution::find_zero_subarrays(const vector<int> &values) {
    set<vector<int>> subarrays;

    if (values.empty()) {
        return subarrays;
    }

    int sum = 0;

    map<int, vector<int>> ranges;

    size_t last = 0;
    vector<int> zeros;

    for (size_t idx = 0 ; idx < values.size() ; idx++) {
        // insert the current index for the this sum
        ranges[sum].push_back(idx);

        // check if the current index value is zero
        if (values[idx] == 0) {
            // determine if zero follows prior zero
            if (last + 1 != idx) {
                // it doesn't so clear the zeros vector
                zeros.clear();
            }
            // update last index
            last = idx;
            // add zero to zeros vector
            zeros.push_back(0);
            // print some logging information
            cout << "Subarray with entries: " << zeros << " adding subarray to subarrays" << endl;
            // add to found subarrays
            subarrays.insert(zeros);
            // proceed to the next entry in the vection
            continue;
        }
        
        // sum the current values
        sum += values[idx];

        // get the subarray for the current sum
        vector<int> subarray = ranges[sum];

        if ( ! subarray.empty() ) {
            cout << "Found zero sum subarrays " << subarray << endl;

            // extract each array values
            for (size_t cnt = 0 ; cnt < subarray.size() ; cnt++) {
                // We've found a subarray that sums to zero
                vector<int> entries;

                cout << "Subarray with entries: [";
                for (size_t pos = subarray[cnt] ; pos < idx ; pos++) {
                    cout << " " << values[pos];
                    entries.push_back(values[pos]);
                }

                cout << " " << values[idx]; // << endl;
                // don't forget to add the current entry
                entries.push_back(values[idx]);
            
                cout << " ] adding subarray to subarrays" << endl;
                // add the subarray to the returning subarrays
                subarrays.insert(entries);
            }

        } // if

    } // for

    cout << "Returning: " << subarrays << endl;

    return subarrays;
}
