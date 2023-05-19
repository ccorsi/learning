/**
 * @file maximum_overlapping_intervals.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=MaximumOverlappingIntervals
 * @version 0.1
 * @date 2023-05-15
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */


#include "maximum_overlapping_intervals.h"

namespace valhalla {
    namespace arrays {
        namespace maximum_overlapping_intervals {
            /*

            Consider an event where a log register is maintained containing the guest's arrival and departure times.
            Given an array of arrival and departure times from entries in the log register, find the first
            occurrence when maximum guests were present in the event.

            Input:

            arrival = [1, 2, 4, 7, 8, 12]
            departure = [2, 7, 8, 12, 10, 15]

            Output: 3

            Explanation: Maximum number of guests is 3, present at time 7 as shown below:

            https://techiedelight.com/practice/images/Maximum-Overlapping-Interval.png


            Note: If an arrival and departure event coincides, the arrival time is preferred over the departure time.

            */

            int Solution::findMaxGuests(std::vector<int> const & arrival, std::vector<int> const & departure) {
                const int a_size = arrival.size(), d_size = departure.size();
                int a_idx = 0, d_idx = 0, guests = 0, current = 0, time = 0;

                while (a_idx < a_size && d_idx < d_size) {
                    if (arrival[a_idx] <= departure[d_idx]) {
                        current++;
                        if (current > guests) {
                            guests = current;
                            time = arrival[a_idx];
                        } // if
                        a_idx++;
                    } else {
                        current--;
                        d_idx++;
                    } // if
                } // while

                // This should never happen but we are adding it here just in case.
                if (a_idx < a_size) {
                    time = arrival.back();
                } // if

                return time;
            } // findMaxGuests
        }
    }
}
