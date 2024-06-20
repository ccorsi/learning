/**
 * @file tiles_problem.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=TilesProblem
 * @version 0.1
 * @date 2023-06-19
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <iostream>
#include <utility>
#include <vector>
#include <set>
#include <algorithm>
#include <sstream>
#include <list>

#include "tiles_problem.h"

namespace valhalla {
    namespace matrices {
        namespace tiles_problem {
            /**
             * NOTE: Since I still can't build a 64bit version on windows using cmake.  The following
             *       output will not work for the current 32bit implementation:
             *
                69, 2489191330
                70, 3435774958
                71, 4742323107
                72, 6545722210
                73, 9034913540
                74, 12470688498
                75, 17213011605
                76, 23758733815
                77, 32793647355
                78, 45264335853
                79, 62477347458
                80, 86236081273
                81, 119029728628
                82, 164294064481
                83, 226771411939
                84, 313007493212
                85, 432037221840
                86, 596331286321
                87, 823102698260
                88, 1136110191472
                89, 1568147413312
                90, 2164478699633
                91, 2987581397893
                92, 4123691589365
                93, 5691839002677
                94, 7856317702310
                95, 10843899100203
                96, 14967590689568
                97, 20659429692245
                98, 28515747394555
                99, 39359646494758
                100, 54327237184326
                101, 74986666876571
                102, 103502414271126
                103, 142862060765884
                104, 197189297950210
                105, 272175964826781
                106, 375678379097907
                107, 518540439863791
                108, 715729737814001
                109, 987905702640782
                110, 1363584081738689
                111, 1882124521602480
                112, 2597854259416481
                113, 3585759962057263
                114, 4949344043795952
                115, 6831468565398432
                116, 9429322824814913
                117, 13015082786872176
                118, 17964426830668128
                119, 24795895396066560
                120, 34225218220881473
                121, 47240301007753649
                122, 65204727838421777
                123, 90000623234488337
                124, 124225841455369810
                125, 171466142463123459
                126, 236670870301545236
                127, 326671493536033573
                128, 450897334991403383
                129, 622363477454526842
                130, 859034347756072078
                131, 1185705841292105651
                132, 1636603176283509034
                133, 2258966653738035876
                134, 3118001001494107954
                135, 4303706842786213605
                136, 5940310019069722639
                137, 8199276672807758515
             *
             */

            long Solution::combination_one(int n, int r) {
                /*
                    Combination Solution 1: This solution works but doesn't know how to
                                            handle a long overflow but the resulting C(n,r)
                                            is not an overflow value.
                */
                if (n < 0) {
                    /*
                        for n < 0 then

                        C(-n,r) = (-1)^r * C(n + r - 1, r)

                    */
                    return combination_one( -1 * n + r - 1, r) * ( (r & 1) ? -1 : 1 );
                } // if (n < 0)

                long result = 1;
                int p = n - r;
                int s = std::max(r, p);
                int e = std::min(r, p);

                std::cout << "n = " << n << ", r = " << r;

                while (s++ < n) {
                    result *= s;
                } // while (r++ < n)

                for (auto v = 0 ; v++ < e ; ) {
                    result /= v;
                } // for (auto v = 0 ; ++v < e ; )

                std::cout << ", C(" << n << "," << r << ") = " << result << "\n";

                return result;
            } // combination_one

            long Solution::combination_two(int n, int r) {
                /*
                    Combination Solution 2: This solution does handle most of the overflow cases but
                                            it still doesn't handle all possible overflow cases where
                                            the result of C(n,r) doesn't return an overflow value.
                                            It is possible that the remaining dividing values cannot
                                            divide the current result and the remaining multipling
                                            values create an overflow.  This case will cause an infinite
                                            loop.
                */
                if (n == 32 && r == 12) {
                    n++;
                    n--;
                }
                if (n < 0) {
                    /*
                        for n < 0 then

                        C(-n,r) = (-1)^r * C(n + r - 1, r)

                    */
                    return combination_two( -1 * n + r - 1, r) * ( (r & 1) ? -1 : 1 );
                } // if (n < 0)

                long result = 1;
                int p = n - r;
                int s = std::max(r, p);
                int e = std::min(r, p);
                std::stringstream sstr;

                sstr << "n = " << n << ", r = " << r;

                while (s < n) {
                    long temp = result * (s + 1);
                    if (temp / (s + 1) != result) break;
                    result = temp;
                    s++;
                } // while (s < n)

                if (s < n) {
                    // we are dealing with an overflow
                    std::set<int> remaining;

                    for (auto v = 0 ; v++ < e ; ) {
                        if (result % v == 0)
                            result /= v;
                        else
                            remaining.insert(v);
                    } // for (auto v = 0 ; ++v < e ; )

                    while (s < n) {
                        int prior = s;
                        std::cout << "Current result = " << result << " and s = " << s;
                        while (s < n) {
                            long temp = result * (s + 1);
                            if (temp / (s + 1) != result) break;
                            result = temp;
                            s++;
                        } // while (s < n)
                        std::cout << " updated result = " << result << " and s = " << s << ", n = " << n << ", r = " << r;

                        std::set<int> remove;

                        for (auto v : remaining) {
                            if (result % v == 0) {
                                result /= v;
                                remove.insert(v);
                            } // if (result % v == 0)
                        } // for (auto v : remaining)

                        std::cout << ", divided by [";
                        for (auto v : remove) {
                            std::cout << " " << v;
                            remaining.erase(remaining.find(v));
                        } // for (auto v : remove)
                        std::cout << " ] remaining [";
                        for (auto v : remaining) {
                            std::cout << " " << v;
                        } // for (auto v : remove)
                        std::cout << " ]\n";

                        if (remaining.empty()) {
                            std::cout << "BREAKING s = " << s << ", remaining [";
                            for (auto v : remaining) {
                                std::cout << " " << v;
                            } // for (auto v : remaining)
                            std::cout << " ]\n";
                            break;
                        }
                        // if (prior == s) break;
                    } // while (s < n)
                } else {
                    for (auto v = 0 ; v++ < e ; ) {
                        result /= v;
                    } // for (auto v = 0 ; ++v < e ; )
                } // if (s < n)

                std::cout << sstr.str() << ", C(" << n << "," << r << ") = " << result << "\n";

                return result;
            } // combination_two

            long Solution::combination_three(int n, int r) {
                /*
                    Combination Solution 3: This has the same issue as combination solution 2!
                */
                if (n == 32 && r == 12) {
                    n++;
                    n--;
                }
                if (n < 0) {
                    /*
                        for n < 0 then

                        C(-n,r) = (-1)^r * C(n + r - 1, r)

                    */
                    return combination_three( -1 * n + r - 1, r) * ( (r & 1) ? -1 : 1 );
                } // if (n < 0)

                long result = 1;
                int p = n - r;
                const int s = std::max(r, p);
                const int e = std::min(r, p);
                std::stringstream sstr;

                sstr << "n = " << n << ", r = " << r;

                p = n;
                while (p >= s) {
                    long temp = result * p;
                    if (temp / p != result) break;
                    result = temp;
                    p--;
                } // while (p >= s)

                if (p >= s) {
                    // we are dealing with an overflow
                    std::list<int> remaining;

                    for (auto v = e ; v > 0 ; v--) {
                        if (result % v == 0)
                            result /= v;
                        else
                            remaining.push_back(v);
                    } // for (auto v = 0 ; v++ < e ; )

                    while (p >= s) {
                        std::cout << "Current result = " << result << " and p = " << p;
                        while (p >= s) {
                            long temp = result * p;
                            if (temp / p != result) break;
                            result = temp;
                            p--;
                        } // while (p >= s)
                        std::cout << " updated result = " << result << " and p = " << p
                                << ", n = " << n << ", r = " << r << ", divided by [";

                        for(size_t cnt = 0, size = remaining.size() ; cnt < size ; cnt++ ) {
                            // pop the front value which is the largest value at the moment
                            auto v = remaining.front(); remaining.pop_front();
                            // check if it is divisible by v
                            if (result % v == 0) {
                                result /= v;
                                std::cout << " " << v;
                            } else {
                                // push it back on the list since result was not divisible by v
                                remaining.push_back(v);
                            } // if (result % v == 0)
                        } // for() auto size = remaining.size, cnt = 0 ; cnt < size ; cnt++)

                        std::cout << " ] remaining [";
                        for (auto v : remaining) {
                            std::cout << " " << v;
                        } // for (auto v : remove)
                        std::cout << " ]\n";
                    } // while (p >= s)
                } else {
                    for (auto v = 0 ; v++ < e ; ) {
                        result /= v;
                    } // for (auto v = 0 ; ++v < e ; )
                } // if (s < n)

                std::cout << sstr.str() << ", C(" << n << "," << r << ") = " << result << "\n";

                return result;
            } // combination_three

            long Solution::combination(int n, int r) {
                /*
                    Combination solution 4: This version takes into account that we can always divide
                                            the remaining numerators with the denominators.  Thus
                                            the remaining numerator values only need to be multiplied
                                            and that will give you the result for C(n,r).
                */
                if (n < 0) {
                    /*
                        for n < 0 then

                        C(-n,r) = (-1)^r * C(n + r - 1, r)

                    */
                    return combination( -1 * n + r - 1, r) * ( (r & 1) ? -1 : 1 );
                } // if (n < 0)

                int p = n - r;
                int s = std::max(r, p);
                int e = n - s;

                std::vector<int> numerator;
                std::list<int> denominator;

                // Push all number multiples on a vector
                while (s++ < n) {
                    numerator.push_back(s);
                } // while (s++ < n)

                // Push all denominator divisors on a list
                while (e > 1) {
                    denominator.push_back(e--);
                } // while (e > 0)

                long result = 1;

                // First pass of reducing the numerator values using the current denominators
                for (auto & n : numerator) {
                    // check if we've already divided the numerators with all of the denominators
                    if (denominator.empty()) {
                        break;
                    } // if (denominator.empty())

                    auto size = denominator.size();

                    for (int cnt = 0 ; cnt < size ; cnt++) {
                        int v = denominator.front(); denominator.pop_front();
                        if (n % v == 0) {
                            // the current numerator is divisible by the current denominator
                            n = n / v;
                        } else {
                            // the current numberator is not divisible by the current denominator
                            denominator.push_back(v);
                        } // if (n % v == 0)
                    } // for (int cnt = 0 ; cnt < size ; cnt++)
                } // for (auto & n : numerator)

                // multiple the current set of numerators together one by one
                for (auto v : numerator) {
                    result *= v;

                    // check if any denominators are left
                    if (! denominator.empty()) {
                        // we are performing the same process as above except on the current
                        // multipled result to insure that the result is not going to cause an
                        // overflow.
                        auto size = denominator.size();

                        for (int cnt = 0 ; cnt < size ; cnt++) {
                            int d = denominator.front(); denominator.pop_front();
                            if (result % d == 0) {
                                result = result / d;
                            } else {
                                denominator.push_back(d);
                            } // if (n % v == 0)
                        } // for (int cnt = 0 ; cnt < size ; cnt++)
                    } // if (! denominator.empty())
                } // for (auto v : numerator)

                // std::cout << "C(" << n << "," << r << ") = " << result << "\n";

                return result;
            } // combination

            /*

            Given an `n × 4` matrix where `n` is a positive number, find the number of ways to
            fill the matrix with `1 × 4` tiles.

            Input: n = 5
            Output: 3
            Explanation: There are three ways to place `1 × 4` tiles in a `5 × 4` matrix:

            • Place all 5 tiles horizontally.
            • Place 4 tiles vertically in the first four rows and 1 tile horizontally in the
                last row.
            • Place 1 tile horizontally in the first row and adjust 4 tiles vertically in
                the remaining rows.

            Input: n = 6
            Output: 4
            Explanation: There are 4 ways to place `1 × 4` tiles in a `6 × 4` matrix:

            • Place all 6 tiles horizontally.
            • Place 4 tiles vertically in the first four rows and the remaining 2 tiles
                horizontally in the last two rows.
            • Place 2 tiles horizontally in the first two rows, and adjust the remaining
                4 tiles vertically in the remaining rows.
            • Place 2 tiles horizontally in the first and last row, and adjust the
                remaining 4 tiles vertically in the middle rows.

            */

            long Solution::findTotalWays(int n) {
                // std::stringstream str;

                // str << "n = " << n;

                // Solution: This is a mathematical problem that can be broken down into
                //           different sections of addition.  Each time that we have
                //           more than 3 rows then we can use the formula n - 3 + fours.
                long total = 0;

                if (n == 0) {
                    return total;
                } // if (n == 0)

                total++;

                int fours = 0, mask = ~3;

                // while four or greater
                while (n & mask) {
                    fours++;
                    n -= 4;
                    total += combination(n + fours, fours);
                    // std::cout << "total = " << total << "\n";
                }

                /*
                    Solution 1: This would only work for n less than 8.  It is an incomplete
                                solution to the problem.  It only solves two of the many
                                cases.
                */
                // while (n & mask) {
                //     fours++;
                //     total += n - 4 + fours;
                //     n -= 4;
                // }
                // if (n < 4) {
                //     total = n > 0 ? 1 : 0;
                // } else {
                //     total = n - 3 + 1;
                // }

                // return n ? ++total : total;

                // std::cout << str.str() << " gives total = " << total << "\n";
                return total;
            } // findTotalWays
        }
    }
}
