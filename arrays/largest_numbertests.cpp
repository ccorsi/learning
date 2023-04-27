/**
 * @file largest_numbertests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains the tests to the problem https://www.techiedelight.com/?problem=LargestNumber
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
#include "largest_number.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::arrays::largest_number;

// Test Fixture Data Class
class LargestNumberData {
    std::vector<int> m_input;
    std::string m_expected;
public:
    LargestNumberData() = default;

    std::vector<int> const & get_input() { return m_input; }
    std::string const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const LargestNumberData &);
    friend std::istream& operator>>(std::istream&, LargestNumberData &);

};

std::ostream& operator<<(std::ostream& out, const LargestNumberData & data) {
    out << "LargestNumberData [ input=[";
    for (int value : data.m_input) {
        out << " " << value;
    } // for
    out << " ] expected=\"" << data.m_expected << "\" ]";

    return out;
}

std::istream& operator>>(std::istream& in, LargestNumberData &data) {
    ::loaders::vectors::vectorLoader<
      int,
      std::vector<int>,
      char,
      ::checkers::is_space_or<','>
    > inputLoader(data.m_input,'[', ']');
    in >> inputLoader;

    ::loaders::primitive::primitiveLoader<
      std::string,
      char,
      ::checkers::is_space_or<','>
    > expectedLoader(&data.m_expected);
    in >> expectedLoader;

    return in;
}

// Test Fixture Class
class LargestNumberFixture :
    public testing::TestWithParam<LargestNumberData> {
};

// Parameterized Test Definition
TEST_P(LargestNumberFixture, LargestNumberTests) {
    LargestNumberData data = GetParam();

    Solution solution;

    std::vector<int> input = data.get_input();

    std::string actual = solution.findLargestNumber(input);

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(LargestNumberTests, LargestNumberFixture, testing::ValuesIn(
    Loader<LargestNumberData>()(find_path("arrays/data/largest_number.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
