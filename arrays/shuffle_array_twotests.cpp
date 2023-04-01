/**
 * @file shuffle_array_twotests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=ShuffleArrayII
 * @version 0.1
 * @date 2023-03-28
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
#include "shuffle_array_two.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::arrays::shuffle_array_two;

// Test Fixture Data Class
class ShuffleArrayTwoData {
    std::vector<int> m_input, m_pos, m_expected;
public:
    ShuffleArrayTwoData() = default;

    std::vector<int> const & get_input() { return m_input; }
    std::vector<int> const & get_pos() { return m_pos; }
    std::vector<int> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const ShuffleArrayTwoData &);
    friend std::istream& operator>>(std::istream&, ShuffleArrayTwoData &);

};

std::ostream& operator<<(std::ostream& out, const ShuffleArrayTwoData & data) {
    out << "ShuffleArrayTwoData [ input=[";
    for (int value : data.m_input)
        out << " " << value;
    out << " ] pos=[";
    for (int value : data.m_pos)
        out << " " << value;
    out << " ] expected=[";
    for (int value : data.m_expected)
        out << " " << value;
    out << " ] ]";

    return out;
}

std::istream& operator>>(std::istream& in, ShuffleArrayTwoData &data) {
    ::checkers::skip_spaces<char, ::checkers::is_space_or<','>> skipSpace;

    skipSpace(in);

    ::loaders::vectors::vectorLoader<
      int,
      std::vector<int>,
      char,
      ::checkers::is_space_or<','>
    > inputLoader(data.m_input,'[', ']');
    in >> inputLoader;

    skipSpace(in);

    ::loaders::vectors::vectorLoader<
      int,
      std::vector<int>,
      char,
      ::checkers::is_space_or<','>
    > posLoader(data.m_pos,'[', ']');
    in >> posLoader;

    skipSpace(in);

    ::loaders::vectors::vectorLoader<
      int,
      std::vector<int>,
      char,
      ::checkers::is_space_or<','>
    > expectedLoader(data.m_expected,'[', ']');
    in >> expectedLoader;

    skipSpace(in);

    return in;
}

// Test Fixture Class
class ShuffleArrayTwoFixture :
    public testing::TestWithParam<ShuffleArrayTwoData> {
};

// Parameterized Test Definition
TEST_P(ShuffleArrayTwoFixture, ShuffleArrayTwoTests) {
    ShuffleArrayTwoData data = GetParam();

    Solution solution;

    std::vector<int> input = data.get_input(), pos = data.get_pos();

    solution.shuffle(input, pos);

    ASSERT_EQ(input, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(ShuffleArrayTwoTests, ShuffleArrayTwoFixture, testing::ValuesIn(
    Loader<ShuffleArrayTwoData>()(find_path("arrays/data/shuffle_array_two.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
