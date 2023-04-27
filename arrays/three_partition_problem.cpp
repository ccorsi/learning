/**
 * @file three_partition_problem.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution of the problem https://www.techiedelight.com/?problem=3PartitionProblem
 * @version 0.1
 * @date 2023-04-12
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "three_partition_problem.h"

#include <set>
#include <iostream>
#include <algorithm>

namespace valhalla {
    namespace arrays {
        namespace three_partition_problem {
            /*

            Given a set S of positive integers, determine if it can be partitioned
            into three disjoint subsets that all have the same sum, and they cover S.

            Input: S = [7, 3, 2, 1, 5, 4, 8]
            Output: true
            Explanation: S can be partitioned into three partitions
            [[7, 3], [5, 4, 1], [8, 2]], each having a sum of 10.

            Note that there can be multiple solutions to a single set.

            */

            bool Solution::partition(std::vector<int> const & S) {
                const int k = 3;

                // We need at least three entries
                if (S.size() < k) return false;

                int sum = 0;

                for (int value : S) sum += value;

                // If the sum is not divisible by k=3 then there is no solution
                if (sum % k != 0) return false;
                
                // Each subset will equal to the following
                const int each = sum / k;

                // We now look for combinations that total the above each value
                // std::set<int> processed;
                const int size = S.size();
                bool partition = true;
                std::vector<int> nums = S;
                std::sort(nums.begin(), nums.end(), std::greater<int>());

                /*
                    Version 5:
                    This version will use two techniques that have been able to
                    find all of the solutions for the current set of test cases
                    but individually they are not able to solve all of the different
                    test cases.  They only solve the test cases when combining
                    the two solutions.
                */

               // Option 1: For each, collection find max value before going to the
               //           next entry.  When 
                /*
                    Version 4:
                    Distributed the values across k sums and then manipulate tham
                    to try and get them to conform to the required solution.
                    This solution is also not complete but it does solve conditions
                    that will work if we first take the maximum consecutive entries
                    before reaching or surpassing the max value before going on to
                    the next entry.
                std::vector<std::vector<int>> sums;
                for (int i = 0 ; i < k ; i++) {
                    sums.push_back(std::vector<int>());
                } // for

                std::vector<int> tots(k, 0);
                int idx = 0;
                // evenly distribute the values across the k sums
                for(; idx < size ; idx++) {
                    int key = idx % k;
                    const int value = nums[idx];
                    if (tots[key] + value > each) {
                        break;
                    } // if
                    sums[key].push_back(value);
                    tots[key] += value;
                } // for

                if (idx == size) {
                    // we have correctly distributed the values across the k totals
                    return true;
                } // if

                while (idx < size) {
                    bool added = false;
                    const int value = nums[idx];
                    for (int cur = 0 ; cur < k ; cur++) {
                        if (tots[cur] + value <= each) {
                            tots[cur] += value;
                            sums[cur].push_back(value);
                            added = true;
                            break;
                        } // if
                    } // for
                    if (added == false) {
                        std::cout << "Unable to add value: " << value << " to equal each: " << each << std::endl;
                        std::cout << "This includes:";
                        for(int cnt = idx + 1 ; cnt < size ; cnt++)
                            std::cout << " " << nums[cnt];
                        std::cout << std::endl;
                        std::cout << "Current sets" << std::endl;
                        for (std::vector<int> values : sums) {
                            std::cout << "[";
                            for (int v : values)
                                std::cout << " " << v;
                            std::cout << " ]" << std::endl;
                        } // for
                        std::cout << "Input [";
                        for (int v : S)
                            std::cout << " " << v;
                        std::cout << " ]" << std::endl;
                        std::cout << "Sorted input [";
                        for (int v : nums)
                            std::cout << " " << v;
                        std::cout << " ]" << std::endl;
                        // We were unable to find a container that can add value to it.
                        return false;
                    } // if
                    idx++;
                } // while
                */

                /*
                    Version 3:
                    This is almost correct but it doesn't take into account that the
                    largest values need to be distributed evenly throughout the k
                    distributions.  It could distribute the largest values in a skewed
                    way that causes the algorithm to produce an incorrect answer.

                std::vector<std::vector<int>> sums;
                for (int i = 0 ; i < k ; i++) sums.push_back(std::vector<int>());
                for (int value : nums) {
                    bool added = false;
                    for (int cnt = 0 ; cnt < k ; cnt++) {
                        int sum = 0;
                        for (int num : sums[cnt]) {
                            sum += num;
                        } // for
                        if (sum + value <= each) {
                            sums[cnt].push_back(value);
                            added = true;
                            break;
                        } // if
                    } // for
                    if (added == false) {
                        int cnt = 0;
                        for (std::vector<int> values : sums) {
                            cnt += values.size();
                            std::cout << "[";
                            for (int n : values)
                                std::cout << " " << n;
                            std::cout << " ]" << std::endl;
                        }
                        std::cout << "[";
                        while (cnt < size)
                            std::cout << " " << nums[cnt++];
                        std::cout << " ]" << std::endl;
                        partition = false;
                        break;
                    } // if
                } // for

                if (partition) {
                    for (std::vector<int> values : sums) {
                        std::cout << "[";
                        for (int value : values)
                            std::cout << " " << value;
                        std::cout << " ]" << std::endl;
                    } // for
                }
                */

                /*
                    Version 2:
                    This version of the solution is better than the first one but alas it
                    can incorrectly combine the solution of accumulating the entries such
                    that it looks like you can't combine the set of values when this is
                    not the case.

                for (int cnt = 0 ; partition && cnt < k ; cnt++) {
                    std::set<int> current;
                    partition = findSum(S, processed, current, 0, each);
                } // for
                */

                /*
                    Version 1:
                    This version does not know how to handle situations that the current addition
                    could use a different combinations of digits to get the expected value.

                for(int cnt = 0 ; cnt < k ; cnt++) {
                    int value = 0;
                    // Find three entries that equal each
                    int added = 0;
                    for (int idx = 0 ; added < k && idx < size ; idx++) {
                        if (processed.find(idx) == processed.end()) {
                            if (value + S[idx] <= each) {
                                added++;
                                value += S[idx];
                                processed.insert(idx);
                                std::cout << "value: " << value << ", S[idx]: " << S[idx] << ", idx: " << idx << std::endl;
                            } // if
                        } // if
                    } // for
                    partition = (added == k && value == each);
                    std::cout << "added: " << added << ", value: " << value << ", each: " << each << ", sum: " << sum
                        << ", partition: " << ((partition) ? "true" : "false") << std::endl;
                } // for
                */

                return partition;
            } // partition

            bool Solution::findSum(std::vector<int> const & S, std::set<int> & processed, std::set<int> & current, int sum, const int each) {
                if (sum == each) {
                    std::cout << "sum: " << sum << ", each: " << each << " using:";
                    for (int idx : current)
                        std::cout << " index: " << idx << "=" << S[idx];
                    std::cout << std::endl;
                    processed.insert(current.begin(), current.end());
                    return true;
                } // if

                const int size = S.size();

                for (int idx = 0 ; idx < size ; idx++) {
                    if (current.find(idx) == current.end() && processed.find(idx) == processed.end() && sum + S[idx] <= each) {
                        std::set<int> next = current;
                        next.insert(idx);

                        if (findSum(S, processed, next, sum + S[idx], each)) {
                            return true;
                        } // if
                    } // if
                } // for

                return false;
            } // findSum
        }
    }
}
