/**
 * @file combinations_ten.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=CombinationsX
 * @version 0.1
 * @date 2023-03-06
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "combinations_ten.h"

/*

Given a positive number `n` and a mobile keypad having digits from 0 to 9 associated with each key, count the total
possible combinations of digits having length `n`. You can start with any digit and press only four adjacent keys of
any digit. The keypad also contains `*` and `#` keys, which you're not allowed to press.

keypad = {
	{ '1', '2', '3' },
	{ '4', '5', '6' },
	{ '7', '8', '9' },
	{ '*', '0', '#' }
};

Input: n = 2
Output: 36
Explanation: Total possible combinations are 36 [00, 08, 11, 12, 14, 21, 22, 23, 25, 32, 33, 36, 41, 44, 45, 47, … ,96, 98, 99]

*/

int valhalla::dynamic_programming::combinations_ten::Solution::findCombinations(std::vector<std::vector<char>> const & keypad, int n) {
    std::set<std::vector<char>> combinations;
    std::set<std::vector<char>> visited;

    if (n > 0) {
        const int rows = keypad.size(), cols = keypad[0].size();
        for (int row = 0 ; row < rows ; row++) {
            for (int col = 0 ; col < cols ; col++) {
                findCombination(visited, combinations, std::vector<char>(), keypad, n, 0, std::pair(row,col));
            } // for
        } // for
    } // if

    return combinations.size();
}

void valhalla::dynamic_programming::combinations_ten::Solution::findCombination(std::set<std::vector<char>> & visited, std::set<std::vector<char>> & combinations, std::vector<char> const & combination, std::vector<std::vector<char>> const & keypad, int n, int current, std::pair<int,int> const & point) {
    static const std::vector<std::pair<int,int>> moves = { { 1, 0 }, { 0, 1 }, { -1, 0 }, { 0, -1 }, { 0, 0 } };

    current++;

    for (std::pair<int,int> move : moves) {
        std::pair<int,int> next_point = point;
        next_point.first  += move.first;
        next_point.second += move.second;

        if (is_valid_move(keypad, next_point)) {
            std::vector<char> next = combination;
            next.push_back(keypad[next_point.first][next_point.second]);
            if (visited.insert(next).second) {
                if (current == n) {
                    combinations.insert(next);
                    continue;
                } // if
                findCombination(visited, combinations, next, keypad, n, current, next_point);
            } // if
        } // if
    } // for
}

bool valhalla::dynamic_programming::combinations_ten::Solution::is_valid_move(std::vector<std::vector<char>> const & keypad, std::pair<int,int> const & point) {
    return point.first > -1 && static_cast<std::vector<char>::size_type>(point.first) < keypad.size() && point.second > -1
        && static_cast<std::vector<char>::size_type>(point.second) < keypad[0].size()
        && keypad[point.first][point.second] != '*' && keypad[point.first][point.second] != '#';
}

/*
This is a test run without using the visited instance:

[==========] Running 7 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 7 tests from CombinationsTenTests/CombinationsTenFixture
[ RUN      ] CombinationsTenTests/CombinationsTenFixture.CombinationsTenTests/0
[       OK ] CombinationsTenTests/CombinationsTenFixture.CombinationsTenTests/0 (0 ms)
[ RUN      ] CombinationsTenTests/CombinationsTenFixture.CombinationsTenTests/1
[       OK ] CombinationsTenTests/CombinationsTenFixture.CombinationsTenTests/1 (2 ms)
[ RUN      ] CombinationsTenTests/CombinationsTenFixture.CombinationsTenTests/2
[       OK ] CombinationsTenTests/CombinationsTenFixture.CombinationsTenTests/2 (40 ms)
[ RUN      ] CombinationsTenTests/CombinationsTenFixture.CombinationsTenTests/3
[       OK ] CombinationsTenTests/CombinationsTenFixture.CombinationsTenTests/3 (802 ms)
[ RUN      ] CombinationsTenTests/CombinationsTenFixture.CombinationsTenTests/4
[       OK ] CombinationsTenTests/CombinationsTenFixture.CombinationsTenTests/4 (6334 ms)
[ RUN      ] CombinationsTenTests/CombinationsTenFixture.CombinationsTenTests/5
[       OK ] CombinationsTenTests/CombinationsTenFixture.CombinationsTenTests/5 (61582 ms)
[ RUN      ] CombinationsTenTests/CombinationsTenFixture.CombinationsTenTests/6
[       OK ] CombinationsTenTests/CombinationsTenFixture.CombinationsTenTests/6 (91609 ms)
[----------] 7 tests from CombinationsTenTests/CombinationsTenFixture (160373 ms total)

[----------] Global test environment tear-down
[==========] 7 tests from 1 test suite ran. (160373 ms total)
[  PASSED  ] 7 tests.

This is a test run using the visited instance:

[==========] Running 7 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 7 tests from CombinationsTenTests/CombinationsTenFixture
[ RUN      ] CombinationsTenTests/CombinationsTenFixture.CombinationsTenTests/0
[       OK ] CombinationsTenTests/CombinationsTenFixture.CombinationsTenTests/0 (0 ms)
[ RUN      ] CombinationsTenTests/CombinationsTenFixture.CombinationsTenTests/1
[       OK ] CombinationsTenTests/CombinationsTenFixture.CombinationsTenTests/1 (1 ms)
[ RUN      ] CombinationsTenTests/CombinationsTenFixture.CombinationsTenTests/2
[       OK ] CombinationsTenTests/CombinationsTenFixture.CombinationsTenTests/2 (23 ms)
[ RUN      ] CombinationsTenTests/CombinationsTenFixture.CombinationsTenTests/3
[       OK ] CombinationsTenTests/CombinationsTenFixture.CombinationsTenTests/3 (442 ms)
[ RUN      ] CombinationsTenTests/CombinationsTenFixture.CombinationsTenTests/4
[       OK ] CombinationsTenTests/CombinationsTenFixture.CombinationsTenTests/4 (1878 ms)
[ RUN      ] CombinationsTenTests/CombinationsTenFixture.CombinationsTenTests/5
[       OK ] CombinationsTenTests/CombinationsTenFixture.CombinationsTenTests/5 (7967 ms)
[ RUN      ] CombinationsTenTests/CombinationsTenFixture.CombinationsTenTests/6
[       OK ] CombinationsTenTests/CombinationsTenFixture.CombinationsTenTests/6 (33424 ms)
[----------] 7 tests from CombinationsTenTests/CombinationsTenFixture (43739 ms total)

[----------] Global test environment tear-down
[==========] 7 tests from 1 test suite ran. (43739 ms total)
[  PASSED  ] 7 tests.

The above solution was faster but still not fast enough to not exceed techie delight time
limit of 15 seconds.
 */
