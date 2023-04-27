/**
 * @file surpasser_count.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=SurpasserCount
 * @version 0.1
 * @date 2023-04-12
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */


#include "surpasser_count.h"

namespace valhalla {
    namespace arrays {
        namespace surpasser_count {
            /*

            Given an integer array having distinct elements, find the surpasser count for
            each element in it. In other words, for each array element, find the total
            number of elements to its right, which are greater than it.

            Input : [4, 6, 3, 9, 7, 10]
            Output: [4, 3, 3, 1, 1, 0]

            */

            std::vector<int> Solution::findSurpasserCount(std::vector<int> & nums) {
                // get the size of the nums array
                const int size = nums.size();
                // set size entries to zero
                std::vector<int> counter(size, 0);
                // keeps track of who is ahead
                std::vector<std::pair<int,int>> tracking;

                for (int cnt = 0 ; cnt < size ; cnt++) {
                    const int value = nums[cnt];
                    /*
                        Version 1:  It works but it just seems to inefficient on an implementation
                                    to be acceptable.
                    */
                    // NOTE: I don't like the idea of having to loop through this everytime but
                    //       the second version seems to run a little longer than this one.  I
                    //       if that has to do with the fact that we are using a vector to access
                    //       the count values.
                    // for (int cmp = cnt + 1 ; cmp < size ; cmp++) {
                    //     if (value < nums[cmp]) counter[cnt]++;
                    // } // for
                    /*
                        Version 2:  This will only increment the values that will be greater
                                    than the ones already processed.  This will reduce the
                                    number of iterations that need to be performed along the
                                    way.
                    */
                    std::pair<int,int> track(value,cnt);
                    std::vector<std::pair<int,int>>::const_iterator itr = tracking.begin();
                    while ( itr != tracking.end() && (*itr).first > value) itr++;
                    itr = tracking.insert(itr, track);

                    for ( itr++ ; itr != tracking.end() ; itr++) {
                        counter[(*itr).second]++;
                    } // for
                } // for

                return counter;
            } // findSurpasserCount
        }
    }
}
