/**
 * @file k_partition_problem.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=KPartitionProblem
 * @version 0.1
 * @date 2023-04-12
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <algorithm>
#include <iostream>

#include "k_partition_problem.h"

namespace valhalla {
    namespace arrays {
        namespace k_partition_problem {
            /*

            Given an array of positive integers, partition it into `k` disjoint subsets
            that all have an equal sum, and they completely cover the array.

            Input : S[] = [7, 3, 5, 12, 2, 1, 5, 3, 8, 4, 6, 4], k = 2
            Output: [[5, 3, 8, 4, 6, 4], [7, 3, 5, 12, 2, 1]] or [[4, 5, 6, 7, 8], [1, 2, 3, 3, 4, 5, 12]]
            Explanation: S can be partitioned into 2 partitions, each having a sum of 30.

            Input : S[] = [7, 3, 5, 12, 2, 1, 5, 3, 8, 4, 6, 4], k = 3
            Output: [[2, 1, 3, 4, 6, 4], [7, 5, 8], [3, 5, 12]]
            Explanation: S can be partitioned into 3 partitions, each having a sum of 20.

            Input : S[] = [7, 3, 5, 12, 2, 1, 5, 3, 8, 4, 6, 4], k = 4
            Output: [[1, 4, 6, 4], [2, 5, 8], [12, 3], [7, 3, 5]]
            Explanation: S can be partitioned into 4 partitions, each having a sum of 15.

            Input : S[] = [7, 3, 5, 12, 2, 1, 5, 3, 8, 4, 6, 4], k = 5
            Output: [[2, 6, 4], [8, 4], [3, 1, 5, 3], [12], [7, 5]]
            Explanation: S can be partitioned into 5 partitions, each having a sum of 12.

            Input : S[] = [3, 5, 7, 3, 2, 1], k = 2
            Output: []

            */

            std::vector<std::vector<int>> Solution::getSubsets(std::vector<int> const & nums, int k) {
                std::vector<std::vector<int>> subsets;

                // We need at least three entries
                if (static_cast<int>(nums.size()) < k) return subsets;

                int sum = 0;

                for (int value : nums) sum += value;

                // If the sum is not divisible by k=3 then there is no solution
                if (sum % k != 0) return subsets;
                
                // Each subset will equal to the following
                const int each = sum / k;

                // We now look for combinations that total the above each value
                // std::set<int> processed;
                const int size = nums.size();
                bool partition = true;
                std::vector<int> sorted = nums;
                std::sort(sorted.begin(), sorted.end(), std::greater<int>());
                
                // std::vector<std::vector<int>> sums;
                for (int i = 0 ; i < k ; i++) {
                    subsets.push_back(std::vector<int>());
                } // for

                for (int value : sorted) {
                    bool added = false;
                    for (int cnt = 0 ; cnt < k ; cnt++) {
                        int sum = 0;
                        for (int num : subsets[cnt]) {
                            sum += num;
                        } // for
                        if (sum + value <= each) {
                            subsets[cnt].push_back(value);
                            added = true;
                            break;
                        } // if
                    } // for
                    if (added == false) {
                        int cnt = 0;
                        for (std::vector<int> values : subsets) {
                            cnt += values.size();
                            std::cout << "[";
                            for (int n : values)
                                std::cout << " " << n;
                            std::cout << " ]" << std::endl;
                        }
                        std::cout << "[";
                        while (cnt < size)
                            std::cout << " " << sorted[cnt++];
                        std::cout << " ]" << std::endl;
                        partition = false;
                        break;
                    } // if
                } // for

                if (partition) {
                    for (std::vector<int> values : subsets) {
                        std::cout << "[";
                        for (int value : values)
                            std::cout << " " << value;
                        std::cout << " ]" << std::endl;
                    } // for
                }

                return subsets;
            } // getSubsets
        }
    }
}
