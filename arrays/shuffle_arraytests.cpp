/**
 * @file shuffle_arraytests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=ShuffleArray
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
#include "shuffle_array.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::arrays::shuffle_array;

// Test Fixture Data Class
class ShuffleArrayData {
    std::vector<int> m_input, m_pos, m_expected;
public:
    ShuffleArrayData() = default;

    std::vector<int> const & get_input() { return m_input; }
    std::vector<int> const & get_pos() { return m_pos; }
    std::vector<int> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const ShuffleArrayData &);
    friend std::istream& operator>>(std::istream&, ShuffleArrayData &);

};

std::ostream& operator<<(std::ostream& out, const ShuffleArrayData & data) {
    out << "ShuffleArrayData [ input=[";
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

std::istream& operator>>(std::istream& in, ShuffleArrayData &data) {
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
    > posLoader(data.m_pos,'[', ']');
    in >> posLoader;

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
class ShuffleArrayFixture :
    public testing::TestWithParam<ShuffleArrayData> {
};

// Parameterized Test Definition
TEST_P(ShuffleArrayFixture, ShuffleArrayTests) {
    ShuffleArrayData data = GetParam();

    Solution solution;

    std::vector<int> input = data.get_input(), pos = data.get_pos();

    solution.shuffle(input, pos);

    ASSERT_EQ(input, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(ShuffleArrayTests, ShuffleArrayFixture, testing::ValuesIn(
    Loader<ShuffleArrayData>()(find_path("arrays/data/shuffle_array.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
