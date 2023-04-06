/**
 * @file rearrange_array_fourtests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-02-10
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <iostream>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "paths.h"
#include "loader.h"
#include "rearrange_array_four.h"

using namespace valhalla::arrays::rearrange_array_four;
using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using ::testing::AnyOfArray;

// Test Fixture Data Class
class RearrangeArrayFourData {
    std::vector<int> m_input;
    std::vector<std::vector<int>> m_expected;
public:
     RearrangeArrayFourData() = default;
     RearrangeArrayFourData(std::vector<int> input, std::vector<std::vector<int>> expected) : m_input(input), m_expected(expected) {}

     std::vector<int> const & get_input() { return m_input; }
     const std::vector<std::vector<int>> const & get_expected() { return m_expected; }

     friend std::ostream& operator<<(std::ostream&, const RearrangeArrayFourData &);
     friend std::istream& operator>>(std::istream&, RearrangeArrayFourData &);
};

std::ostream& operator<<(std::ostream& out, const RearrangeArrayFourData &data) {
    out << "RearrangeArrayFourData [ input=[";
    for (int v : data.m_input)
        out << " " << v;
    out << " ], expected=[";
    for (std::vector<int> values : data.m_expected) {
        out << " [";
        for (int value : values) {
            out << " " << value;
        } // for
        out << " ]";
    } // for
    out << " ]";

    return out;
}

std::istream& operator>>(std::istream& in, RearrangeArrayFourData & data) {
    vectorLoader<int> vecLoader('{', '}', data.m_input);
    in >> vecLoader;
    matrixLoader<int> matLoader(data.m_expected,'{', '}');
    in >> matLoader;
    return in;
}

// Test Fixture Class
class RearrangeArrayFourFixture :
    public testing::TestWithParam<RearrangeArrayFourData> {
};

// Parameterized Test Definition
TEST_P(RearrangeArrayFourFixture, RearrangeArrayFourTests) {
    RearrangeArrayFourData data = GetParam();

    Solution solution;

    std::vector<int> actual(data.get_input());

    solution.rearrange(actual);

    const std::vector<std::vector<int>> & expected = data.get_expected();

    ASSERT_THAT(actual, AnyOfArray(expected.begin(), expected.end()));
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(RearrangeArrayFourTests, RearrangeArrayFourFixture, testing::ValuesIn(
    Loader<RearrangeArrayFourData>()(find_path("arrays/data/rearrange_array_four.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
