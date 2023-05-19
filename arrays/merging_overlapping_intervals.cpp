/**
 * @file merging_overlapping_intervals.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=MergingOverlappingIntervals
 * @version 0.1
 * @date 2023-05-15
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */


#include "merging_overlapping_intervals.h"

#include <algorithm>

namespace valhalla {
    namespace arrays {
        namespace merging_overlapping_intervals {
            /*

            Given a collection of intervals, return all non-overlapping intervals after
            merging the overlapping intervals.

            Input : [(1, 5), (2, 3), (4, 6), (7, 8), (8, 10), (12, 15)]
            Output: {(1, 6), (7, 10), (12, 15)}

            */

            std::set<std::pair<int,int>> Solution::mergeIntervals(std::vector<std::pair<int,int>> intervals) {
                /*
                    Version 1:  This solution assumes that the intervals are sorted such that none of the next
                                intervals will be before the current interval we are comparing.  If this is
                                not the case then we just sort the incoming intervals such that they will
                                always be less than the next interval.
                */
                std::set<std::pair<int,int>> merged;

                if (intervals.empty() == false) {

                    std::sort(intervals.begin(), intervals.end(), [](const std::pair<int,int> & lhs, const std::pair<int,int> & rhs) {
                        if (lhs.first != rhs.first) {
                            return lhs.first < rhs.first;
                        } else {
                            return lhs.second < rhs.second;
                        } // else
                    });

                    const int size = intervals.size();
                    int idx = 0;
                    std::pair<int,int> current = intervals[idx];

                    while (idx < size) {
                        std::pair<int,int> next = intervals[idx++];

                        if (current.second < next.first) {
                            // The current interval is before the next interval
                            merged.insert(current);
                            current = next;
                        } else if (current.first <= next.first && current.second >= next.second) {
                            // nothing to do since the next pair is a subset of the current pair
                        } else if (current.first > next.second) {
                            // The current interval is after the next interval.  If that is the case
                            // then we need to sort the incoming intervals array.
                            merged.insert(current);
                            current = next;
                        } else {
                            // The next interval overlaps the current interval in some way and we just
                            // need to update the current intervals ends.
                            current.first = std::min(current.first, next.first);
                            current.second = std::max(current.second, next.second);
                        } // else
                    } // while

                    // Let us not forget to include the last interval since it is always going to be added.
                    merged.insert(current);
                } // if

                return merged;
            } // mergeIntervals
        }
    }
}
