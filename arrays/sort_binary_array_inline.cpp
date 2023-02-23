/**
 * @file sort_binary_array_inline.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief 
 * @version 0.1
 * @date 2022-12-29
 * 
 * @copyright Copyright (c) 2022 Claudio Corsi
 * 
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */
#include <iostream>

using namespace std;

#include "sort_binary_array_inline.h"

ostream& operator<<(ostream& out, const std::vector<int>& values) {
    out << "[";

    for( auto value : values) {
        cout << " " << value;
    }

    out << " ]";

    return out;
}

/*

Given a binary array, in-place sort it in linear time and constant space. The output should contain all zeroes, followed by all ones.

Input : [1, 0, 1, 0, 1, 0, 0, 1]
Output: [0, 0, 0, 0, 1, 1, 1, 1]

Input : [1, 1]
Output: [1, 1]

*/

void valhalla::arrays::sort_binary_array_inline::Solution::sort_array(std::vector<int> &values) {
    if (values.empty()) return;

    cout << "Before: " << values << endl;

    std::vector<int>::size_type front = 0, back = values.size() - 1;

    while (front < back) {
        cout << "Start [front,back] = [" << front << "," << back << "]" << endl;
        if (values[front] == 0) {
            front++;
            if (values[back] == 1) {
                back--;
            }
        } else {
            // values[front] == 1
            if (values[back] == 0) {
                values[front++] = 0;
                values[back--] = 1;
            } else {
                // values[back] == 1
                back--;
            }
        }
        cout << "End [front,back] = [" << front << "," << back << "]" << endl;
    }

    cout << "After: " << values << endl;
}
