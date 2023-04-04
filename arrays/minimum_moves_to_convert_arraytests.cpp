/**
 * @file minimum_moves_to_convert_arraytests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=MinimumMovesToConvertArray
 * @version 0.1
 * @date 2023-04-03
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
#include "minimum_moves_to_convert_array.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::arrays::minimum_moves_to_convert_array;

// Test Fixture Data Class
class MinimumMovesToConvertArrayData {
    std::vector<int> m_input;
    int m_expected;
public:
    MinimumMovesToConvertArrayData() = default;

    std::vector<int> const & get_input() { return m_input; }
    int get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const MinimumMovesToConvertArrayData &);
    friend std::istream& operator>>(std::istream&, MinimumMovesToConvertArrayData &);

};

std::ostream& operator<<(std::ostream& out, const MinimumMovesToConvertArrayData & data) {
    out << "MinimumMovesToConvertArrayData [ input=[";
    for (int value : data.m_input)
        out << " " << value;
    out << " ] expected=" << data.m_expected << " ]";

    return out;
}

std::istream& operator>>(std::istream& in, MinimumMovesToConvertArrayData &data) {
    ::loaders::vectors::vectorLoader<
      int,
      std::vector<int>,
      char,
      ::checkers::is_space_or<','>
    > inputLoader(data.m_input,'[', ']');
    in >> inputLoader;

    ::checkers::skip_spaces<char, ::checkers::is_space_or<','>> skipSpace;

    skipSpace(in);
    in >> data.m_expected;
    skipSpace(in);

    return in;
}

// Test Fixture Class
class MinimumMovesToConvertArrayFixture :
    public testing::TestWithParam<MinimumMovesToConvertArrayData> {
};

// Parameterized Test Definition
TEST_P(MinimumMovesToConvertArrayFixture, MinimumMovesToConvertArrayTests) {
    MinimumMovesToConvertArrayData data = GetParam();

    Solution solution;

    std::vector<int> input = data.get_input();

    int actual = solution.findMinMoves(input);

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(MinimumMovesToConvertArrayTests, MinimumMovesToConvertArrayFixture, testing::ValuesIn(
    Loader<MinimumMovesToConvertArrayData>()(find_path("arrays/data/minimum_moves_to_convert_array.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
