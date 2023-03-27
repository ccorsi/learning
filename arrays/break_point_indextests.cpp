/**
 * @file break_point_indextests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=BreakPointIndex
 * @version 0.1
 * @date 2023-03-27
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
#include "break_point_index.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::arrays::break_point_index;

// Test Fixture Data Class
class BreakPointIndexData {
    std::vector<int> m_input;
    int m_expected;
public:
    BreakPointIndexData() = default;

    std::vector<int> const & get_input() { return m_input; }
    int get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const BreakPointIndexData &);
    friend std::istream& operator>>(std::istream&, BreakPointIndexData &);

};

std::ostream& operator<<(std::ostream& out, const BreakPointIndexData & data) {
    out << "BreakPointIndexData [ input=[";
    for (int value : data.m_input)
        out << " " << value;
    out << " ] expected=" << data.m_expected << " ]";

    return out;
}

std::istream& operator>>(std::istream& in, BreakPointIndexData &data) {
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
class BreakPointIndexFixture :
    public testing::TestWithParam<BreakPointIndexData> {
};

// Parameterized Test Definition
TEST_P(BreakPointIndexFixture, BreakPointIndexTests) {
    BreakPointIndexData data = GetParam();

    Solution solution;

    int actual = solution.findBreakPoint(data.get_input());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(BreakPointIndexTests, BreakPointIndexFixture, testing::ValuesIn(
    Loader<BreakPointIndexData>()(find_path("arrays/data/break_point_index.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
