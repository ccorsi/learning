/**
 * @file surpasser_counttests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=SurpasserCount
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
#include "surpasser_count.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::arrays::surpasser_count;

// Test Fixture Data Class
class SurpasserCountData {
    std::vector<int> m_input;
    std::vector<int> m_expected;
public:
    SurpasserCountData() = default;

    std::vector<int> const & get_input() { return m_input; }
    std::vector<int> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const SurpasserCountData &);
    friend std::istream& operator>>(std::istream&, SurpasserCountData &);

};

std::ostream& operator<<(std::ostream& out, const SurpasserCountData & data) {
    out << "SurpasserCountData [ input=[";
    for (int value : data.m_input)
        out << " " << value;
    out << " ] expected=[";
    for (int value : data.m_expected)
        out << " " << value;
    out << " ] ]";

    return out;
}

std::istream& operator>>(std::istream& in, SurpasserCountData &data) {
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
class SurpasserCountFixture :
    public testing::TestWithParam<SurpasserCountData> {
};

// Parameterized Test Definition
TEST_P(SurpasserCountFixture, SurpasserCountTests) {
    SurpasserCountData data = GetParam();

    Solution solution;

    std::vector<int> input = data.get_input();

    std::vector<int> actual = solution.findSurpasserCount(input);

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(SurpasserCountTests, SurpasserCountFixture, testing::ValuesIn(
    Loader<SurpasserCountData>()(find_path("arrays/data/surpasser_count.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
