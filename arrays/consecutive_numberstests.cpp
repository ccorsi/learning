/**
 * @file consecutive_numberstests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=ConsecutiveNumbers
 * @version 0.1
 * @date 2023-03-27
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
#include "consecutive_numbers.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::arrays::consecutive_numbers;

// Test Fixture Data Class
class ConsecutiveNumbersData {
    std::vector<int> m_input;
    bool m_expected;
public:
    ConsecutiveNumbersData() = default;

    std::vector<int> const & get_input() { return m_input; }
    bool get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const ConsecutiveNumbersData &);
    friend std::istream& operator>>(std::istream&, ConsecutiveNumbersData &);

};

std::ostream& operator<<(std::ostream& out, const ConsecutiveNumbersData & data) {
    out << "ConsecutiveNumbersData [ input=[";
    for (int value : data.m_input)
        out << " " << value;
    out << " ] expected=" << ((data.m_expected) ? "true" : "false") << " ]";

    return out;
}

std::istream& operator>>(std::istream& in, ConsecutiveNumbersData &data) {
    ::loaders::vectors::vectorLoader<
        int,
        std::vector<int>,
        char,
        ::checkers::is_space_or<','>
    > inputLoader(data.m_input, '[', ']');
    in >> inputLoader;

    ::checkers::skip_spaces<char, ::checkers::is_space_or<','>> skipSpace;

    skipSpace(in);
    in >> data.m_expected;
    skipSpace(in);

    return in;
}

// Test Fixture Class
class ConsecutiveNumbersFixture :
    public testing::TestWithParam<ConsecutiveNumbersData> {
};

// Parameterized Test Definition
TEST_P(ConsecutiveNumbersFixture, ConsecutiveNumbersTests) {
    ConsecutiveNumbersData data = GetParam();

    Solution solution;

    bool actual = solution.isConsecutive(data.get_input());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(ConsecutiveNumbersTests, ConsecutiveNumbersFixture, testing::ValuesIn(
    Loader<ConsecutiveNumbersData>()(find_path("arrays/data/consecutive_numbers.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
