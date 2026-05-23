/**
 * @file connect_n_ropes.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief The contains a solution to the problem https://www.techiedelight.com/?problem=ConnectNRopes
 * @version 0.1
 * @date 2026-04-28
 *
 * @copyright Copyright (c) 2026 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>

#include "connect_n_ropes.h"

namespace valhalla {

namespace heap {

namespace connect_n_ropes {

/*

Given n ropes of different lengths, connect them into a single rope with
minimum cost. Assume that the cost to connect two ropes is the same as the
sum of their lengths.

Input: [5, 4, 2, 8]
Output: 36
Explanation: The total cost for connecting all ropes is 6 + 11 + 19 = 36.

[5, 4, 2, 8] –> First, connect ropes of lengths 4 and 2 that will cost 6.
[5, 6, 8]    –> Next, connect ropes of lengths 5 and 6 that will cost 11.
[11, 8]      –> Finally, connect the remaining two ropes that will cost 19.

[1, 5, 2, 2, 2, 5, 5, 4]
[3, 5, 2, 2, 5, 5, 4] => 3
[3, 5, 4, 5, 5, 4] => 7
[7, 5, 5, 5, 4] => 14
[7, 5, 5, 9] => 23
[7, 10, 9] => 33
[16, 10] => 49
[26] => 75

NOTE: You can combine any two numbers within the passed vector and you are not relegated to
combining two adjacent numbers.

*/
struct entry {
    std::vector<int>::size_type m_idx;
    int m_lhs, m_rhs;

    entry(std::vector<int>::size_type idx, int lhs, int rhs) : m_idx(idx), m_lhs(lhs), m_rhs(rhs) {}

    std::vector<int>::size_type operator()() { return m_idx; }

    int sum() { return m_lhs + m_rhs; }

    friend inline bool operator<(const entry & lhs, const entry & rhs) {
        bool less = ( lhs.m_lhs + lhs.m_rhs ) > ( rhs.m_lhs + rhs.m_rhs );
        // std::cout << "1 - Comparing lhs: " << lhs << " to rhs: " << rhs << " with result = " << less << "\n";
        return less;
    }

    inline bool operator()(const entry & other) {
        bool less = ( m_lhs + m_rhs ) > ( other.m_lhs + other.m_rhs );
        // std::cout << "2 - Comparing this: " << *this << " to other: " << other << " with result = " << less << "\n";
        return less;
    }

    inline entry & operator=(const entry & other) {
        // std::cout << "Copying " << other << " to " << *this << "\n";
        // return this == &other || m_idx == other.m_idx;
        if ( this != &other ) {
           m_idx = other.m_idx;
           m_lhs = other.m_lhs;
           m_rhs = other.m_rhs;
        } // if ( this != &other )

        return *this;
    }

    friend inline std::ostream & operator<<(std::ostream & out, const entry & e) {
        return out << "entry [ m_idx=" << e.m_idx << " m_lhs=" << e.m_lhs << " m_rhs=" << e.m_rhs << " ]";
    }
};

void print(const std::vector<int> & vec, std::ostream & out = std::cout) {
    out << "[";
    for (int value : vec) {
        out << " " << value;
    } // for (int value : vec)
    out << " ]\n";
}

void nprint(const std::vector<int> & vec, std::ostream & out = std::cout) {
    out << "[";
    for (int value : vec) {
        out << " " << value;
    } // for (int value : vec)
    out << " ]";
}

int attempt_one(std::vector<int> & prices) {
    // print(prices);
    if (prices.size() == 1) {
        return prices[0];
    } // if (prices.size() == 1)

    int min = prices[0] + prices[1];
    auto min_idx = 0;
    int sum = 0;

    while ( prices.size() > 1) {
        // purge the vector after each pass
        min = prices[0] + prices[1];
        auto min_idx = 0;

        for (auto cur = 2 ; cur < prices.size() ; cur++) {
            int sum = prices[cur] + prices[cur -1];
            // std::cout << "comparing sum " << sum << " to min " << min << "\n";
            if (sum < min) {
                min_idx = cur - 1;
                min = sum;
            } // if (sum < min)
        } // for (auto cur = 2 ; cur < prices.size() ; cur++)

        // update the min_idx value
        prices[min_idx + 1] += prices[min_idx];

        // move all entries after min_idx over by one
        std::move(prices.begin() + min_idx + 1, prices.end(), prices.begin() + min_idx);

        // resize the vector
        prices.resize(prices.size() - 1);

        // print(prices); std::cout << "sum = " << sum << ", min = " << prices[min_idx] << "\n";

        sum += prices[min_idx];
    } // while ( prices.size() > 1)

    // std::cout << "sum = " << sum << "\n";
    return sum;
} // int attempt_one(std::vector<int> & prices)

int attempt_two(std::vector<int> & prices) {
    if (prices.size() == 1) {
        return prices[0];
    } // if (prices.size() == 1)

    // auto cmp = [&prices] (std::vector<int>::size_type lhs, std::vector<int>::size_type rhs) {
    //     return ( prices[lhs] + prices[lhs - 1] ) < ( prices[rhs] + prices[rhs - 1] );
    // };

    // std::priority_queue<std::vector<int>::size_type, std::vector<std::vector<int>::size_type>, decltype(cmp)> heap;
    int sum = 0;

    // print(prices);

    while (prices.size() > 1) {
        // std::priority_queue<std::vector<int>::size_type, std::vector<std::vector<int>::size_type>, decltype(cmp)> heap;
        std::priority_queue<entry> heap;
        std::priority_queue<int> h;

        for (auto idx = prices.size() - 1 ; idx > 0 ; idx--) {
            // heap.push(idx);
            entry e(idx, prices[idx - 1], prices[idx]);
            // std::cout << "Adding entry = " << e << " sum = " << e.sum() << "\n";
            heap.push(e);
            h.push(e.sum());
            e = heap.top();
            // std::cout << "Current top entry = " << e << " with sum = " << e.sum() << "\n";
            // std::cout << "Current top int = " << h.top() << "\n";
        } // for (auto idx = 1 ; idx < prices.size() ; idx++)

        // get the top entry
        entry top = heap.top();
        // get the entry index
        std::vector<int>::size_type idx = top();
        // add the popped index is incremented
        prices[idx] = top.sum();
        sum += prices[idx];
        // std::cout << "top = " << top << "\n";

        // move all entries after idx over by one
        std::move(prices.begin() + idx, prices.end(), prices.begin() + idx - 1);

        // resize the vector
        prices.resize(prices.size() - 1);

        // print(prices);

        // std::cout << "sum = " << sum << "\n";

    } // while (prices.size() > 1)

    // std::cout << "sum = " << sum << "\n";

    return sum;
} // int attempt_two(std::vector<int> & prices)

int attempt_three(std::vector<int> & prices) {
    // let us try an exhausted search to determine if what was expected from techie delight is correct
    struct Process {
        Process() = default;
        int execute(std::vector<int> & prices) {
            std::set<std::pair<std::vector<int>,int>> processed;
            int min = INT_MAX;

            // process the different combinations to determine the min using an exhaustive algorithem
            for (std::vector<int>::size_type idx = prices.size() - 1 ; idx > 0 ; idx--) {
                std::vector<int> current(prices.begin(), prices.begin() + idx);
                int cur_min = current[idx - 1] += prices[idx];
                for (auto itr = prices.begin() + idx + 1 ; itr != prices.end() ; itr++) {
                    current.push_back(*itr);
                } // for (auto itr = prices.begin() + idx + 1 ; itr != prices.end() ; itr++)
                auto result = processed.insert(std::pair(current, cur_min));
                if (result.second) {
                    if (current.size() > 1) {
                        cur_min += sum(processed, current);
                        // replace the prior instance with...
                        processed.erase((*result.first));
                        // the update version
                        processed.insert(std::pair(current, cur_min));
                    } // if (current.size() > 1)
                } else {
                    cur_min = (*result.first).second;
                    // std::cout << "Used cached cur_min = " << cur_min << " for "; print(current);
                } // if (result.second)
                if (cur_min < min) {
                    // std::cout << "Top Level New min = " << cur_min << " at index " << (idx - 1);
                    // std::cout << " From "; nprint(prices);
                    // std::cout << " To "; print(current);
                    min = cur_min;
                    continue;
                } // if (cur_min < min)
                // std::cout << "Top Level min = " << cur_min << " at index " << (idx - 1);
                // std::cout << " From "; nprint(prices);
                // std::cout << " To "; print(current);
            } // for (std::vector<int>::size_type idx = prices.size() - 1 ; idx > 0 ; idx--)

            return min != INT_MAX ? min : 0;
        }

        int sum(std::set<std::pair<std::vector<int>,int>> & processed, std::vector<int> & parent) {
            int min = INT_MAX;

            // process the parent vector into a child vector and determine the min value
            for (std::vector<int>::size_type idx = parent.size() - 1 ; idx > 0 ; idx--) {
                std::vector<int> child(parent.begin(), parent.begin() + idx);
                int cur_min = child[idx - 1] += parent[idx];
                for (auto itr = parent.begin() + idx + 1 ; itr != parent.end() ; itr++) {
                    child.push_back(*itr);
                } // for (auto itr = parent.begin() + idx + 1 ; itr != parent.end() ; itr++)
                // determine if the child vector has been processed already
                auto & result = processed.insert(std::pair(child, cur_min));
                if (result.second) {
                    if (child.size() > 1) {
                        cur_min += sum(processed, child);
                        // remove the prior one since it has been updated and...
                        processed.erase((*result.first));
                        // replace it with the updated version
                        processed.insert(std::pair(child, cur_min));
                    } // if (child.size() > 1)
                } else {
                    cur_min = (*result.first).second;
                    // std::cout << "Used cached cur_min = " << cur_min << " for "; print(child);
                } // if (result.second)
                if (cur_min < min) {
                    // std::cout << "New min = " << cur_min << " at index " << (idx - 1);
                    // std::cout << " From "; nprint(parent);
                    // std::cout << " To "; print(child);
                    min = cur_min;
                } // if (cur_min < min)
            } // for (std::vector<int>::size_type idx = parent.size() - 1 ; idx > 0 ; idx--)

            return min != INT_MAX ? min : 0;
        }
    };

    return Process().execute(prices);
} // int attempt_three(std::vector<int> & prices)

int attempt_four(std::vector<int> & prices) {
    if (prices.empty()) {
        return 0;
    } // if (prices.empty())

    if (prices.size() == 1) {
        return prices[0];
    } // if (prices.size() == 1)

    int min = INT_MAX;
    std::queue<std::pair<std::vector<int>, int>> sums;
    sums.push(std::pair(prices, 0));

    while (sums.empty() == false) {
        // get a reference to the first entry from the queue
        auto current = sums.front();
        // remove the first entry from the queue
        sums.pop();

        if (current.first.size() == 1) {
            const int sum = current.second;
            if (sum < min) {
                min = sum;
            } // if (sum < min)
            continue;
        } // if (current.first.size() == 1)

        // add the different combinations to the queue
        for (auto idx = current.first.size() - 1 ; idx > 0 ; idx--) {
            std::vector<int> child(current.first.begin(), current.first.begin() + idx);
            child[idx - 1] += current.first[idx];
            for (auto itr = current.first.begin() + idx + 1 ; itr != current.first.end() ; itr++) {
                child.push_back(*itr);
            } // for (auto itr = current.first.begin() + idx + 1 ; itr != current.first.end() ; itr++)
            // add a new prices vector generated from the current prices vector and increase the sum
            const int sum = current.second + child[idx - 1];
            if (sum < min) {
                // only add current sums that are less than the current min
                sums.push(std::pair(child, sum));
            } // if (sum < min)
        } // for (auto idx = current.first.size() - 1 ; idx > 0 ; idx--)
    } // while (sums.empty() == false)

    return min;
} // int attempt_four(std::vector<int> & prices)

// NOTE: The above attempts all incorrectly assumed that I was only allowed to combined
//       the two adjacent values in the prices vector.  The next attempts removes that
//       requirement.

int attempt_five(std::vector<int>  & prices) {
    int min = 0;

    std::sort(prices.begin(), prices.end(), std::less<int>());

    // print(prices);

    for (auto idx = 0 ; idx + 1 < prices.size() ; idx += 2) {
        int cur = prices[idx + 1] + prices[idx];
        min += cur;
        prices.push_back(cur);
    } // for (auto idx = 0 ; idx + 1 < prices.size() ; idx++)

    return min;
} // int attempt_five(std::vector<int>  & prices)

int attempt_six(std::vector<int> & prices) {
    int sum = 0;

    std::priority_queue<int, std::vector<int>, std::greater<int>> heap(prices.begin(), prices.end());

    while (heap.size() > 1) {
        // pop the two top entries and add them together
        int cur = heap.top(); heap.pop();
        cur += heap.top(); heap.pop();
        // push the combined value back onto the heap
        heap.push(cur);
        // update the sum by adding the popped values
        sum += cur;
    } // while (heap.size() > 1)

    return sum;
} // int attempt_six(std::vector<int> & prices)

int Solution::findMinCost(std::vector<int> & prices) {
    return attempt_six(prices);
} // findMinCost

} // namespace connect_n_ropes

} // namespace heap

} // namespace valhalla
