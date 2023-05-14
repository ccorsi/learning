/**
 * @file next_greater_element_twotests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests for the problem https://www.techiedelight.com/?problem=NextGreaterElementII
 * @version 0.1
 * @date 2023-05-03
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
#include "next_greater_element_two.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::arrays::next_greater_element_two;

// Test Fixture Data Class
class NextGreaterElementTwoData {
    std::vector<int> m_input;
    std::vector<int> m_expected;
public:
    NextGreaterElementTwoData() = default;

    std::vector<int> const & get_input() { return m_input; }
    std::vector<int> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const NextGreaterElementTwoData &);
    friend std::istream& operator>>(std::istream&, NextGreaterElementTwoData &);

};

std::ostream& operator<<(std::ostream& out, const NextGreaterElementTwoData & data) {
    out << "NextGreaterElementTwoData [ input=[";
    for (int value : data.m_input) {
        out << " " << value;
    }
    out << " ]  expected=[";
    for (int value : data.m_expected) {
        out << " " << value;
    }
    out << " ] ]";

    return out;
}

std::istream& operator>>(std::istream& in, NextGreaterElementTwoData &data) {
    ::loaders::vectors::vectorLoader<
      int,
      std::vector<int>,
      char,
      ::checkers::is_space_or<','>
    > inputLoader(data.m_input,'[', ']');
    in >> inputLoader;

    ::loaders::vectors::vectorLoader<
      int,
      std::vector<int>,
      char,
      ::checkers::is_space_or<','>
    > expectedLoader(data.m_expected,'[', ']');
    in >> expectedLoader;

    return in;
}

// Test Fixture Class
class NextGreaterElementTwoFixture :
    public testing::TestWithParam<NextGreaterElementTwoData> {
};

// Parameterized Test Definition
TEST_P(NextGreaterElementTwoFixture, NextGreaterElementTwoTests) {
    NextGreaterElementTwoData data = GetParam();

    Solution solution;

    std::vector<int> actual = solution.findNextGreaterElements(data.get_input());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(NextGreaterElementTwoTests, NextGreaterElementTwoFixture, testing::ValuesIn(
    Loader<NextGreaterElementTwoData>()(find_path("arrays/data/next_greater_element_two.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
