/**
 * @file floor_and_ceiltests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief These are tests for the problem https://www.techiedelight.com/?problem=FloorAndCeil
 * @version 0.1
 * @date 2023-02-21
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
#include "floor_and_ceil.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::arrays::floor_and_ceil;

// Test Fixture Data Class
class FloorAndCeilData {
    std::vector<int> m_input;
    int m_target;
    std::pair<int,int> m_expected;
public:
    FloorAndCeilData() = default;

    std::vector<int> const & get_input() { return m_input; }
    int get_target() { return m_target; }
    std::pair<int,int> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const FloorAndCeilData &);
    friend std::istream& operator>>(std::istream&, FloorAndCeilData &);

};

std::ostream& operator<<(std::ostream& out, const FloorAndCeilData & data) {
    out << "FloorAndCeilData [ input=[";
    for(int value : data.m_input)
        out << " " << value;
    out << " ] target=" << data.m_target << " expected=(" << data.m_expected.first << "," << data.m_expected.second << ")";
    out << " ]";

    return out;
}

std::istream& operator>>(std::istream& in, FloorAndCeilData &data) {
    std::string line;

    if (static_cast<char>(in.peek()) == '[') {
        std::getline(in, line); // read in the '[' line
        while (static_cast<char>(in.peek()) != ']') {
            int value;
            in >> value;
            data.m_input.push_back(value);
            std::getline(in, line); // read the end of line
        } // while
        std::getline(in, line); // read in the ']' line
    } // if

    in >> data.m_target;
    std::getline(in, line); // read the end of line
    in >> data.m_expected.first >> data.m_expected.second;
    std::getline(in, line); // read the end of line

    return in;
}

// Test Fixture Class
class FloorAndCeilFixture :
    public testing::TestWithParam<FloorAndCeilData> {
};

// Parameterized Test Definition
TEST_P(FloorAndCeilFixture, FloorAndCeilTests) {
    FloorAndCeilData data = GetParam();

    Solution solution;

    std::pair<int,int> actual = solution.findFloorAndCeil(data.get_input(), data.get_target());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(FloorAndCeilTests, FloorAndCeilFixture, testing::ValuesIn(
    Loader<FloorAndCeilData>()(find_path("arrays/data/floor_and_ceil.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
