/**
 * @file next_greater_elementtests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests for the problem https://www.techiedelight.com/?problem=NextGreaterElement
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
#include "next_greater_element.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::arrays::next_greater_element;

// Test Fixture Data Class
class NextGreaterElementsData {
    std::vector<int> m_input;
    std::vector<int> m_expected;
public:
    NextGreaterElementsData() = default;

    std::vector<int> const & get_input() { return m_input; }
    std::vector<int> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const NextGreaterElementsData &);
    friend std::istream& operator>>(std::istream&, NextGreaterElementsData &);

};

std::ostream& operator<<(std::ostream& out, const NextGreaterElementsData & data) {
    out << "NextGreaterElementsData [ input=[";
    for (int value : data.m_input) {
        out << " " << value;
    }
    out << "  ] expected=[";
    for (int value : data.m_expected) {
        out << " " << value;
    }
    out << " ] ]";

    return out;
}

std::istream& operator>>(std::istream& in, NextGreaterElementsData &data) {
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
class NextGreaterElementsFixture :
    public testing::TestWithParam<NextGreaterElementsData> {
};

// Parameterized Test Definition
TEST_P(NextGreaterElementsFixture, NextGreaterElementsTests) {
    NextGreaterElementsData data = GetParam();

    Solution solution;

    std::vector<int> actual = solution.findNextGreaterElements(data.get_input());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(NextGreaterElementsTests, NextGreaterElementsFixture, testing::ValuesIn(
    Loader<NextGreaterElementsData>()(find_path("arrays/data/next_greater_element.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
