/**
 * @file job_sequencing_problemtests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=JobSequencingProblem
 * @version 0.1
 * @date 2023-05-31
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */
#include <iostream>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "paths.h"
#include "loaders.h"
#include "job_sequencing_problem.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::arrays::job_sequencing_problem;

// Test Fixture Data Class
class JonSequencingProblemData {
    std::vector<Job> m_input;
    std::unordered_set<int> m_expected;
public:
    JonSequencingProblemData() = default;

    std::vector<Job> const & get_input() { return m_input; }
    std::unordered_set<int> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const JonSequencingProblemData &);
    friend std::istream& operator>>(std::istream&, JonSequencingProblemData &);

};

std::ostream& operator<<(std::ostream& out, const JonSequencingProblemData & data) {
    out << "JonSequencingProblemData [ input={";
    for (Job value : data.m_input) {
        out << " " << value;
    }
    out << " } expected=[";
    for (int value : data.m_expected) {
        out << " " << value;
    }
    out <<" ] ]";

    return out;
}

std::istream& operator>>(std::istream& in, JonSequencingProblemData &data) {
    ::loaders::vectors::vectorLoader<
      Job,
      std::vector<Job>,
      char,
      ::checkers::is_space_or<','>
    > inputLoader(data.m_input,'[', ']');
    in >> inputLoader;

    ::loaders::set::setLoader<
      int,
      std::unordered_set<int>,
      char,
      ::checkers::is_space_or<','>
    > expectedLoader(data.m_expected,'{', '}');
    in >> expectedLoader;

    return in;
}

// Test Fixture Class
class JonSequencingProblemFixture :
    public testing::TestWithParam<JonSequencingProblemData> {
};

// Parameterized Test Definition
TEST_P(JonSequencingProblemFixture, JonSequencingProblemTests) {
    JonSequencingProblemData data = GetParam();

    Solution solution;

    std::vector<Job> input = data.get_input();

    std::unordered_set<int> actual = solution.scheduleJobs(input);

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(JonSequencingProblemTests, JonSequencingProblemFixture, testing::ValuesIn(
    Loader<JonSequencingProblemData>()(find_path("arrays/data/job_sequencing_problem.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
