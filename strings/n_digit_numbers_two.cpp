/**
 * @file n_digit_numbers_two.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=NDigitNumbersII
 * @version 0.1
 * @date 2025-02-19
 *
 * @copyright Copyright (c) 2025 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */


#include "n_digit_numbers_two.h"
#include <iostream>
#include <list>

namespace valhalla {

namespace strings {

namespace n_digit_numbers_two {

/*

Given a positive integer n, find all n–digit binary numbers having more 1’s than 0’s for any prefix of the number.

Input : n = 4
Output: {"1111", "1110", "1101", "1100", "1011", "1010"}

Note that 1001 will not form part of the solution as it violates the problem constraints (1001 has 2 zeros and 1
one at third position). The same applies to all other 4–digit binary numbers.

*/

std::unordered_set<std::string> solution_three(int n) {
    std::unordered_set<std::string> combinations;

    if (n > 0) {
        std::list<std::pair<int,std::string>> prefixes;
        prefixes.push_back(std::pair(0,""));

        while ( ! prefixes.empty() ) {
            auto next = prefixes.front(); prefixes.pop_front();
            int ones = next.first;
            std::string prefix = next.second;
            // std::cout << "Processing: " << prefix << '\n';

            int size = static_cast<int>(prefix.size());

            if (size == n) {
                combinations.insert(prefix);
                continue;
            } // if (prefix.size() == n)

            prefix += '1';
            if (prefix.size() == n) {
                combinations.insert(prefix);
                continue;
            }

            ones++;
            prefixes.push_back(std::pair(ones,prefix));
            int zeroes = static_cast<int>(prefix.size() - ones);

            while (zeroes < ones && zeroes + ones < n) {
                prefix += '0';
                zeroes++;
                if (prefix.size() == n) {
                    combinations.insert(prefix);
                    continue;
                }
                prefixes.push_back(std::pair(ones,prefix));
            } // while (zeroes < ones && zeroes + ones < n)

        } // while ( ! prefixes.empty() )

    } // if (n > 0)

    return combinations;
} // solution_three

std::unordered_set<std::string> attempt_two(int n) {
    std::unordered_set<std::string> combinations;

    if (n > 0) {
        std::list<std::string> prefixes;
        prefixes.push_back("");

        std::string str(n, '1');
        // std::cout << "Inserted: " << str << '\n';
        combinations.insert(str);

        while (prefixes.empty() == false) {
            std::string str = prefixes.front(); prefixes.pop_front();
            // std::cout << "Processing: " << str << "\n";

            const int size = static_cast<int>(str.size());

            if (size == n) {
                // std::cout << "Inserted: " << str << '\n';
                combinations.insert(str);
                continue;
            }

            for (int len = 1 ; len + size <= n ; len++ ) {
                std::string prefix = str + std::string(len, '1');
                // std::cout << "prefix: " << prefix << "\n";
                if (prefix.size() == n) {
                    // std::cout << "Inserted: " << prefix << '\n';
                    combinations.insert(prefix);
                    continue;
                }
                prefixes.push_back(prefix);
                for (int zeros = 1 ; zeros <= len && zeros + len + size <= n; zeros++) {
                    prefixes.push_back(prefix + std::string(zeros, '0'));
                    // std::cout << "2: " << prefixes.back() << "\n";
                }
            }

        }
    }

    return combinations;
} // attempt_two

std::unordered_set<std::string> attempt_one(int n) {
    std::unordered_set<std::string> combinations;

    if (n > 0) {
        std::list<std::string> prefixes;
        // n has to be greater than 0 to be able to find anything
        for (int len = 1 ; len <= n ; len++) {
            std::string prefix = std::string(len, '1');
            if (prefix.size() == n) {
                combinations.insert(prefix);
                continue;
            }
            for (int zeros = 1 ; zeros <= len && zeros + len <= n; zeros++) {
                prefixes.push_back(prefix + std::string(zeros, '0'));
                // std::cout << "1: " << prefixes.back() << "\n";
            }
        }

        std::string str(n, '1');
        std::cout << "Inserted: " << str << '\n';
        combinations.insert(str);

        while (prefixes.empty() == false) {
            std::string str = prefixes.front(); prefixes.pop_front();
            // std::cout << "Processing: " << str << "\n";

            const int size = static_cast<int>(str.size());

            if (size == n) {
                std::cout << "Inserted: " << str << '\n';
                combinations.insert(str);
                continue;
            }

            for (int len = 1 ; len + size <= n ; len++ ) {
                std::string prefix = str + std::string(len, '1');
                // std::cout << "prefix: " << prefix << "\n";
                if (prefix.size() == n) {
                    std::cout << "Inserted: " << prefix << '\n';
                    combinations.insert(prefix);
                    continue;
                }
                for (int zeros = 1 ; zeros <= len && zeros + len <= n; zeros++) {
                    prefixes.push_back(prefix + std::string(zeros, '0'));
                    // std::cout << "2: " << prefixes.back() << "\n";
                }
                prefixes.push_back(prefix);
            }

        }
    }

    return combinations;
} // attempt_one

std::unordered_set<std::string> Solution::findNDigitNumbers(int n) {
    return solution_three(n);
} // findNDigitNumbers

} // namespace n_digit_numbers_two

} // namespace strings

} // namespace valhalla
