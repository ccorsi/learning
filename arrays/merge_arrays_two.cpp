/**
 * @file merge_arrays_two.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem at https://www.techiedelight.com/?problem=MergeArraysII
 * @version 0.1
 * @date 2023-01-16
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <iostream>
#include <algorithm>

#include "merge_arrays_two.h"

using namespace std;

/*

Given two sorted integer arrays `X[]` and `Y[]` of size `m` and `n` each where `m >= n` and `X[]` has exactly `n` vacant cells, merge elements of `Y[]` in their correct position in array `X[]`, i.e., merge `(X, Y)` by keeping the sorted order.

Input : Two arrays X[] and Y[] where vacant cells in X[] is represented by 0.

X[] = [0, 2, 0, 3, 0, 5, 6, 0, 0]
Y[] = [1, 8, 9, 10, 15]

Output: X[] = [1, 2, 3, 5, 6, 8, 9, 10, 15]

*/

void print(vector<int>& X) {
    cout << "[";
    for(int value : X) {
        cout << " " << value;
    }
    cout << " ]" << endl;
}

/**
 * @brief This method will merge the two arrays into the X vector.  The X vector will
 *  contain vacant entries set to 0 while the Y doesn't contain vacant values.  The values
 *  of Y will be insert into the X vector.  Note that the vector Y can also contain the
 *  vacant entry 0 which is not consider a vacant entry.
 *
 * @param X
 * @param Y
 */
void valhalla::arrays::merge_arrays_two::Solution::merge(vector<int>& X, vector<int>& Y) {
    /*
        NOTE: the following solution is using the available libraries to perform this task.
            It does work but alas it doesn't really challange me with a solution.

    // copy all entries in Y into the vacant entries in X
    for(auto Xitr = X.begin(), Yitr = Y.begin() ; Yitr != Y.end() ; Yitr++) {
        // skip all non-vacant entries in X
        while(*Xitr != 0) Xitr++;
        // assign the Y value to X
        *Xitr = *Yitr;
    }

    // sort the array after adding the entries
    sort(X.begin(), X.end());
    */

    /*
        Here is a list of all of the possible conditions that require actions

            1 - One or more values of Y is smaller than the smallest value of X
            2 - One or more values of Y is greater than the largest value of X
            3 - All vacant entries are at the beginning of X
            4 - All vacant entries are at the end of X
            5 - Vacant entries are spread out throughout X
            6 - The X or Y vector is empty
            7 - The X vector only contains vacancies where size of X is equal to size of Y
            8 - The X vector only contains vacancies where size of X is not equal to size of Y
            9 - Y contains one or more vacant entry values

    */

    // check if the passed arrays are empty then there is nothing to do
    if (X.size() == 0 || Y.size() == 0) {
        // This solves case 6
        return;
    } // if

    // setup different tracking indexes used to merge the two arrays
    size_t x_idx = 0, y_idx = 0, idx = 0;

    // find first vacant entry.
    while (X[x_idx] != 0) {
        x_idx++;
    } // while

    for(int value : Y) {
        // cout << "value: " << value << ", x_idx: " << x_idx << " X: "; print(X);
        // assign the current value to the current vacant index
        X[x_idx] = value;
        // move it to the correct spot.
        if (x_idx == 0) {
            // This is an end value
            for(size_t idx = x_idx + 1; idx < X.size() && X[idx] < value ; idx++) {
                // swap the entries
                int temp = X[idx - 1];
                X[idx - 1] = X[idx];
                X[idx] = temp;
            } // for
        } else if (x_idx == X.size() - 1) {
            // This is an end value
            for (size_t idx = x_idx; idx > 0 && X[idx - 1] > value ; idx--) {
                // swap the entries
                int temp = X[idx - 1];
                X[idx - 1] = X[idx];
                X[idx] = temp;
            } // for
        } else {
            // We are adding the entry within the boundaries of the vector
            if (X[x_idx - 1] < X[x_idx] && X[x_idx] < X[x_idx]) {
                // The entry was already inserted into the correct index
            } else if (X[x_idx - 1] > X[x_idx]) {
                // The entry needs to be moved to the back
                for(size_t idx = x_idx ; idx > 0 && X[idx - 1] > X[idx] ; idx--) {
                    // swap the entries
                    int temp = X[idx - 1];
                    X[idx - 1] = X[idx];
                    X[idx] = temp;
                } // for
            } else {
                // The entry needs to be moved to the front
                for(size_t idx = x_idx + 1 ; idx < X.size() && X[idx - 1] > X[idx] ; idx++ ) {
                    // swap the entries
                    int temp = X[idx - 1];
                    X[idx - 1] = X[idx];
                    X[idx] = temp;
                } // for
            } // else
        } // else

        if (X[x_idx] != 0 || value == 0) {
            // increment index only if it is not a vacant entry or that the value is a vacant value
            x_idx++;
        } // if

        // find next vacant entry.
        while (x_idx < X.size() && X[x_idx] != 0) {
            x_idx++;
        } // while
    } // for
}
