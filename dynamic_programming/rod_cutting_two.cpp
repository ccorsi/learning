/**
 * @file rod_cutting_two.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is solution to the problem https://www.techiedelight.com/?problem=RodCuttingII
 * @version 0.1
 * @date 2023-05-21
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */


#include "rod_cutting_two.h"

namespace valhalla {
    namespace dynamic_programming {
        namespace rod_cutting_two {
            /*

            Given a rod of length n, find the optimal way to cut the rod into smaller
            rods to maximize the product of each of the smaller rod's price. Assume
            that each rod of length i has price i.

            Input: n = 4 (rod length)
            Output: 4
            Explanation: Cut the rod into two pieces of length 2 each to gain revenue
            of 2×2 = 4

            Cut				Profit
            4				4
            1, 3			(1 × 3) = 3
            2, 2			(2 × 2) = 4	  <-- optimal way
            3, 1			(3 × 1) = 3
            1, 1, 2			(1 × 1 × 2) = 2
            1, 2, 1			(1 × 2 × 1) = 2
            2, 1, 1			(2 × 1 × 1) = 2
            1, 1, 1, 1		(1 × 1 × 1 × 1) = 1

            Similarly, for n = 6, (3 × 3) = 9
            For n = 8, (2 × 3 × 3) = 18
            For n = 15, (3 × 3 × 3 × 3 × 3) = 243

            The following tests don't work using cmake on windows since it makes long into a 
            32bit signed integer instead of a 64bit signed integer.  At the moment, I am unable
            to fix this issue.

            59, 2324522934
            60, 3486784401
            61, 4649045868
            62, 6973568802
            63, 10460353203
            64, 13947137604
            65, 20920706406
            66, 31381059609
            67, 41841412812
            68, 62762119218
            69, 94143178827
            70, 125524238436
            71, 188286357654
            72, 282429536481
            73, 376572715308
            74, 564859072962
            75, 847288609443
            76, 1129718145924
            77, 1694577218886
            78, 2541865828329
            79, 3389154437772
            80, 5083731656658
            81, 7625597484987
            82, 10167463313316
            83, 15251194969974
            84, 22876792454961
            85, 30502389939948
            86, 45753584909922
            87, 68630377364883
            88, 91507169819844
            89, 137260754729766
            90, 205891132094649
            91, 274521509459532
            92, 411782264189298
            93, 617673396283947
            94, 823564528378596
            95, 1235346792567894
            96, 1853020188851841
            97, 2470693585135788
            98, 3706040377703682
            99, 5559060566555523
            100, 7412080755407364
            101, 11118121133111046
            102, 16677181699666569
            103, 22236242266222092
            104, 33354363399333138
            105, 50031545098999707
            106, 66708726798666276
            107, 100063090197999414
            108, 150094635296999121
            109, 200126180395998828
            110, 300189270593998242
            111, 450283905890997363
            112, 600378541187996484
            113, 900567811781994726
            114, 1350851717672992089
            115, 1801135623563989452
            116, 2701703435345984178
            117, 4052555153018976267
            118, 5403406870691968356

            */

            long Solution::findMaxProfit(int n) {
                long max = 0;

                /*
                    Version 1:  This version is correct but it lacks any performance boost
                                and is really a slow way of determine the maximum profit.

                for (int value = 1 ; value <= n ; value++) {
                    findProfit(n, value, value, value, max);
                }
                */

                /*
                    Version 2:  This version takes a mathematical take on the problem itself.
                                When one looks at the problem we can see that the number 3 is
                                a major factor in the solution of the maximum profit.  We can
                                then take this information to devise the solution to this
                                problem.  We then start to see how many 3's fit into n.  We
                                then look at the remaining remainder.  If it is 1, we then
                                remove a 3 from n and use 2*2 instead of 1*3 since 4 is
                                greater than 3.  If it is 2, we then just use 2 and finally
                                a remainder of 0 doesn't require any action.
                                Finally, to calculate the profit using powers of 3.  We use
                                the understanding that 3^x where x is divisible by 2 is equal
                                to 3^(x/2)^2.  If x/2 can be divisible 2 we can continue to
                                square the solution such that if x is divisible by for y times
                                then we can solve 3^(x/(2^y))^2^...^2.  This calculation is
                                much faster than just calculating 3^x.

                                The solution doesn't include a simple formula to calculate
                                the powers instead of the above optimization.
                */

                int powers = n / 3;
                int remainder = n % 3;

                switch (remainder) {
                    case 0:
                        if (powers > 0) {
                            max = 3;
                            while (--powers > 0) {
                                max *= 3;
                            } // while
                        } // if
                        break;
                    case 1:
                        if (powers > 0) {
                            if (powers > 1) {
                                max = 3;
                                while (--powers > 1) {
                                    max *= 3;
                                } // while
                                max *= 4;
                            } else {
                                max = 4;
                            } // else
                        } else {
                            max = 1;
                        }
                        break;
                    case 2:
                        if (powers > 0) {
                            max = 3;
                            while (--powers > 0) {
                                max *= 3;
                            } // while
                            max *= 2;
                        } else {
                            max = 2;
                        }
                        break;
                } // switch

                return max;
            } // findMaxProfit

            void Solution::findProfit(const int n, const int value, const int total, const long product, long & max) {
                if (total > n) {
                    // we are done
                    return;
                } // if

                if (product > max) {
                    max = product;
                } // if

                for (int idx = value ; idx <= n ; idx++) {
                    if (total + idx > n) return;
                    findProfit(n, idx, total + idx, product * static_cast<long>(idx), max);
                } // for
            }
        }
    }
}
