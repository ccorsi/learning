/**
 * @file partition_array_equal_sumtests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=PartitionArrayEqualSum
 * @version 0.1
 * @date 2023-03-26
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
#include "partition_array_equal_sum.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::arrays::partition_array_equal_sum;

// Test Fixture Data Class
class PartitionArrayEqualSumData {
    std::vector<int> m_input;
    int m_expected;
public:
    PartitionArrayEqualSumData() = default;

    std::vector<int> const & get_input() { return m_input; }
    int get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const PartitionArrayEqualSumData &);
    friend std::istream& operator>>(std::istream&, PartitionArrayEqualSumData &);

};

std::ostream& operator<<(std::ostream& out, const PartitionArrayEqualSumData & data) {
    out << "PartitionArrayEqualSumData [ input=[";
    for (int value : data.m_input)
        out << " " << value;
    out << " ] expected=" << data.m_expected << " ]";

    return out;
}

std::istream& operator>>(std::istream& in, PartitionArrayEqualSumData &data) {
    ::loaders::vectors::vectorLoader<
        int,
        std::vector<int>,
        char,
        ::checkers::is_space_or<','>
    > inputLoader(data.m_input, '[', ']');
    in >> inputLoader;

    in >> data.m_expected;

    ::checkers::skip_spaces<char, ::checkers::is_space_or<','>> skipSpace;

    skipSpace(in);

    return in;
}

// Test Fixture Class
class PartitionArrayEqualSumFixture :
    public testing::TestWithParam<PartitionArrayEqualSumData> {
};

// Parameterized Test Definition
TEST_P(PartitionArrayEqualSumFixture, PartitionArrayEqualSumTests) {
    PartitionArrayEqualSumData data = GetParam();

    Solution solution;

    int actual = solution.findPartitionIndex(data.get_input());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(PartitionArrayEqualSumTests, PartitionArrayEqualSumFixture, testing::ValuesIn(
    Loader<PartitionArrayEqualSumData>()(find_path("arrays/data/partition_array_equal_sum.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
