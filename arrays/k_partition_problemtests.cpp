/**
 * @file k_partition_problemtests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains the tests to the problem https://www.techiedelight.com/?problem=KPartitionProblem
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
#include "k_partition_problem.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::arrays::k_partition_problem;

// Test Fixture Data Class
class KPartitionProblemData {
    std::vector<int> m_input;
    int m_k;
    std::vector<std::vector<int>> m_expected;
public:
    KPartitionProblemData() = default;

    std::vector<int> const & get_input() { return m_input; }
    int get_k() { return m_k; }
    std::vector<std::vector<int>> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const KPartitionProblemData &);
    friend std::istream& operator>>(std::istream&, KPartitionProblemData &);

};

std::ostream& operator<<(std::ostream& out, const KPartitionProblemData & data) {
    out << "KPartitionProblemData [ input=[";
    out << " ] k=" << data.m_k << " expected=[";
    for (std::vector<int> values : data.m_expected) {
        out << " [";
        for (int value : values)
            out << " " << value;
        out << " ]";
    } // for
    out << " ] ]";

    return out;
}

std::istream& operator>>(std::istream& in, KPartitionProblemData &data) {
    ::loaders::vectors::vectorLoader<
      int,
      std::vector<int>,
      char,
      ::checkers::is_space_or<','>
    > inputLoader(data.m_input,'[', ']');
    in >> inputLoader;

    ::loaders::primitive::primitiveLoader<
        int,
        char,
        ::checkers::is_space_or<','>
    > kLoader(&data.m_k);
    in >> kLoader;

    ::loaders::matrix::matrixLoader<
      int,
      std::vector<int>,
      std::vector<std::vector<int>>,
      char,
      ::checkers::is_space_or<','>
    > expectedLoader(data.m_expected, '[', ']');
    in >> expectedLoader;

    return in;
}

// Test Fixture Class
class KPartitionProblemFixture :
    public testing::TestWithParam<KPartitionProblemData> {
};

// Parameterized Test Definition
TEST_P(KPartitionProblemFixture, KPartitionProblemTests) {
    KPartitionProblemData data = GetParam();

    Solution solution;

    std::vector<int> input = data.get_input();

    std::vector<std::vector<int>> actual = solution.getSubsets(input, data.get_k());

    // TODO: We need to create a MATCHER that will be passed to the ASSERT_THAT macro instead
    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(KPartitionProblemTests, KPartitionProblemFixture, testing::ValuesIn(
    Loader<KPartitionProblemData>()(find_path("arrays/data/k_partition_problem.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
