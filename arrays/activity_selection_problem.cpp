/**
 * @file activity_selection_problem.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=ActivitySelectionProblem
 * @version 0.1
 * @date 2023-04-03
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <algorithm>

#include "activity_selection_problem.h"

namespace valhalla {
    namespace arrays {
        namespace activity_selection_problem {
            /*

            Given a set of activities, along with the starting and finishing time of
            each activity, find the maximum number of activities performed by a single
            person assuming that a person can only work on a single activity at a time.

            Input : [(1, 4), (3, 5), (0, 6), (5, 7), (3, 8), (5, 9), (6, 10), (8, 11), (8, 12), (2, 13), (12, 14)]
            Output: {(1, 4), (5, 7), (8, 11), (12, 14)}

            Input : [(3, 7), (1, 3), (2, 9), (2, 7), (1, 2), (7, 8)]
            Output: {(1, 3), (3, 7), (7, 8)} or {(1, 2), (3, 7), (7, 8)} or {(1, 2), (2, 7), (7, 8)}

            */

            std::set<std::pair<int,int>> Solution::selectActivity(std::vector<std::pair<int,int>> activities) {
                const int size = activities.size();
                std::set<std::pair<int,int>> selections;

                std::sort(activities.begin(), activities.end(),
                    [](std::pair<int,int> const & lhs, std::pair<int,int> const & rhs) {
                        if (lhs.first == rhs.first) {
                            return lhs.second < rhs.second;
                        } else {
                            return lhs.first < rhs.first ;
                        } // else
                });

                for (int start = 0 ; start < size ; start++) {
                    if (start + static_cast<int>(selections.size()) >= size) {
                        break;
                    } // if

                    std::set<std::pair<int,int>> current;
                    int last = activities[start].second;
                    current.insert(activities[start]);

                    for (int idx = start + 1; idx < size ; idx++) {
                        if (last <= activities[idx].first) {
                            current.insert(activities[idx]);
                            last = activities[idx].second;
                        } // if
                    } // for

                    if (current.size() > selections.size()) {
                        selections.clear();
                        selections = current;
                    } // if
                } // for

                return selections;
            } // selectActivity
        }
    }
}
