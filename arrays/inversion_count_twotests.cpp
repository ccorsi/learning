/**
 * @file inversion_count_twotests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=InversionCountII
 * @version 0.1
 * @date 2023-04-11
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
#include "inversion_count_two.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::arrays::inversion_count_two;

// Test Fixture Data Class
class InversionCountTwoData {
    std::vector<int> m_input;
    int m_expected;
public:
    InversionCountTwoData() = default;

    std::vector<int> const & get_input() { return m_input; }
    int get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const InversionCountTwoData &);
    friend std::istream& operator>>(std::istream&, InversionCountTwoData &);

};

std::ostream& operator<<(std::ostream& out, const InversionCountTwoData & data) {
    out << "InversionCountTwoData [ input=[";
    for (int value : data.m_input)
        out << " " << value;
    out << " ] expected=" << data.m_expected << " ]";

    return out;
}

std::istream& operator>>(std::istream& in, InversionCountTwoData &data) {
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
class InversionCountTwoFixture :
    public testing::TestWithParam<InversionCountTwoData> {
};

// Parameterized Test Definition
TEST_P(InversionCountTwoFixture, InversionCountTwoTests) {
    InversionCountTwoData data = GetParam();

    Solution solution;

    int count = solution.findInversionCount(data.get_input());

    ASSERT_EQ(count, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(InversionCountTwoTests, InversionCountTwoFixture, testing::ValuesIn(
    Loader<InversionCountTwoData>()(find_path("arrays/data/inversion_count_two.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
