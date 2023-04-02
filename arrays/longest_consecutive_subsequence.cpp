/**
 * @file longest_consecutive_subsequence.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=LongestConsecutiveSubsequence
 * @version 0.1
 * @date 2023-04-01
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <map>
#include <set>
#include <algorithm>
#include <queue>
#include <iostream>

#include "longest_consecutive_subsequence.h"

namespace valhalla {
    namespace arrays {
        namespace longest_consecutive_subsequence {
            /*

            Given an integer array, find the length of the longest subsequence formed by the
            consecutive integers. The subsequence should contain all distinct values, and
            the character set should be consecutive, irrespective of its order.

            Input : [2, 0, 6, 1, 5, 3, 7]
            Output: 4
            Explanation: The longest subsequence formed by the consecutive integers is
            [2, 0, 1, 3]. It has distinct values and length 4.

            Input : [1, 4, 4, 0, 2, 3]
            Output: 5
            Explanation: The longest subsequence formed by the consecutive integers is
            [1, 4, 4, 0, 2, 3]. The distinct subsequence is [1, 4, 0, 2, 3] having length 5.

            Input : [2, 4, 6, 3, 7, 4, 8, 1]
            Output: 4
            Explanation: The longest subsequence formed by the consecutive integers is
            [2, 4, 3, 4, 1]. The distinct subsequence is [2, 4, 3, 1] having length 4.

            */

            int Solution::findMaxLenSubseq(std::vector<int> & nums) {
                const int size = nums.size();
                int max = 0;

                /*
                    Version 3 :
                    Successful and took 16ms
                */
                if (size > 0) {
                    std::sort(nums.begin(), nums.end());
                    int last = nums[0], cnt = 1;
                    max = cnt;

                    for (int idx = 1 ; idx < size ; idx++) {
                        int current = nums[idx];
                        if (current == last) {
                            continue;
                        } // if
                        if (last + 1 != current) {
                            last = current;
                            if (cnt > max) {
                                max = cnt;
                            } // if
                            cnt = 1;
                            continue;
                        } // if
                        cnt++;
                        last = current;
                        if (cnt > max) {
                            max = cnt;
                        } // if
                    } // for
                } // if

                /*
                    Version 2:
                    Unsuccessful because you priority queue allows for duplicates
                    while version 1 accounted for duplicate values.
                if (size > 0) {
                    std::priority_queue<int, std::vector<int>, std::greater<int>> priority;
                    for (int value : nums) {
                        priority.push(value);
                    } // for
                    int last = priority.top(); priority.pop();
                    int cnt = 1;
                    max = cnt;
                    std::cout << "last: " << last << std::endl;

                    while ( ! priority.empty() ) {
                        int value = priority.top(); priority.pop();
                        std::cout << "value: " << value;
                        if (last + 1 != value) {
                            if (cnt > max) max = cnt;
                            last = value;
                            cnt = 1;
                            std::cout << " cnt: " << cnt << std::endl;
                            continue;
                        } // if
                        cnt++;
                        last = value;
                        if (cnt > max) max = cnt;
                        std::cout << " cnt: " << cnt << std::endl;
                    } // while
                } // if
                */

                /*
                    Version 1 :
                    Successful and took 18ms

                if (size > 0) {
                    std::map<int,std::vector<int>> values;
                    std::set<int> keys;

                    for (int idx = 0 ; idx < size ; idx++) {
                        int key = nums[idx];
                        values[key].push_back(idx);
                        keys.insert(key);
                    } // for

                    std::vector<int> tosort(keys.begin(), keys.end());
                    std::sort(tosort.begin(), tosort.end());

                    int last = tosort[0], cnt = 1;
                    const int tosortsize = tosort.size();
                    max = cnt;

                    for (int idx = 1 ; idx < tosortsize ; idx++) {
                        int current = tosort[idx];
                        if (last + 1 != current) {
                            last = current;
                            if (cnt > max) max = cnt;
                            cnt = 1;
                            continue;
                        } // if
                        cnt++;
                        last = current;
                        if (cnt > max) max = cnt;
                    } // for
                } // if
                */

                return max;
            } // findMaxLenSubseq
        }
    }
}

