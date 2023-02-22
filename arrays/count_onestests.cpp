/**
 * @file count_onestests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains the tests for the problem https://www.techiedelight.com/?problem=CountOnes
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
#include "count_ones.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::arrays::count_ones;

// Test Fixture Data Class
class CountOnesData {
    std::vector<int> m_input;
    int m_expected;
public:
    CountOnesData() = default;

    std::vector<int> const & get_input() { return m_input; }
    int get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const CountOnesData &);
    friend std::istream& operator>>(std::istream&, CountOnesData &);

};

std::ostream& operator<<(std::ostream& out, const CountOnesData & data) {
    out << "CountOnesData [ input=[";
    for (int value : data.m_input)
        out << " " << value;
    out << " ] expected=" << data.m_expected;
    out << " ]";

    return out;
}

std::istream& operator>>(std::istream& in, CountOnesData &data) {
    std::string line;

    if (static_cast<char>(in.peek()) == '[') {
        char chr;
        in >> chr;  // read the '[' character
        while (static_cast<char>(in.peek()) != ']') {
            int value;
            in >> value;
            data.m_input.push_back(value);
        } // while
        std::getline(in, line); // read the ']' line
        in >> data.m_expected;
        std::getline(in, line); // read the end of line
    } // if

    return in;
}

// Test Fixture Class
class CountOnesFixture :
    public testing::TestWithParam<CountOnesData> {
};

// Parameterized Test Definition
TEST_P(CountOnesFixture, CountOnesTests) {
    CountOnesData data = GetParam();

    Solution solution;

    int actual = solution.countOnes(data.get_input());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(CountOnesTests, CountOnesFixture, testing::ValuesIn(
    Loader<CountOnesData>()(find_path("arrays/data/count_ones.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
