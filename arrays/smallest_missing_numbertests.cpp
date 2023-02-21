/**
 * @file smallest_missing_numbertests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains the tests for the problem https://www.techiedelight.com/?problem=SmallestMissingNumber
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
#include "smallest_missing_number.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::arrays::smallest_missing_number;

// Test Fixture Data Class
class SmallestMissingNumberData {
    std::vector<int> m_input;
    int m_expected;
public:
    SmallestMissingNumberData() = default;

    std::vector<int> const & get_input() { return m_input; }
    int get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const SmallestMissingNumberData &);
    friend std::istream& operator>>(std::istream&, SmallestMissingNumberData &);

};

std::ostream& operator<<(std::ostream& out, const SmallestMissingNumberData & data) {
    out << "SmallestMissingNumberData [ input=[";
    for (int value : data.m_input)
        out << " " << value;
    out << " ] expected=" << data.m_expected;
    out << " ]";

    return out;
}

std::istream& operator>>(std::istream& in, SmallestMissingNumberData &data) {
    std::string line;

    if (static_cast<char>(in.peek()) == '[') {
        std::getline(in,line);
        while (static_cast<char>(in.peek()) != ']') {
            int value;
            in >> value;
            data.m_input.push_back(value);
            std::getline(in, line); // read the end of line
        } // while
        std::getline(in, line); // read the ']' line character
    } // if

    in >> data.m_expected;
    std::getline(in, line); // read the end of line

    return in;
}

// Test Fixture Class
class SmallestMissingNumberFixture :
    public testing::TestWithParam<SmallestMissingNumberData> {
};

// Parameterized Test Definition
TEST_P(SmallestMissingNumberFixture, SmallestMissingNumberTests) {
    SmallestMissingNumberData data = GetParam();

    Solution solution;

    int actual = solution.findSmallestMissingNumber(data.get_input());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(SmallestMissingNumberTests, SmallestMissingNumberFixture, testing::ValuesIn(
    Loader<SmallestMissingNumberData>()(find_path("arrays/data/smallest_missing_number.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
