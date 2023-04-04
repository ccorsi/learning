/**
 * @file left_rotate_arraytests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=LeftRotateArray
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
#include "left_rotate_array.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::arrays::left_rotate_array;

// Test Fixture Data Class
class LeftRotateArrayData {
    std::vector<int> m_input;
    int m_k;
    std::vector<int> m_expected;
public:
    LeftRotateArrayData() = default;

    std::vector<int> const & get_input() { return m_input; }
    int get_k() { return m_k; }
    std::vector<int> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const LeftRotateArrayData &);
    friend std::istream& operator>>(std::istream&, LeftRotateArrayData &);

};

std::ostream& operator<<(std::ostream& out, const LeftRotateArrayData & data) {
    out << "LeftRotateArrayData [ input=[";
    for (int value : data.m_input)
        out << " " << value;
    out << " ] k=" << data.m_k << " expected=[";
    for (int value : data.m_expected)
        out << " " << value;
    out << " ] ]";

    return out;
}

std::istream& operator>>(std::istream& in, LeftRotateArrayData &data) {
    ::loaders::vectors::vectorLoader<
      int,
      std::vector<int>,
      char,
      ::checkers::is_space_or<','>
    > inputLoader(data.m_input,'[', ']');
    in >> inputLoader;

    ::checkers::skip_spaces<char, ::checkers::is_space_or<','>> skipSpace;
    skipSpace(in);
    in >> data.m_k;
    skipSpace(in);

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
class LeftRotateArrayFixture :
    public testing::TestWithParam<LeftRotateArrayData> {
};

// Parameterized Test Definition
TEST_P(LeftRotateArrayFixture, LeftRotateArrayTests) {
    LeftRotateArrayData data = GetParam();

    Solution solution;

    std::vector<int> input = data.get_input();

    solution.leftRotate(input, data.get_k());

    ASSERT_EQ(input, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(LeftRotateArrayTests, LeftRotateArrayFixture, testing::ValuesIn(
    Loader<LeftRotateArrayData>()(find_path("arrays/data/left_rotate_array.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
