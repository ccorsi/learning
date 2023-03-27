/**
 * @file partition_array_equal_sum.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=PartitionArrayEqualSum
 * @version 0.1
 * @date 2023-03-26
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <iostream>

#include "partition_array_equal_sum.h"

namespace valhalla {
    namespace arrays {
        namespace partition_array_equal_sum {
            /*

            Given an integer array, partition it into two contiguous subarrays having the same sum of
            elements and return the index that points to the starting of the second subarray.
            Return -1 if no partition is possible.

            Input : [6, -4, -3, 2, 3]
            Output: 2
            Explanation: The subarrays [6, -4] and [-3, 2, 3] have equal sum of 2. The second subarray
            starts from index 2.

            Input : [6, -5, 2, -4, 1]
            Output: -1
            Explanation: No equal sum partition possible.

            In case multiple solutions is possible, return the index of the first occurrence. For example,

            Input : [1, -1, 1, -1, 1, -1]
            Output: 0

            */

            int Solution::findPartitionIndex(std::vector<int> const & nums) {
                // std::cout << "[";
                // for (int value : nums)
                //     std::cout << " " << value;
                // std::cout << " ]" << std::endl;

                int partition_index = -1;

                int total = 0;

                for (int value : nums) {
                    total += value;
                } // for

                const int last = nums.size() - 1;
                int sum = 0;

                // std::cout << "Total = " << total << ", sum = " << sum << std::endl;

                for (int idx = 0 ; idx < last ; idx++) {
                    sum   += nums[idx];
                    total -= nums[idx];
                    // std::cout << "Total = " << total << ", sum = " << sum << std::endl;
                    if (sum == total) {
                        // std::cout << "sum = " << sum << ", total = " << total << ", idx = " << idx << std::endl;
                        if (partition_index != -1) {
                            partition_index = 0;
                            break;
                        } // if
                        partition_index = idx + 1;
                    } // if
                } // for

                // std::cout << partition_index << std::endl;
                return partition_index;
            } // findPartitionIndex
        }
    }
}
