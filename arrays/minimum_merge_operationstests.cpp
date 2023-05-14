/**
 * @file minimum_merge_operationstests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests for the problem https://www.techiedelight.com/?problem=MinimumMergeOperations
 * @version 0.1
 * @date 2023-05-01
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
#include "minimum_merge_operations.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::arrays::minimum_merge_operations;

// Test Fixture Data Class
class MinimumMergeOperationData {
    std::vector<int> m_input;
    int m_expected;
public:
    MinimumMergeOperationData() = default;

    std::vector<int> const & get_input() { return m_input; }
    int get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const MinimumMergeOperationData &);
    friend std::istream& operator>>(std::istream&, MinimumMergeOperationData &);

};

std::ostream& operator<<(std::ostream& out, const MinimumMergeOperationData & data) {
    out << "MinimumMergeOperationData [ input=[";
    for (int value : data.m_input)
        out << " " << value;
    out << " ] expected=" << data.m_expected << " ]";

    return out;
}

std::istream& operator>>(std::istream& in, MinimumMergeOperationData &data) {
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
    > expectedLoader(&data.m_expected);
    in >> expectedLoader;

    return in;
}

// Test Fixture Class
class MinimumMergeOperationFixture :
    public testing::TestWithParam<MinimumMergeOperationData> {
};

// Parameterized Test Definition
TEST_P(MinimumMergeOperationFixture, MinimumMergeOperationTests) {
    MinimumMergeOperationData data = GetParam();

    Solution solution;

    std::vector<int> input = data.get_input();

    int actual = solution.findMin(input);

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(MinimumMergeOperationTests, MinimumMergeOperationFixture, testing::ValuesIn(
    Loader<MinimumMergeOperationData>()(find_path("arrays/data/minimum_merge_operations.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
