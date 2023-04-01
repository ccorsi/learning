/**
 * @file shuffle_array_threetests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains the tests to the problem https://www.techiedelight.com/?problem=ShuffleArrayIII
 * @version 0.1
 * @date 2023-03-28
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <iostream>
#include <algorithm>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "paths.h"
#include "loaders.h"
#include "shuffle_array_three.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::arrays::shuffle_array_three;

// Test Fixture Data Class
class ShuffleArrayThreeData {
    std::vector<int> m_input;
    std::vector<int> m_expected;
public:
    ShuffleArrayThreeData() = default;

    std::vector<int> const & get_input() { return m_input; }
    std::vector<int> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const ShuffleArrayThreeData &);
    friend std::istream& operator>>(std::istream&, ShuffleArrayThreeData &);

};

std::ostream& operator<<(std::ostream& out, const ShuffleArrayThreeData & data) {
    out << "ShuffleArrayThreeData [ input=[";
    for (int value : data.m_input)
        out << " " << value;
    out << " ] expected=[";
    for (int value : data.m_expected)
        out << " " << value;
    out << " ] ]";

    return out;
}

std::istream& operator>>(std::istream& in, ShuffleArrayThreeData &data) {
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
class ShuffleArrayThreeFixture :
    public testing::TestWithParam<ShuffleArrayThreeData> {
};

// Parameterized Test Definition
TEST_P(ShuffleArrayThreeFixture, ShuffleArrayThreeTests) {
    ShuffleArrayThreeData data = GetParam();

    Solution solution;

    std::vector<int> nums = data.get_input();

    solution.shuffle(nums);

    for (int value : data.get_expected())
        EXPECT_TRUE(std::find(nums.begin(), nums.end(), value) != nums.end()) << "missing value: " << value;

}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(ShuffleArrayThreeTests, ShuffleArrayThreeFixture, testing::ValuesIn(
    Loader<ShuffleArrayThreeData>()(find_path("arrays/data/shuffle_array_three.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
