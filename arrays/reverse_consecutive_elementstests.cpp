/**
 * @file reverse_consecutive_elementstests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=ReverseConsecutiveElements
 * @version 0.1
 * @date 2023-03-20
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
#include "reverse_consecutive_elements.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::arrays::reverse_consecutive_elements;

// Test Fixture Data Class
class ReverseConsecutiveElementsData {
    std::vector<int> m_input;
    int m_m, m_i, m_j;
    std::vector<int> m_expected;
public:
    ReverseConsecutiveElementsData() = default;

    std::vector<int> const & get_input() { return m_input; }
    int get_m() { return m_m; }
    int get_i() { return m_i; }
    int get_j() { return m_j; }
    std::vector<int> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const ReverseConsecutiveElementsData &);
    friend std::istream& operator>>(std::istream&, ReverseConsecutiveElementsData &);

};

std::ostream& operator<<(std::ostream& out, const ReverseConsecutiveElementsData & data) {
    out << "ReverseConsecutiveElementsData [ input=[";
    for (int value : data.m_input)
        out << " " << value;
    out << " ] m=" << data.m_m << " i=" << data.m_i << " j=" << data.m_j << " expected=[";
    for (int value : data.m_expected)
        out << " " << value;
    out << " ] ]";

    return out;
}

std::istream& operator>>(std::istream& in, ReverseConsecutiveElementsData &data) {
    std::cout << "Entering operator>> '" << static_cast<char>(in.peek()) << "'" << std::endl;
    ::loaders::vectors::vectorLoader<
        int,
        std::vector<int>,
        char,
        ::checkers::is_space_or<','>
    > inputLoader(data.m_input, '[', ']');
    in >> inputLoader;

    std::cout << "1" << std::endl;
    in >> data.m_m >> data.m_i >> data.m_j;
    std::cout << "2" << std::endl;

    ::loaders::vectors::vectorLoader<
        int,
        std::vector<int>,
        char,
        ::checkers::is_space_or<','>
    > expectedLoader(data.m_expected, '[', ']');
    in >> expectedLoader;

    std::cout << "Exiting operator>> " << data << std::endl;
    return in;
}

// Test Fixture Class
class ReverseConsecutiveElementsFixture :
    public testing::TestWithParam<ReverseConsecutiveElementsData> {
};

// Parameterized Test Definition
TEST_P(ReverseConsecutiveElementsFixture, ReverseConsecutiveElementsTests) {
    ReverseConsecutiveElementsData data = GetParam();

    Solution solution;

    std::vector<int> actual(data.get_input());

    solution.reverseInGroup(actual, data.get_m(), data.get_i(), data.get_j());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(ReverseConsecutiveElementsTests, ReverseConsecutiveElementsFixture, testing::ValuesIn(
    Loader<ReverseConsecutiveElementsData>()(find_path("arrays/data/reverse_consecutive_elements.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
