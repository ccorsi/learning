/**
 * @file coin_change_problem.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=CoinChangeProblem
 * @version 0.1
 * @date 2023-05-03
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "coin_change_problem.h"

#include <algorithm>
#include <iostream>

namespace valhalla {
    namespace arrays {
        namespace coin_change_problem {
            /*

            Given an unlimited supply of coins of given denominations, find the minimum number of
            coins required to get the desired change.

            Input: S = [1, 3, 5, 7], target = 15
            Output: 3
            Explanation: The minimum number of coins required is 3 (7 + 7 + 1) or (5 + 5 + 5) or (3 + 5 + 7)

            Input: S = [1, 3, 5, 7], target = 18
            Output: 4
            Explanation: The minimum number of coins required is 4 (7 + 7 + 3 + 1) or (5 + 5 + 5 + 3) or (7 + 5 + 5 + 1)

            If desired change is not possible, the solution should return -1.

            Input: S = [2, 4, 6, 8], target = 15
            Output: -1

            */

            int Solution::findMinCoins(std::vector<int> const & S, int target) {
                int minCoins = -1;

                std::vector<int> coins = S;

                std::sort(coins.rbegin(), coins.rend());

                const int size = coins.size();

                int idx = 0;

                // skip values that are larger than target
                while (idx < size && coins[idx] > target) idx++;

                while (idx < size) {
                    const int value = coins[idx++];
                    // Determine the number of possible counts that value can be added to make up target
                    int count = target / value;
                    // Only set it to the minimum between the current value and what can be possible
                    if (minCoins != -1 && count > minCoins) {
                        count = minCoins;
                    } // if
                    int sum = count * value;

                    while (count > 0) {
                        findMinCoin(coins, target, idx, sum, count, minCoins);
                        sum -= value;
                        count--;
                    } // while
                } // while

                return minCoins;
            } // findMinCoins

            void Solution::findMinCoin(std::vector<int> const & coins, int target, int idx, int sum, int count, int & minCoins) {
                // std::cout << "sum = " << sum << ", target = " << target << ", count = " << count << std::endl;
                if (target < sum || (minCoins != -1 && minCoins < count)) {
                    // we are done
                    return;
                }

                if (sum == target) {
                    if (minCoins == -1 || count < minCoins) {
                        minCoins = count;
                    } // if
                    return;
                } // if

                const int size = coins.size();

                while (idx < size) {
                    const int value = coins[idx++];
                    int total = sum + value;
                    int cnt = count + 1;

                    while ((minCoins == -1 || cnt <= minCoins) && total <= target) {
                        findMinCoin(coins, target, idx, total, cnt, minCoins);
                        total += value;
                        cnt++;
                    } // while
                } // while
            }
        }
    }
}
