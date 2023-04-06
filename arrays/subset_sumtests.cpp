/**
 * @file subset_sumtests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests for the problem https://www.techiedelight.com/?problem=SubsetSum
 * @version 0.1
 * @date 2023-03-08
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <iostream>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "paths.h"
#include "loader.h"
#include "checkers.h"
#include "subset_sum.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils::checkers;
using namespace valhalla::arrays::subset_sum;

// Test Fixture Data Class
class SubsetSumData {
    std::vector<int> m_input;
    int m_target;
    int m_expected;
public:
    SubsetSumData() = default;

    std::vector<int> const & get_input() { return m_input; }
    int get_target() { return m_target; }
    int get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const SubsetSumData &);
    friend std::istream& operator>>(std::istream&, SubsetSumData &);

};

std::ostream& operator<<(std::ostream& out, const SubsetSumData & data) {
    out << "SubsetSumData [ input=[";
    for (int value : data.m_input)
        out << " " << value;
    out << " ] target=" << data.m_target << " expected=" << data.m_expected << " ]";

    return out;
}

std::istream& operator>>(std::istream& in, SubsetSumData &data) {
    vectorLoader<int> loader('[', ']', data.m_input);
    in >> loader;

    skip_spaces<char,is_space_or<','>> skipSpace;

    skipSpace(in);
    in >> data.m_target;

    skipSpace(in);
    in >> data.m_expected;

    skipSpace(in);

    return in;
}

// Test Fixture Class
class SubsetSumFixture :
    public testing::TestWithParam<SubsetSumData> {
};

// Parameterized Test Definition
TEST_P(SubsetSumFixture, SubsetSumTests) {
    SubsetSumData data = GetParam();

    Solution solution;

    int actual = solution.countWays(data.get_input(), data.get_target());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(SubsetSumTests, SubsetSumFixture, testing::ValuesIn(
    Loader<SubsetSumData>()(find_path("arrays/data/subset_sum.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
