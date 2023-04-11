/**
 * @file greater_elementstests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=GreaterElements
 * @version 0.1
 * @date 2023-04-05
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
#include "greater_elements.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::arrays::greater_elements;

// Test Fixture Data Class
class GreaterElementsData {
    std::vector<int> m_input;
    std::vector<int> m_expected;
public:
    GreaterElementsData() = default;

    std::vector<int> const & get_input() { return m_input; }
    std::vector<int> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const GreaterElementsData &);
    friend std::istream& operator>>(std::istream&, GreaterElementsData &);

};

std::ostream& operator<<(std::ostream& out, const GreaterElementsData & data) {
    out << "GreaterElementsData [ input=[";
    for (int value : data.m_input)
        out << " " << value;
    out << " ] expected=[";
    for (int value : data.m_expected)
        out << " " << value;
    out << " ] ]";

    return out;
}

std::istream& operator>>(std::istream& in, GreaterElementsData &data) {
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
class GreaterElementsFixture :
    public testing::TestWithParam<GreaterElementsData> {
};

// Parameterized Test Definition
TEST_P(GreaterElementsFixture, GreaterElementsTests) {
    GreaterElementsData data = GetParam();

    Solution solution;

    std::vector<int> actual = solution.findGreaterElements(data.get_input());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(GreaterElementsTests, GreaterElementsFixture, testing::ValuesIn(
    Loader<GreaterElementsData>()(find_path("arrays/data/greater_elements.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
