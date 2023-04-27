/**
 * @file three_partition_problem_two.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=3PartitionProblemII
 * @version 0.1
 * @date 2023-04-12
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <iostream>
#include <algorithm>

#include "three_partition_problem_two.h"

namespace valhalla {
    namespace arrays {
        namespace three_partition_problem_two {
            /*

            Given an array of positive integers, which can be partitioned into three
            disjoint subsets having the same sum, return the partitions.

            Input: S = [7, 3, 2, 1, 5, 4, 8]
            Output: [[7, 3], [5, 4, 1], [8, 2]]
            Explanation: S can be partitioned into three partitions, each having a sum of 10.

            Note that there can be multiple solutions to a single set, the procedure
            can return any one of them.

            */

            std::vector<std::vector<int>> Solution::partition(std::vector<int> const & S) {
                std::vector<std::vector<int>> partitions;

                const int k = 3;

                // We need at least three entries
                if (S.size() < k) return partitions;

                int sum = 0;

                for (int value : S) sum += value;

                // If the sum is not divisible by 3 then there is no solution
                if (sum % k != 0) return partitions;
                
                // Each subset will equal to the following
                const int each = sum / k;

                // We now look for combinations that total the above each value
                std::set<int> processed;
                const int size = S.size();

                // Make copy of the integer valeus
                std::vector<int> nums = S;
                // Sort the copied integer array from greatest to lowest
                std::sort(nums.rbegin(), nums.rend());

                // Initialize the k arrays in the partitions solution
                partitions = std::vector<std::vector<int>>(k, std::vector<int>());

                // create a sums vector to simplify addition
                std::vector<int> sums(k, 0);

                // Step 1: Add to the each array the current consecutive values that are
                //         less than or equal to the expected sum.
                int idx = 0;

                for (int cnt = 0 ; cnt < k ; cnt++) {
                    int subsum = 0;
                    while (idx < size && subsum + nums[idx] <= each) {
                        partitions[cnt].push_back(nums[idx]);
                        subsum += nums[idx++];
                    } // while
                    sums[cnt] = subsum;
                } // for

                if (idx == size) {
                    // we are done
                    return partitions;
                } // if

                while (idx < size) {
                    const int value = nums[idx];
                    bool added = false;
                    for (int cnt = 0 ; cnt < k ; cnt++) {
                        if (sums[cnt] + value <= each) {
                            sums[cnt] += value;
                            partitions[cnt].push_back(value);
                            break;
                        } // if
                    } // for
                    if (added == false) break;
                } // while

                if (idx == size) {
                    // we are done
                    return partitions;
                } // if

                // Step 2: If step 1 doesn't find a solution.  We now try to evenly
                //         distribute the values across the arrays until we can't.

                // Clear current values and sum from each.
                for (int cnt = 0 ; cnt < k ; cnt++) {
                    partitions[cnt].clear();
                    sums[cnt] = 0;
                } // while
                
                idx = 0;

                while (idx < size) {
                    const int key = idx % k, value = nums[idx];

                    if (sums[key] + value > each) break;

                    sums[key] += value;
                    partitions[key].push_back(value);
                    idx++;
                } // while

                if (idx == size) {
                    // we are done
                    return partitions;
                } // if


                while (idx < size) {
                    bool added = false;
                    const int value = nums[idx];
                    for (int cnt = 0 ; cnt < k ; cnt++) {
                        if (sums[cnt] + value <= each) {
                            sums[cnt] += value;
                            partitions[cnt].push_back(value);
                            added = true;
                            break;
                        }
                    } // for
                    if (added == false) break;
                    idx++;
                } // while

                if (idx < size) {
                    partitions.clear();
                } // if

                return partitions;
            } //partition

            bool Solution::findSum(std::vector<std::vector<int>> & partitions, std::vector<int> const & S, std::set<int> & processed, std::set<int> & current, int sum, const int each) {
                if (sum == each) {
                    std::vector<int> values;
                    std::cout << "sum: " << sum << ", each: " << each << " using:";
                    for (int idx : current) {
                        values.push_back(S[idx]);
                        processed.insert(idx);
                        std::cout << " index: " << idx << "=" << S[idx];
                    } // for
                    std::cout << std::endl;
                    partitions.push_back(values);
                    return true;
                } // if

                const int size = S.size();

                for (int idx = 0 ; idx < size ; idx++) {
                    if (current.find(idx) == current.end() && processed.find(idx) == processed.end() && sum + S[idx] <= each) {
                        std::set<int> next = current;
                        next.insert(idx);

                        if (findSum(partitions, S, processed, next, sum + S[idx], each)) {
                            return true;
                        } // if
                    } // if
                } // for

                return false;
            } // findSum
        }
    }
}
