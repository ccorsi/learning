/**
 * @file inversion_counttests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=InversionCount
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
#include "inversion_count.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::arrays::inversion_count;

// Test Fixture Data Class
class InversionCountData {
    std::vector<int> m_input;
    int m_expected;
public:
    InversionCountData() = default;

    std::vector<int> const & get_input() { return m_input; }
    int get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const InversionCountData &);
    friend std::istream& operator>>(std::istream&, InversionCountData &);

};

std::ostream& operator<<(std::ostream& out, const InversionCountData & data) {
    out << "InversionCountData [ input=[";
    for (int value : data.m_input)
        out << " " << value;
    out << " ] expected=" << data.m_expected << " ]";

    return out;
}

std::istream& operator>>(std::istream& in, InversionCountData &data) {
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
class InversionCountFixture :
    public testing::TestWithParam<InversionCountData> {
};

// Parameterized Test Definition
TEST_P(InversionCountFixture, InversionCountTests) {
    InversionCountData data = GetParam();

    Solution solution;

    std::vector<int> input = data.get_input();

    int count = solution.findInversionCount(input);

    ASSERT_EQ(count, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(InversionCountTests, InversionCountFixture, testing::ValuesIn(
    Loader<InversionCountData>()(find_path("arrays/data/inversion_count.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
