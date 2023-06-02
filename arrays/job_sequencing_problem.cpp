/**
 * @file job_sequencing_problem.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=JobSequencingProblem
 * @version 0.1
 * @date 2023-05-31
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <algorithm>

#include "job_sequencing_problem.h"
#include "primitive_loader.h"

using namespace valhalla::utils::checkers;
using namespace valhalla::utils::loaders;
using namespace valhalla::utils;

namespace valhalla {
    namespace arrays {
        namespace job_sequencing_problem {
            /*

            Given a list of tasks with deadlines and total profit earned on completing a task,
            find the maximum profit earned by executing the tasks within the specified deadlines.
            Assume that each task takes one unit of time to complete, and a task can't execute
            beyond its deadline.

            Input: (Task Id, Deadline, Profit)

            [(1, 9, 15), (2, 2, 2), (3, 5, 18), (4, 7, 1), (5, 4, 25), (6, 2, 20), (7, 5, 8),
             (8, 7, 10), (9, 4, 12), (10, 3, 5)]

            Output: {1, 3, 4, 5, 6, 7, 8, 9}
            Explanation: The maximum profit that can be achieved is 109 by leaving tasks 2 and 10 out.

            Constraints:

            • Only a single task can be executed at a time.
            • The maximum number of tasks are 100.
            • The maximum deadline that can be associated with a job is 1000.

            */

            std::unordered_set<int> Solution::scheduleJobs(std::vector<Job> jobs) {
                std::unordered_set<int> scheduled;

                std::sort(jobs.begin(), jobs.end(), [](const Job & lhs, const Job & rhs) {
                    return lhs.deadline != rhs.deadline ? lhs.deadline < rhs.deadline : lhs.profit > rhs.profit;
                });

                for (Job value : jobs) {
                    std::cout << " " << value << std::endl;
                }
                std::cout << std::endl;

                return scheduled;
            } // scheduleJobs

            std::istream & operator>>(std::istream & in, Job & job) {
                ::checkers::skip_spaces<char, ::checkers::is_space_or<','>> skipSpaces;

                skipSpaces(in);

                if (static_cast<char>(in.peek()) == '(') {
                    in.get(); // read the '(' character

                    skipSpaces(in);

                    ::loaders::primitive::primitiveLoader<
                    int,
                    char,
                    ::checkers::is_space
                    > taskIdLoader(&job.taskId);
                    in >> taskIdLoader;

                    skipSpaces(in);

                    ::loaders::primitive::primitiveLoader<
                    int,
                    char,
                    ::checkers::is_space
                    > deadlineLoader(&job.deadline);
                    in >> deadlineLoader;

                    skipSpaces(in);

                    ::loaders::primitive::primitiveLoader<
                    int,
                    char,
                    ::checkers::is_space
                    > profitLoader(&job.profit);
                    in >> profitLoader;

                    skipSpaces(in);

                    if (static_cast<char>(in.peek()) == ')') {
                        in.get(); // read the ')' character
                        return in;
                    } // if
                } // if

                throw std::runtime_error("Invalid input format");
            }

            std::ostream & operator<<(std::ostream & out, const Job & job) {
                return out << "Job[ " << "taskId=" << job.taskId << " deadline=" << job.deadline << " profit=" << job.profit << " ]";
            }
        }
    }
}
