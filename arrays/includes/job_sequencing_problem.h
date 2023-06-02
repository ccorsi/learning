/**
 * @file job_sequencing_problem.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-05-31
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __JOB_SEQUENCING_PROBLEM_H__
#define __JOB_SEQUENCING_PROBLEM_H__

#include <iostream>
#include <vector>
#include <unordered_set>

namespace valhalla {
    namespace arrays {
        namespace job_sequencing_problem {
            class Job {
            public:
                int taskId, deadline, profit;

                bool operator==(const Job & p) {
                    return taskId == p.taskId && deadline == p.deadline && profit == p.profit;
                }

                friend std::istream & operator>>(std::istream &, Job &);
                friend std::ostream & operator<<(std::ostream &, const Job &);
            };

            class Solution {
            public:
                std::unordered_set<int> scheduleJobs(std::vector<Job> jobs);
            };
        }
    }
}

#endif
