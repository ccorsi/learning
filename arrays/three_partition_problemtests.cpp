/**
 * @file three_partition_problemtests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=3PartitionProblem
 * @version 0.1
 * @date 2023-04-12
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
#include "three_partition_problem.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::arrays::three_partition_problem;

// Test Fixture Data Class
class ThreePartitionProblemData {
    std::vector<int> m_input;
    bool m_expected;
public:
    ThreePartitionProblemData() = default;

    std::vector<int> const & get_input() { return m_input; }
    bool get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const ThreePartitionProblemData &);
    friend std::istream& operator>>(std::istream&, ThreePartitionProblemData &);

};

std::ostream& operator<<(std::ostream& out, const ThreePartitionProblemData & data) {
    out << "ThreePartitionProblemData [ input=[";
    for (int value : data.m_input)
        out << " " << value;
    out << " ] expected=" << ((data.m_expected) ? "true" : "false") << " ]";

    return out;
}

std::istream& operator>>(std::istream& in, ThreePartitionProblemData &data) {
    ::loaders::vectors::vectorLoader<
      int,
      std::vector<int>,
      char,
      ::checkers::is_space_or<','>
    > inputLoader(data.m_input,'[', ']');
    in >> inputLoader;
    
    ::checkers::skip_spaces<char,::checkers::is_space_or<','>> skipSpace;
    skipSpace(in);
    in >> data.m_expected;
    skipSpace(in);

    return in;
}

// Test Fixture Class
class ThreePartitionProblemFixture :
    public testing::TestWithParam<ThreePartitionProblemData> {
};

// Parameterized Test Definition
TEST_P(ThreePartitionProblemFixture, ThreePartitionProblemTests) {
    ThreePartitionProblemData data = GetParam();

    Solution solution;

    std::vector<int> input = data.get_input();

    bool actual = solution.partition(input);

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(ThreePartitionProblemTests, ThreePartitionProblemFixture, testing::ValuesIn(
    Loader<ThreePartitionProblemData>()(find_path("arrays/data/three_partition_problem.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
