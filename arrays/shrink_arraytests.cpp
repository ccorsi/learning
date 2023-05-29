/**
 * @file shrink_arraytests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=ShrinkArray
 * @version 0.1
 * @date 2023-05-21
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
#include "shrink_array.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::arrays::shrink_array;

// Test Fixture Data Class
class ShrinkArrayData {
    std::vector<int> m_input;
    int m_k;
    int m_expected;
public:
    ShrinkArrayData() = default;

    std::vector<int> const & get_input() { return m_input; }
    int get_k() { return m_k; }
    int get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const ShrinkArrayData &);
    friend std::istream& operator>>(std::istream&, ShrinkArrayData &);

};

std::ostream& operator<<(std::ostream& out, const ShrinkArrayData & data) {
    out << "ShrinkArrayData [ input=[";
    for (int value : data.m_input) {
        out << " " << value;
    }

    return out << " ] k=" << data.m_k << " expected=" << data.m_expected << " ]";
}

std::istream& operator>>(std::istream& in, ShrinkArrayData &data) {
    ::loaders::vectors::vectorLoader<
      int,
      std::vector<int>,
      char,
      ::checkers::is_space_or<','>
    > inputLoader(data.m_input,'[', ']');
    in >> inputLoader;

    ::loaders::primitive::primitiveLoader<
      int,
      char,
      ::checkers::is_space_or<','>
    > kLoader(&data.m_k);
    in >> kLoader;

    ::loaders::primitive::primitiveLoader<
      int,
      char,
      ::checkers::is_space_or<','>
    > expectedLoader(&data.m_expected);
    in >> expectedLoader;

    return in;
}

// Test Fixture Class
class ShrinkArrayFixture :
    public testing::TestWithParam<ShrinkArrayData> {
};

// Parameterized Test Definition
TEST_P(ShrinkArrayFixture, ShrinkArrayTests) {
    ShrinkArrayData data = GetParam();

    Solution solution;

    int actual = solution.shrink(data.get_input(), data.get_k());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(ShrinkArrayTests, ShrinkArrayFixture, testing::ValuesIn(
    Loader<ShrinkArrayData>()(find_path("arrays/data/shrink_array.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
